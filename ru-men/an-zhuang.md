# 安装

## 安装

1. 下载最新的[LuaScript](https://github.com/HalcyonAlcedo/MHWLuaScript/releases)文件
2. 解压文件到游戏根目录
3. 下载并安装[Stracker's Loader](https://www.nexusmods.com/monsterhunterworld/mods/1982)
4. 写入脚本启动游戏，测试脚本是否正常运行

测试脚本示例

```lua
function run ()
    local init = Lua_Variable_ReadIntVariable('init')
    if init == 0 then
        init = 1
        System_Message_ShowMessage('LuaScript init success')
    end
    Lua_Variable_SaveIntVariable('init', init)
end
```

