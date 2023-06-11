## 官网

官网: [https://love2d.org/](https://love2d.org/)

wiki: [https://love2d.org/wiki/Main_Page_(简体中文)](https://love2d.org/wiki/Main_Page_(简体中文))

## 安装

参考: [https://love2d.org/wiki/Getting_Started_(简体中文)](https://love2d.org/wiki/Getting_Started_(简体中文))

```shell
sudo add-apt-repository ppa:bartbes/love-stable
sudo apt-get update
sudo apt-get install love
```

直接运行`love`
![](/assets/image/love2d/index/01.png)


## 使用 vscode
安装如下插件

* Love2D Support

* Love2d Snippets

* Love2d Made Easy

* love-launcher

![](/assets/image/love2d/index/02.png)

打开设置, 修改如下位置

![](/assets/image/love2d/index/03.png)

![](/assets/image/love2d/index/04.png)

## hello world
!!! note
    `love2d` 的启动文件必须为`main.lua`

### 代码
```lua linenums="1" title="main.lua"
function love.draw()
    love.graphics.rectangle("fill", 10, 100, 120, 80)
end
```

### 运行方法
第一种:

![](/assets/image/love2d/index/05.png)

第二种:保存后立即运行

![](/assets/image/love2d/index/07.png)

### 运行效果

![](/assets/image/love2d/index/06.png)

## 参考资料
### lua资料
[Lua 5.3 参考手册 云风翻译](http://cloudwu.github.io/lua53doc/manual.html)

[Lua 最全的快速入门教程](https://panguangyu.blog.csdn.net/article/details/88775896)

[Visual Studio Code -> VSCode 开发环境搭建 ---- Lua 代码调试（code runner 插件）](https://blog.csdn.net/yanwennian/article/details/103524744)

### love2d
开源社区: [https://github.com/love2d-community](https://github.com/love2d-community)

[https://www.love2d.org/wiki/Category:Tutorials](https://www.love2d.org/wiki/Category:Tutorials) 中有一个 [How to LÖVE](https://sheepolution.com/learn/book/contents). 介绍比较详细, 对应的视频教程:[Love2d游戏开发入门中文教程全网独家](https://www.bilibili.com/video/BV16Q4y1z7Hd), 对应的博客: [Love2d从青铜到王者](https://blog.csdn.net/qq_44918090/category_11757733.html)

[【Udemy高赞+中英字幕】使用 LÖVE 2D 和 Lua 进行游戏开发 – 完整课程 - freeCodeCamp](https://www.bilibili.com/video/BV1Se4y1S7L5/)

[love2d 教程 半山](https://www.cnblogs.com/xdao/tag/love2d/default.html?page=3)


### box2d

[Box2D v2.1.0用户手册翻译](https://blog.csdn.net/complex_ok/category_871440.html)






