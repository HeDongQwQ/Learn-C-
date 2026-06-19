#include <windows.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

namespace {

constexpr int SCREEN_W = 80;
constexpr int VIEW_H = 22;
constexpr int HUD_H = 2;
constexpr int TOTAL_H = HUD_H + VIEW_H;
constexpr int MAP_W = 20;
constexpr int MAP_H = 16;
constexpr double PI = 3.14159265358979323846;
constexpr double FOV = PI / 3.0;
constexpr double MOVE_SPEED = 0.08;
constexpr double TURN_SPEED = 0.055;
constexpr double ENEMY_SPEED = 0.025;
constexpr double SHOOT_RANGE = 12.0;
constexpr double SHOOT_COOLDOWN = 0.35;

const char* MAP[MAP_H] = {
    "####################",
    "#P........#........#",
    "#.........#....E...#",
    "#...E.....####.....#",
    "#..................#",
    "#....E.......E.....#",
    "#..................#",
    "#########....#######",
    "#...........#......#",
    "#..E........#..E...#",
    "#...........#......#",
    "#....E......#......#",
    "#...........#..E...#",
    "#...........#......#",
    "#..E...............#",
    "####################",
};

struct Enemy {
    double x, y;
    bool alive = true;
};

struct Game {
    double px = 1.5;
    double py = 1.5;
    double angle = 0.0;
    int health = 100;
    int score = 0;
    int kills = 0;
    int totalEnemies = 0;
    bool running = true;
    bool won = false;
    bool lost = false;
    double shootTimer = 0.0;
    double hurtFlash = 0.0;
    double muzzleFlash = 0.0;
    std::vector<Enemy> enemies;
    char screen[TOTAL_H][SCREEN_W + 1];
    double depth[SCREEN_W];
};

Game g;

void initConsole() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info{};
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(out, &info);
}

