#include <iostream>
#include <windows.h>
int main() {
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        int a,b=0;
        char c;
        std::cout << "请输入一个整数：";
        std::cin >> a;
        std::cout << "请输入一个整数：";
        std::cin >> c;
        std::cout << "请输入一个字符：";
        std::cin >>b;
        switch (c) {
        case '+':
            std::cout << a + b << std::endl;
            break;
        case '-':
            std::cout << a - b << std::endl;
            break;
        case '*':
            std::cout << a * b << std::endl;
            break;
        case '/':
            if (b != 0) {
                std::cout << a / b << std::endl;
            } else {
                std::cout << "除数不能为0" << std::endl;
            }
            break;
        default:
            std::cout << "输入错误" << std::endl;
            break;
            }
            std::cout << "是否继续？(y/n)";
            std::cin >> c;
            if (c == 'n') {
                break;
            }
            else {
                continue;
            }
    }

    return 0;
}