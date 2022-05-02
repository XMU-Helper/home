# 厦门大学WebVPN



## 介绍

为了方便老师同学们在外网访问内网和图书馆资源，学校开通了新版 VPN ([WebVPN](https://webvpn.xmu.edu.cn))

![img](https://s2.loli.net/2022/04/27/WxH5iUKu86YIdjR.png)

登录后可以访问的网站非常有限（为了避免VPN滥用）

![img](https://s2.loli.net/2022/04/27/5UuiZIzrbqsjVG1.png)



## 问题

但是很多时候不得不使用校内ip访问一些其他校内网站，[校内ip检测](https://beian.xmu.edu.cn/checkip)

![img](https://s2.loli.net/2022/04/27/HVlpGjwT9sdA38Q.png)



## 解决

简单利用WebVPN设计的漏洞



### 方式1：

登录[WebVPN](https://webvpn.xmu.edu.cn)，通过浏览器的开发者工具执行如下代码

方法：按F12 - 点击控制台(console) - 复制后粘贴下列代码 - 回车

```js
    const waitUntilElementPresent = (cssLocator, callback)=>{
        var checkExist = setInterval(function () {
            if (document.querySelector(cssLocator)) {
                clearInterval(checkExist)
                callback()
                return;
            }
        }, 100)
        }

    waitUntilElementPresent("#history", ()=>{
        var newNode = document.createElement("div");
        newNode.innerHTML =`
<div class="layui-form-item" style="display: flex;flex-direction: row;margin: auto;padding: 40px">
    <div style="width: 90%">
        <label class="layui-form-label">URL</label>
        <div class="layui-input-block" style="width: auto">
            <input id="url-to-go" type="text" placeholder="请输入跳转链接" class="layui-input">
        </div>
    </div>
    <div>
        <button class="layui-btn layui-btn-normal" onclick="go(document.getElementById('url-to-go').value)">进入</button>
    </div>
</div>`;
        document.getElementById("vpn-content").insertBefore(newNode,document.getElementById("history"));
    })
```

效果如下：

![img](https://s2.loli.net/2022/04/27/Q68jFs7NDl4OznA.png)



输入想要跳转的网页链接，点击进入按钮即可，如进入[校内ip检测](https://beian.xmu.edu.cn/checkip)

![img](https://s2.loli.net/2022/04/27/wxKa4tcq8Hni9g1.png)

可见已成功使用WebVPN访问

![img](https://s2.loli.net/2022/04/27/fGzL7ieXqu3sEP5.png)





### 方式2：

使用浏览器油猴插件，可省去每次登录WebVPN后使用开发者工具执行代码



方法：进入油猴插件的脚本管理 - 新建脚本 - 将新脚本内容替换为下列代码 - 保存即可

```js
// ==UserScript==
// @name         厦门大学WebVPN
// @namespace    https://github.com/ruchuby
// @version      0.1
// @description  厦门大学WebVPN自定义跳转!
// @author       ruchuby
// @match        https://webvpn.xmu.edu.cn/
// ==/UserScript==

(function() {
    'use strict';
    const waitUntilElementPresent = (cssLocator, callback)=>{
        var checkExist = setInterval(function () {
            if (document.querySelector(cssLocator)) {
                clearInterval(checkExist)
                callback()
                return;
            }
        }, 100)
        }

    waitUntilElementPresent("#history", ()=>{
        var newNode = document.createElement("div");
        newNode.innerHTML =`
<div class="layui-form-item" style="display: flex;flex-direction: row;margin: auto;padding: 40px">
    <div style="width: 90%">
        <label class="layui-form-label">URL</label>
        <div class="layui-input-block" style="width: auto">
            <input id="url-to-go" type="text" placeholder="请输入跳转链接" class="layui-input">
        </div>
    </div>
    <div>
        <button class="layui-btn layui-btn-normal" onclick="go(document.getElementById('url-to-go').value)">进入</button>
    </div>
</div>`;
        document.getElementById("vpn-content").insertBefore(newNode,document.getElementById("history"));
    })
})();
```



之后每次登录Web后都会看到和**方式1**中一样的URL跳转输入框，其他同上。