void moveCursorHome() {
    COORD pos{0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

bool keyDown(int vk) {
    return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

bool isWall(int mx, int my) {
    if (mx < 0 || my < 0 || mx >= MAP_W || my >= MAP_H) return true;
    return MAP[my][mx] == '#';
}

bool isBlocking(double x, double y) {
    return isWall(static_cast<int>(x), static_cast<int>(y));
}

void loadLevel() {
    g.enemies.clear();
    for (int y = 0; y < MAP_H; ++y) {
        for (int x = 0; x < MAP_W; ++x) {
            char c = MAP[y][x];
            if (c == 'P') {
                g.px = x + 0.5;
                g.py = y + 0.5;
                g.angle = 0.0;
            } else if (c == 'E') {
                g.enemies.push_back({x + 0.5, y + 0.5, true});
            }
        }
    }
    g.totalEnemies = static_cast<int>(g.enemies.size());
}

char wallChar(double dist, bool horizontal) {
    if (dist < 1.5) return horizontal ? '|' : '=';
    if (dist < 3.0) return '#';
    if (dist < 6.0) return '+';
    if (dist < 10.0) return '.';
    return ':';
}

char floorChar(double dist) {
    if (dist < 2.0) return '_';
    if (dist < 5.0) return ',';
    return ' ';
}

void castRay(int col, double rayAngle) {
    double sinA = std::sin(rayAngle);
    double cosA = std::cos(rayAngle);

    int mapX = static_cast<int>(g.px);
    int mapY = static_cast<int>(g.py);

    double deltaDistX = (sinA == 0.0) ? 1e30 : std::abs(1.0 / sinA);
    double deltaDistY = (cosA == 0.0) ? 1e30 : std::abs(1.0 / cosA);

    int stepX, stepY;
    double sideDistX, sideDistY;

    if (sinA < 0) {
        stepX = -1;
        sideDistX = (g.px - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - g.px) * deltaDistX;
    }
    if (cosA < 0) {
        stepY = -1;
        sideDistY = (g.py - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - g.py) * deltaDistY;
    }

    bool hit = false;
    bool side = false;
    int hitX = mapX, hitY = mapY;

    for (int i = 0; i < 64; ++i) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = false;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = true;
        }
        if (isWall(mapX, mapY)) {
            hit = true;
            hitX = mapX;
            hitY = mapY;
            break;
        }
    }

    double dist;
    if (!hit) {
        dist = 20.0;
    } else if (side) {
        dist = (mapY - g.py + (1 - stepY) / 2.0) / sinA;
    } else {
        dist = (mapX - g.px + (1 - stepX) / 2.0) / cosA;
    }

    dist *= std::cos(rayAngle - g.angle);
    if (dist < 0.01) dist = 0.01;
    g.depth[col] = dist;

    int wallHeight = static_cast<int>(VIEW_H / dist);
    if (wallHeight > VIEW_H) wallHeight = VIEW_H;
    int drawStart = (VIEW_H - wallHeight) / 2;
    int drawEnd = drawStart + wallHeight;

    char wc = wallChar(dist, side);
    for (int row = 0; row < VIEW_H; ++row) {
        int y = HUD_H + row;
        if (row < drawStart) {
            g.screen[y][col] = '.';
        } else if (row < drawEnd) {
            g.screen[y][col] = wc;
        } else {
            double floorDist = dist + (row - VIEW_H / 2.0) * 0.15;
            g.screen[y][col] = floorChar(floorDist);
        }
    }
}

struct SpriteDraw {
    double dist;
    int index;
};

void drawEnemies() {
    std::vector<SpriteDraw> order;
    for (int i = 0; i < static_cast<int>(g.enemies.size()); ++i) {
        if (!g.enemies[i].alive) continue;
        double dx = g.enemies[i].x - g.px;
        double dy = g.enemies[i].y - g.py;
        order.push_back({dx * dx + dy * dy, i});
    }
    std::sort(order.begin(), order.end(),
              [](const SpriteDraw& a, const SpriteDraw& b) { return a.dist > b.dist; });

    for (const auto& s : order) {
        const Enemy& e = g.enemies[s.index];
        double dx = e.x - g.px;
        double dy = e.y - g.py;
        double dist = std::sqrt(dx * dx + dy * dy);
        if (dist < 0.3) continue;

        double enemyAngle = std::atan2(dy, dx);
        double rel = enemyAngle - g.angle;
        while (rel > PI) rel -= 2 * PI;
        while (rel < -PI) rel += 2 * PI;
        if (std::abs(rel) > FOV * 0.65) continue;

        int spriteScreenX = static_cast<int>((0.5 + rel / FOV) * SCREEN_W);
        int spriteH = static_cast<int>(VIEW_H / dist * 0.9);
        if (spriteH < 1) spriteH = 1;
        int spriteW = std::max(1, spriteH / 2);
        int drawStartY = (VIEW_H - spriteH) / 2;
        int drawEndY = drawStartY + spriteH;

        for (int stripe = -spriteW; stripe < spriteW; ++stripe) {
            int x = spriteScreenX + stripe;
            if (x < 0 || x >= SCREEN_W) continue;
            if (dist >= g.depth[x]) continue;

            for (int row = drawStartY; row < drawEndY; ++row) {
                if (row < 0 || row >= VIEW_H) continue;
                int y = HUD_H + row;
                int localRow = row - drawStartY;
                char ch;
                if (localRow < spriteH / 5) ch = 'o';
                else if (localRow > spriteH * 4 / 5) ch = '/';
                else if (stripe == 0) ch = 'E';
                else ch = '|';
                g.screen[y][x] = ch;
            }
        }
    }
}

void drawCrosshair() {
    int cx = SCREEN_W / 2;
    int cy = HUD_H + VIEW_H / 2;
    if (g.muzzleFlash > 0.0) {
        g.screen[cy][cx] = '*';
        g.screen[cy][cx - 1] = '*';
        g.screen[cy][cx + 1] = '*';
    } else {
        g.screen[cy][cx] = '+';
    }
}

void drawMinimap() {
    constexpr int MM_W = 16;
    constexpr int MM_H = 10;
    int ox = SCREEN_W - MM_W - 1;
    int oy = HUD_H + 1;

    for (int my = 0; my < MM_H; ++my) {
        for (int mx = 0; mx < MM_W; ++mx) {
            int mapX = mx * MAP_W / MM_W;
            int mapY = my * MAP_H / MM_H;
            char c = isWall(mapX, mapY) ? '#' : ' ';
            g.screen[oy + my][ox + mx] = c;
        }
    }

    for (const auto& e : g.enemies) {
        if (!e.alive) continue;
        int mx = ox + static_cast<int>(e.x * MM_W / MAP_W);
        int my = oy + static_cast<int>(e.y * MM_H / MAP_H);
        if (mx >= ox && mx < ox + MM_W && my >= oy && my < oy + MM_H) {
            g.screen[my][mx] = 'E';
        }
    }

    int px = ox + static_cast<int>(g.px * MM_W / MAP_W);
    int py = oy + static_cast<int>(g.py * MM_H / MAP_H);
    if (px >= ox && px < ox + MM_W && py >= oy && py < oy + MM_H) {
        g.screen[py][px] = '@';
    }
}

void render() {
    for (int y = 0; y < TOTAL_H; ++y) {
        std::memset(g.screen[y], ' ', SCREEN_W);
        g.screen[y][SCREEN_W] = '\0';
    }

    for (int x = 0; x < SCREEN_W; ++x) {
        double rayAngle = g.angle - FOV / 2.0 + (static_cast<double>(x) / SCREEN_W) * FOV;
        castRay(x, rayAngle);
    }

    drawEnemies();
    drawCrosshair();
    drawMinimap();

    if (g.hurtFlash > 0.0) {
        for (int y = HUD_H; y < TOTAL_H; ++y) {
            for (int x = 0; x < 3; ++x) {
                g.screen[y][x] = '!';
            }
        }
    }

    moveCursorHome();
    int alive = 0;
    for (const auto& e : g.enemies) if (e.alive) ++alive;

    std::cout << " FPS终端射击  生命:" << g.health
              << "  分数:" << g.score
              << "  敌人:" << alive << "/" << g.totalEnemies
              << "  [W/S前后 A/D平移 ←→转向 空格射击 ESC退出]\n";
    std::cout << " 视角:" << static_cast<int>(g.angle * 180 / PI) << "°"
              << "  击杀:" << g.kills
              << (g.shootTimer > 0 ? "  [换弹中...]" : "  [就绪]")
              << "\n";

    for (int y = 0; y < TOTAL_H; ++y) {
        std::cout << g.screen[y] << '\n';
    }
    std::cout << std::flush;
}

void tryMove(double nx, double ny) {
    if (!isBlocking(nx, g.py)) g.px = nx;
    if (!isBlocking(g.px, ny)) g.py = ny;
}

void handleInput() {
    if (keyDown(VK_ESCAPE)) {
        g.running = false;
        return;
    }

    double forwardX = std::cos(g.angle);
    double forwardY = std::sin(g.angle);
    double strafeX = std::cos(g.angle + PI / 2.0);
    double strafeY = std::sin(g.angle + PI / 2.0);

    if (keyDown('W')) tryMove(g.px + forwardX * MOVE_SPEED, g.py + forwardY * MOVE_SPEED);
    if (keyDown('S')) tryMove(g.px - forwardX * MOVE_SPEED, g.py - forwardY * MOVE_SPEED);
    if (keyDown('A')) tryMove(g.px - strafeX * MOVE_SPEED, g.py - strafeY * MOVE_SPEED);
    if (keyDown('D')) tryMove(g.px + strafeX * MOVE_SPEED, g.py + strafeY * MOVE_SPEED);
    if (keyDown(VK_LEFT)) g.angle -= TURN_SPEED;
    if (keyDown(VK_RIGHT)) g.angle += TURN_SPEED;

    static bool spaceWasDown = false;
    bool spaceDown = keyDown(VK_SPACE);
    if (spaceDown && !spaceWasDown && g.shootTimer <= 0.0) {
        g.shootTimer = SHOOT_COOLDOWN;
        g.muzzleFlash = 0.12;

        Enemy* best = nullptr;
        double bestScore = 1e9;
        for (auto& e : g.enemies) {
            if (!e.alive) continue;
            double dx = e.x - g.px;
            double dy = e.y - g.py;
            double dist = std::sqrt(dx * dx + dy * dy);
            if (dist > SHOOT_RANGE) continue;

            double aim = std::atan2(dy, dx);
            double diff = aim - g.angle;
            while (diff > PI) diff -= 2 * PI;
            while (diff < -PI) diff += 2 * PI;
            if (std::abs(diff) > 0.08) continue;

            double score = dist + std::abs(diff) * 10.0;
            if (score < bestScore) {
                bestScore = score;
                best = &e;
            }
        }

        if (best) {
            best->alive = false;
            g.score += 100;
            ++g.kills;
        }
    }
    spaceWasDown = spaceDown;
}

void updateEnemies(double dt) {
    for (auto& e : g.enemies) {
        if (!e.alive) continue;
        double dx = g.px - e.x;
        double dy = g.py - e.y;
        double dist = std::sqrt(dx * dx + dy * dy);
        if (dist < 0.45) {
            g.health -= static_cast<int>(40 * dt);
            g.hurtFlash = 0.15;
            if (g.health <= 0) {
                g.health = 0;
                g.lost = true;
                g.running = false;
            }
            continue;
        }
        if (dist > 0.5) {
            e.x += (dx / dist) * ENEMY_SPEED;
            e.y += (dy / dist) * ENEMY_SPEED;
            if (isBlocking(e.x, e.y)) {
                e.x -= (dx / dist) * ENEMY_SPEED;
                e.y -= (dy / dist) * ENEMY_SPEED;
            }
        }
    }

    bool anyAlive = false;
    for (const auto& e : g.enemies) {
        if (e.alive) { anyAlive = true; break; }
    }
    if (!anyAlive) {
        g.won = true;
        g.running = false;
    }
}

void updateTimers(double dt) {
    if (g.shootTimer > 0) g.shootTimer -= dt;
    if (g.hurtFlash > 0) g.hurtFlash -= dt;
    if (g.muzzleFlash > 0) g.muzzleFlash -= dt;
}

void showTitle() {
    system("cls");
    std::cout << "\n\n";
    std::cout << "  ========================================\n";
    std::cout << "       终 端 第 一 人 称 射 击 (FPS)\n";
    std::cout << "  ========================================\n\n";
    std::cout << "  射线投射 3D 视角，类似经典 Wolfenstein\n\n";
    std::cout << "  操作:\n";
    std::cout << "    W / S       前进 / 后退\n";
    std::cout << "    A / D       左平移 / 右平移\n";
    std::cout << "    ← / →       左转 / 右转\n";
    std::cout << "    空格        射击（准星对准敌人）\n";
    std::cout << "    ESC         退出\n\n";
    std::cout << "  目标: 消灭地图中所有敌人 E\n";
    std::cout << "  右上角小地图显示你的位置 @ 和敌人 E\n\n";
    std::cout << "  按 Enter 开始...\n";
    std::cin.get();
}

void showEndScreen() {
    system("cls");
    std::cout << "\n\n";
    if (g.won) {
        std::cout << "  ==============================\n";
        std::cout << "           任 务 完 成!\n";
        std::cout << "  ==============================\n\n";
    } else if (g.lost) {
        std::cout << "  ==============================\n";
        std::cout << "           你 已 阵 亡\n";
        std::cout << "  ==============================\n\n";
    } else {
        std::cout << "  游戏已退出\n\n";
    }
    std::cout << "  击杀: " << g.kills << " / " << g.totalEnemies << '\n';
    std::cout << "  分数: " << g.score << '\n';
    std::cout << "\n  按 Enter 退出...\n";
    std::cin.get();
}

}  // namespace

int main() {
    initConsole();
    showTitle();
    loadLevel();

    const double frameTime = 1.0 / 30.0;
    while (g.running) {
        handleInput();
        if (!g.running) break;
        updateEnemies(frameTime);
        updateTimers(frameTime);
        render();
        Sleep(33);
    }

    if (g.won || g.lost) {
        showEndScreen();
    }

    return 0;
}
