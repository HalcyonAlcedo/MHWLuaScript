# MHWLua脚本载入Mod

可用于载入Lua脚本来控制游戏行为，Lua从nativePC\LuaScript\MainScript.lua中的run函数开始执行。

## 示例

示例脚本为盾斧的瞬移脚本，可在持有盾斧时双击w瞬移至瞄准的目标点

    function run ()
	    if System_Chronoscope_CheckChronoscope('BlinkCD') == 0 then
	        if System_Keyboard_CheckDoubleKey(87) == 1  and
	            Gmae_Player_CheckAimingStatus() == 1 and
	            Gmae_Player_Weapon_GetWeaponType() == 9
	        then 
	            local x,y,z = Gmae_Player_GetPlayerCollimatorCoordinate()
	            Gmae_Player_SetPlayerCoordinate(x,y,z)
	            Gmae_Player_AddEffect(2003,5)
	            System_Chronoscope_AddChronoscope(5.0,'BlinkCD')
	        end
	    else
	        Gmae_Player_AddEffect(2002,0)
	    end
	end

## API说明

### 系统操作
|                                   |示例							                                               |说明						                     |
|-----------------------------------|---------------------------------------------------------------|-------------------------------------|
|System_Keyboard_CheckKey			      |`System_Keyboard_CheckKey(87)`                                 |检查按键是否按下，按键为VK码           |
|System_Keyboard_CheckDoubleKey		  |`System_Keyboard_CheckDoubleKey(87)`                           |检查是否双击按键，按键为VK码           |
|System_Chronoscope_AddChronoscope	|`System_Chronoscope_AddChronoscope(1.0,'ChronoscopeName')`     |创建计时器，需设定时间和计时器名称      |
|System_Chronoscope_CheckChronoscope|`System_Chronoscope_CheckChronoscope('ChronoscopeName')`       |检查指定名称的计时器是否到期，到期值为0 |

### 玩家数据
|                                         |示例							                                         |说明						   |
|-----------------------------------------|----------------------------------------------------------|------------------|
|Gmae_Player_GetPlayerCoordinate          |`local x,y,z = Gmae_Player_GetPlayerCoordinate()`         |获取玩家坐标       |
|Gmae_Player_SetPlayerCoordinate          |`Gmae_Player_SetPlayerCoordinate(1.0,1.0,1.0)`            |设置玩家坐标       |
|Gmae_Player_GetPlayerCollimatorCoordinate|`local x,y,z = Gmae_Player_GetPlayerCoordinate()`         |获取准星坐标       |
|Gmae_Player_CheckAimingStatus            |`Gmae_Player_CheckAimingStatus()`                         |检查是否处于瞄准状态|
|Gmae_Player_AddEffect                    |`Gmae_Player_AddEffect(0,0)`                              |为玩家添加特效     |
|Gmae_Player_Weapon_GetWeaponType         |`Gmae_Player_Weapon_GetWeaponType()`                      |获取玩家武器类型   |
