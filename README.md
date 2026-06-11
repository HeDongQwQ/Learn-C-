- # 从现在开始学习C++
- ## 配置Cursor的C++环境
  1.下载msys64安装并配置
  
  2.在CurSor下载C++插件
  
  3.创建项目添加.vscode文件夹，在文件夹中添加launch.json，settings.json，tasks.json文件并分别键入：
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

		"miDebuggerPath": "路径“, // 指定gdb.exe调试器路径

		"preLaunchTask": "Build C++"  // 调试前自动执行的任务名称

			}

		]
	}
	
	```
	settings.json
	```json
	{

		"clangd.arguments": [

		"--query-driver=路径"//路径填g++路径

		],

		"C_Cpp.intelliSenseEngine": "disabled"

	}
	```
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
