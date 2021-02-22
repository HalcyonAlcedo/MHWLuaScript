# 介绍

## 前言

在怪猎DllMod发展早期，制作这类Mod需要寻找地址、编写代码并编译成Dll文件。现在我们有了更加简单的方式制作复杂的脚本Mod，只需使用Lua脚本编写实现代码，无需再关心查找地址和编译文件，并且还拥有了实时调试的功能，希望这能为这款老游戏带来新鲜的活力。

## 使用说明

LuaScript脚本文件为Lua脚本，脚本运行时会每时间帧执行一次run函数，脚本结构如下

```lua
function run ()

end
```

需要执行的代码只需写在run函数中即可被执行，更多功能请浏览功能页面

{% page-ref page="gong-neng/" %}



## 多脚本合并

虽然LuaScript支持多脚本同时运行，但是脚本实例越多运行效率越低，建议使用时将多个脚本合并为1个脚本使用，如果需要多脚本文件管理，可以使用require方式加载到一个脚本中执行，这里请注意加载路径

{% hint style="warning" %}
加载路径请不要使用nativePC/LuaScript/路径，这样会被当成需执行的脚本被加载入游戏
{% endhint %}

{% tabs %}
{% tab title="Lua" %}
```lua
function run ()
    local NewLua= require('nativePC/LuaScript/Luas/NewLua')
    NewLua.run()
end
```
{% endtab %}

{% tab title="NewLua.lua" %}
```
local module = {}
function module.run ()

end
return module
```
{% endtab %}
{% endtabs %}

## 变量

这里要注意的是每次执行会清除上次Lua的全部数据，如果需要保留变量信息，请使用Lua辅助函数进行变量缓存，下面的例子中int将被自增，而float将始终为1

```lua
function run ()
    --这里读取了一个Int缓存变量，存放在局部变量int中
    local int = Lua_Variable_ReadIntVariable('int')
    --这里定义了一个变量float
    local float = 0
    int = int + 1
    float = float + 1
    --这里将int的修改存入缓存变量中
    Lua_Variable_SaveIntVariable('int', int)
end
```



