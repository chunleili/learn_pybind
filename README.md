编译
```
cmake -B build ; cmake --build build --config=Release
```
会默认拷贝.pyd文件到python目录（只要.pyd文件与.py文件在同一目录下就可以）


运行
```
./python/test_mymod.py
```

Optional:
- 如果用vscode, control+shift+p 然后选择运行 my cmake build也可以编译
- 用`python run.py`也可以编译然后运行test_mymod.py
- 用`python run.py setup`可以打包并且安装到本地, 安装之后可以在任何地方import mymod
