# Lua辅助函数

## Lua\_Variable\_SaveIntVariable\(name,value\)

存入整数变量

| 参数 | 说明 | 类型 |
| :--- | :--- | :--- |
| name | 变量名 | string |
| value | 变量值 | int |

```bash
Lua_Variable_SaveIntVariable('VariableName',10)
```

## Lua\_Variable\_SaveFloatVariable\(name,value\)

存入浮点数变量

| 参数 | 说明 | 类型 |
| :--- | :--- | :--- |
| name | 变量名 | string |
| value | 变量值 | float |

```bash
Lua_Variable_SaveFloatVariable('VariableName',1.0)
```

## Lua\_Variable\_SaveStringVariable\(name,value\)

存入字符串变量

| 参数 | 说明 | 类型 |
| :--- | :--- | :--- |
| name | 变量名 | string |
| value | 变量值 | string |

```bash
Lua_Variable_SaveStringVariable('VariableName',1.0)
```

## Lua\_Variable\_ReadIntVariable\(name\)

读取整数变量

## Lua\_Variable\_ReadFloatVariable\(name\)

读取浮点数变量

## Lua\_Variable\_ReadStringVariable\(name\)

读取字符串变量

## Lua\_Variable\_DestroyVariable\(name\)

销毁变量

## Lua\_Variable\_SaveGlobalIntVariable\(name,value\)

存入全局整数变量

## Lua\_Variable\_SaveGlobalFloatVariable\(name,value\)

存入全局浮点数变量

## Lua\_Variable\_SaveGlobalStringVariable\(name,value\)

存入全局字符串变量

## Lua\_Variable\_ReadGlobalIntVariable\(name\)

读取全局整数变量

## Lua\_Variable\_ReadGlobalFloatVariable\(name\)

读取全局浮点数变量

## Lua\_Variable\_ReadGlobalStringVariable\(name\)

读取全局字符串变量

## Lua\_Variable\_DestroyGlobalVariable\(name\)

销毁全局变量

## Lua\_Math\_Rander\(min,max\)

获取随机数

## Lua\_Http\_GetHttpData\(url\)

获取指定网址的数据

