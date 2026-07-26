- # 从现在开始学习C++
- ## 配置Cursor的C++环境
  1.下载msys64安装并配置
  
  2.在CurSor下载C++插件
  
  3.创建项目添加.vscode文件夹，在文件夹中添加launch.json，settings.json，tasks.json文件并分别键入：
  
  ---
	 launch.json
	```json
	{
	"version": "0.2.0",
	"configurations": [
		{
		"name": "Debug C++", // 配置名称
		"type": "cppdbg",
		"request": "launch",
		"program": "${fileDirname}/${fileBasenameNoExtension}.exe", // 要调试的程序路径
		"args": [],
		"stopAtEntry": false,
		"cwd": "${fileDirname}",
		"environment": [],
		"externalConsole": false,
		"MIMode": "gdb", // 调试器模式若使用MinGW则设为gdb
		"miDebuggerPath": "路径", // 指定gdb.exe调试器路径
		"preLaunchTask": "Build C++"  // 调试前自动执行的任务名称
			}
		]
	}
	
	```
	---
	
	settings.json
	```json
	{
		"clangd.arguments": [
		"--query-driver=路径"//路径填g++路径
		],
		"C_Cpp.intelliSenseEngine": "disabled"
	}
	```
	---
	
	tasks.json
	```json
	{
		"version": "2.0.0",
		"tasks": [
		{
			"label": "Build C++", // 任务名称
			"type": "shell",
			"command": "g++", // 编译器命令，需确保已在PATH中
			"args": [
			"-std=c++17", "-g", // 使用C++17标准并生成调试信息
			"${file}", // 当前打开的源文件
			"-o", // 指定输出文件
			"${fileDirname}/${fileBasenameNoExtension}.exe"  // 输出文件名
			],
			"group": {
			"kind": "build",
			"isDefault": true // 设为默认构建任务（按 Ctrl+Shift+B 触发）
			},
			"problemMatcher": ["$gcc"]
			}
		]
	}
	```
	
- ## 用C++简单输出HelloWorld
  1.创建hello.cpp文件
  
  hello.cpp
	```cpp
	#include<iostream>
	int main(){
		std::cout<<"HelloWorld"<<std::end1;
		return 0;//返回值0:
	}
	```
	---

## 输入输出

```cpp
cout << "文字" << endl;   // 打印到屏幕
cin >> a >> b;            // 从键盘读入
```

- `<<`：往外送（输出）
- `>>`：往里装（输入）
- 可以一路串：文字、变量、算式都能接在后面
- 读多个数时中间用空格或回车分隔，例如输入 `3 5`

---

## 变量与运算

```cpp
int a, b;        // 整数变量（装数的盒子）
a + b; a - b; a * b;
a % 2;           // 取余：能整除 2 就是偶数
```

- `=` 是赋值（把右边装进左边）
- `==` 是判断相等
- 不要混：`n % 2 = 0` 是错的，判断要用 `==`

---

## 条件判断

```cpp
if (n > 0) {
    // 正数
} else if (n < 0) {
    // 负数
} else {
    // 零
}

if (n % 2 == 0) {
    // 偶数
} else {
    // 奇数
}
```

满足哪个条件就走哪一段。多个互斥条件用 `else if` 串起来。

---

## 循环

```cpp
int sum = 0;
for (int i = 1; i <= n; i++) {
    if (i % 2 == 0) {
        cout << i << " ";   // 筛偶数
    }
    sum = sum + i;          // 累加 1 到 n
}
```

`for` 三部分：

```text
for (初始; 条件; 步进)   // 例如 i=1; i<=n; i++
```

- 初始：开始前做一次
- 条件：为真就继续
- 步进：每轮结束执行（`i++` 表示加 1）
- 累加变量要在循环外先设为 0

---

## 数组（固定长度）

```cpp
int a[5];                 // 5 个格子，下标 0～4
for (int i = 0; i < 5; i++) {
    cin >> a[i];
}

int max = a[0];           // 先假定第一个是最大
int min = a[0];
for (int i = 0; i < 5; i++) {
    if (a[i] > max) max = a[i];
    if (a[i] < min) min = a[i];
}
```

- 下标从 0 开始，不是从 1
- `a[5]` 越界，合法只有 `a[0]`～`a[4]`
- 找最大/最小：先用第一个当极值，再跟后面比，更大/更小就更新
- 长度写死，人数一变就要改代码

---

## 函数

把一段逻辑起个名字，需要时调用：

```cpp
int add(int a, int b) {
    return a + b;
}

int findMax(int arr[], int len) {
    int max = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// 调用
cout << add(3, 5);              // 8
cout << findMax(arr, len);
```

- 主程序更干净，同样逻辑不用抄多遍
- 数组传给函数时，通常再传一个长度
- 在 `main` 里可写：`int len = sizeof(arr) / sizeof(arr[0]);`

---

## 指针与引用

**指针**：存的是「地址」

```cpp
int x = 10;
int *p = &x;   // p 指向 x

cout << x;     // 10，值本身
cout << &x;    // x 的地址
cout << p;     // 和 &x 一样
cout << *p;    // 顺着地址拿到 10

*p = 99;       // 改的就是 x
```

- `&x`：取地址
- `*p`：解引用，访问指针指向的那个变量

**引用**：变量的别名，改别名就是改原变量

```cpp
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
```

- 带 `&` 传参，函数里改了，外面真的变
- 若不写 `&`（值传递），外面不会变
- 后面给 `vector` 传参时，要改列表也必须写 `vector<Student>& st`

---

## 类（class）

把「数据 + 相关操作」捆成一种自定义类型。

正确思路：**一个对象 = 一个学生**

```cpp
class Student {
public:
    string name;
    int score;
    void print() {
        cout << name << " " << score << endl;
    }
};

Student s1, s2;   // 两个学生 → 两个对象
cin >> s1.name >> s1.score;
s1.print();
```

- `public:` 下面的成员，外面可以用 `对象.成员` 访问
- 不要把好几个学生的姓名、分数全塞进同一个对象的数组里
- 用 `string` 时建议 `#include <string>`

---

## vector（能变长的数组）

```cpp
#include <vector>

vector<int> v;
v.push_back(x);    // 往末尾加
v[i];              // 按下标用
v.size();          // 当前有几个
v.clear();         // 清空
```

- 长度可以随输入变，比写死 `int a[5]` 灵活
- 典型用法：先读人数 `n`，再循环 `n` 次 `push_back`
- 空的时候先别访问 `v[0]`

和定长数组比：个数不固定时优先用 `vector`。

---

## string（字符串）

```cpp
#include <string>

string word;
cin >> word;
word.size();                    // 长度
word[0];                        // 第一个字符
word[word.size() - 1];          // 最后一个
```

注意：`cin >>` / 文件里的 `>>` 遇到空格就停，姓名里不要带空格。

---

## 排序与查找

```cpp
#include <algorithm>

sort(v.begin(), v.end());       // 从小到大

// 自定义：按学生分数从高到低
bool cmp(const Student& a, const Student& b) {
    return a.score > b.score;   // 返回 true 表示 a 排在 b 前面
}
sort(st.begin(), st.end(), cmp);
```

升序 / 降序：

```cpp
return a.score < b.score;   // 升序
return a.score > b.score;   // 降序
```

查找：

```cpp
bool found = false;
for (int i = 0; i < st.size(); i++) {
    if (st[i].name == name) {
        found = true;
        st[i].print();
        break;              // 找到就停
    }
}
if (!found) {
    cout << "没有找到" << endl;
}
```

- `v.begin()` / `v.end()`：排序的起止范围
- `const Student&`：只读引用，比较时不拷贝、不修改
- `sort` 第三个参数写函数名 `cmp`，不要写成 `cmp()`

---

## 文件读写

```cpp
#include <fstream>
```

程序关掉，内存里的数据就没了；写进文件才能长期保存。

**写文件**（像 `cout`）：

```cpp
ofstream fout("Student.txt");
if (!fout) {
    cout << "打开失败" << endl;
    return;
}
for (int i = 0; i < st.size(); i++) {
    fout << st[i].name << " " << st[i].score << endl;
}
fout.close();
```

**读文件**（像 `cin`，推荐读到没有为止）：

```cpp
ifstream fin("Student.txt");
if (!fin) {
    cout << "打开失败" << endl;
    return;
}
st.clear();                     // 先清空再装
Student s;
while (fin >> s.name >> s.score) {
    st.push_back(s);
}
fin.close();
```

- 文件名是相对路径，实际写在「程序运行时的当前目录」
- 写完最好 `close`
- 读写格式要一致（比如都是 `姓名 分数`）
- 尽量用 `while (fin >> ...)`，别死绑内存里已有的人数

---

## 菜单循环与拆函数

把各个功能写成函数，主程序用菜单反复调用：

```cpp
void addStudent(vector<Student>& st) { /* 读入并 push_back */ }
void showAll(const vector<Student>& st) { /* 遍历打印 */ }
void saveToFile(const vector<Student>& st) { /* ofstream 写入 */ }
void loadFromFile(vector<Student>& st) { /* clear + while 读入 */ }

int main() {
    vector<Student> st;         // 放在循环外，大家共用
    int choice;
    do {
        cout << "1添加 2显示 3排序 4查找 5保存 6加载 0退出\n";
        cin >> choice;
        if (choice == 1) addStudent(st);
        else if (choice == 2) showAll(st);
        else if (choice == 5) saveToFile(st);
        else if (choice == 6) loadFromFile(st);
        // ...
    } while (choice != 0);
    return 0;
}
```

传参：

- `vector<Student>& st`：函数要改列表（添加、加载）
- `const vector<Student>& st`：只读（显示、保存）

显示和加载不是一回事：

- **显示**：遍历内存里的 `st` 打印
- **加载**：`clear` 后从文件读进 `st`

若用 `switch`：不要把 `vector` 声明在某个 `case` 里；`case` 里声明变量时用 `{ }` 包起来。初学用 `if / else if` 更省事。

---

## 常用头文件

| 头文件 | 提供 |
|---|---|
| `<iostream>` | `cin` / `cout` |
| `<string>` | `string` |
| `<vector>` | `vector` |
| `<algorithm>` | `sort` |
| `<fstream>` | `ofstream` / `ifstream` |


