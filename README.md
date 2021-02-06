# MHWLua脚本载入Mod

可用于载入Lua脚本来控制游戏行为，脚本从nativePC\LuaScript\MainScript.lua中的run函数开始执行。

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

### Lua
|                                   |示例							                                               |说明						                     |
|-----------------------------------|---------------------------------------------------------------|-------------------------------------|
|Lua_Variable_SaveIntVariable       |`Lua_Variable_SaveIntVariable('VariableName',10)`              |存入整数变量                          |
|Lua_Variable_SaveFloatVariable		|`Lua_Variable_SaveFloatVariable('VariableName',1.0)`            |存入浮点数变量                       |
|Lua_Variable_SaveStringVariable	|`Lua_Variable_SaveStringVariable('VariableName','VariableValue')`|存入字符串变量                      |
|Lua_Variable_ReadIntVariable       |`local Variable = Lua_Variable_ReadIntVariable('VariableName')`|读取整数变量                          |
|Lua_Variable_ReadFloatVariable		|`local Variable = Lua_Variable_ReadFloatVariable('VariableName')`|读取浮点数变量                        |
|Lua_Variable_ReadStringVariable	|`local Variable = Lua_Variable_ReadStringVariable('VariableName')`|读取字符串变量                        |
|Lua_Variable_DestroyVariable		|`Lua_Variable_DestroyVariable('VariableName')`                 |销毁变量                             |

### 系统
|                                   |示例							                                               |说明						                     |
|-----------------------------------|---------------------------------------------------------------|-------------------------------------|
|System_Keyboard_CheckKey			|`System_Keyboard_CheckKey(87)`                                 |检查按键是否按下，按键为VK码           |
|System_Keyboard_CheckDoubleKey		|`System_Keyboard_CheckDoubleKey(87)`                           |检查是否双击按键，按键为VK码           |
|System_Chronoscope_AddChronoscope	|`System_Chronoscope_AddChronoscope(1.0,'ChronoscopeName')`     |创建计时器，需设定时间和计时器名称      |
|System_Chronoscope_CheckChronoscope|`System_Chronoscope_CheckChronoscope('ChronoscopeName')`       |检查指定名称的计时器是否到期，到期值为0 |
|System_Message_ShowMessage			|`System_Message_ShowMessage('Message')`       	                |向游戏内发送消息                      |
|System_Console_Info				|`System_Console_Info('Message')`       	                    |向控制台发送消息                      |
|System_Console_Error				|`System_Console_Error('Message')`       	                    |向控制台发送错误消息                  |

### 玩家
|                                         |示例							                                         |说明						   |
|-----------------------------------------|----------------------------------------------------------|------------------|
|Gmae_Player_GetPlayerCoordinate          |`local x,y,z = Gmae_Player_GetPlayerCoordinate()`         |获取玩家坐标       |
|Gmae_Player_SetPlayerCoordinate          |`Gmae_Player_SetPlayerCoordinate(1.0,1.0,1.0)`            |设置玩家坐标       |
|Gmae_Player_GetPlayerCollimatorCoordinate|`local x,y,z = Gmae_Player_GetPlayerCollimatorCoordinate()`|获取准星坐标       |
|Gmae_Player_GetPlayerIncrementCoordinate |`local x,y,z = Gmae_Player_GetPlayerIncrementCoordinate()`|获取坐标运动增量   |
|Gmae_Player_GetPlayerNavigationCoordinate|`local x,y,z = Gmae_Player_GetPlayerNavigationCoordinate()`|获取导航坐标      |
|Gmae_Player_GetPlayerVisualCoordinate    |`local x,y,z = Gmae_Player_GetPlayerVisualCoordinate()`   |获取视角相机坐标    |
|Gmae_Player_SetPlayerVisualCoordinate    |`Gmae_Player_SetPlayerVisualCoordinate(1.0,1.0,1.0,0)`    |设置玩家视角相机坐标，最后一位参数为持续时间，0为锁定|
|Gmae_Player_UnbindPlayerVisualCoordinate |`Gmae_Player_UnbindPlayerVisualCoordinate()`              |解除玩家视角相机坐标设置|
|Gmae_Player_CheckAimingStatus            |`Gmae_Player_CheckAimingStatus()`                         |检查是否处于瞄准状态|
|Gmae_Player_AddEffect                    |`Gmae_Player_AddEffect(0,0)`                              |为玩家添加特效     |
|Gmae_Player_GetPlayerActionId            |`Gmae_Player_GetPlayerActionId()`                         |获取玩家动作ID     |
|Gmae_Player_GetPlayerAngle               |`Gmae_Player_GetPlayerAngle()`                            |获取玩家面向角度   |
|Gmae_Player_Weapon_GetWeaponId           |`Gmae_Player_Weapon_GetWeaponId()`                        |获取玩家武器ID     |
|Gmae_Player_Weapon_GetWeaponType         |`Gmae_Player_Weapon_GetWeaponType()`                      |获取玩家武器类型   |
|Gmae_Player_GetFsmData                   |`local type,id = Gmae_Player_GetFsmData()`                |获取玩家当前派生动作信息   |
|Gmae_Player_RunFsmAction                 |`Gmae_Player_RunFsmAction(3,5)`                           |执行指定对象的派生动作，第一个参数为对象（玩家1，武器3）第二个参数为派生动作Id   |
|Gmae_Player_CheckRunFsmActionOver        |`Gmae_Player_CheckRunFsmActionOver()`                     |检查执行的派生动作是否结束  |
|Gmae_World_GetMapId                      |`Gmae_World_GetMapId()`                                   |获取地图ID        |

### 怪物
|                                         |示例                                                      |说明						   |
|-----------------------------------------|----------------------------------------------------------|------------------|
|Game_Monster_SetFilter                   |`Game_Monster_SetFilter(1,0)`                             |设置怪物筛选器     |
|Game_Monster_DisableFilter               |`Game_Monster_DisableFilter()`                            |清除怪物筛选器     |
|Game_Monster_SetBehaviorOfNavigationMonsters|`Game_Monster_SetBehaviorOfNavigationMonsters(20)`     |设置导航标记的怪物的行为,不受筛选器影响     |
|Game_Monster_KillNavigationMarkMonster   |`Game_Monster_KillNavigationMarkMonster()`               |杀死导航标记的怪物,受筛选器影响，返回是否成功击杀 |
|Game_Monster_AddDebuffToNavigationMarkMonster|`Game_Monster_AddDebuffToNavigationMarkMonster('Sleep')`|为导航标记的怪物添加异常状态,不受筛选器影响     |
|Game_Monster_SetBehaviorOfNearestMonsters|`Game_Monster_SetBehaviorOfNearestMonsters(20)`           |设置距离最近的怪物的行为,不受筛选器影响     |
|Game_Monster_KillNearestMonster          |`Game_Monster_KillNearestMonster()`                       |杀死距离最近的怪物,受筛选器影响，返回是否成功击杀 |
|Game_Monster_KillNearestMonsterInRange   |`Game_Monster_KillNearestMonsterInRange(0,2000)`         |杀死范围内距离最近的怪物,受筛选器影响，返回是否成功击杀 |
|Game_Monster_KillLastHitMonster          |`Game_Monster_KillLastHitMonster()`                       |杀死最后一次击中的怪物,不受筛选器影响，返回是否成功击杀 |
|Game_Monster_KillAllMonsterInRange       |`Game_Monster_KillAllMonsterInRange(0,2000)`              |杀死范围内所有的怪物,受筛选器影响 |
|Game_Monster_AddDebuffNearestMonster     |`Game_Monster_AddDebuffNearestMonster('Sleep')`           |为距离最近的怪物添加异常状态,不受筛选器影响     |
|Game_Monster_AddDebuffNearestMonsterInRange|`Game_Monster_AddDebuffNearestMonsterInRange('Sleep',0,2000)`|为距离最近的怪物添加异常状态,不受筛选器影响     |
|Game_Monster_SetBehaviorOfLastHitMonsters|`Game_Monster_SetBehaviorOfLastHitMonsters(20)`           |设置最后一次击中的怪物的行为,不受筛选器影响     |
|Game_Monster_AddDebuffLastHitMonster     |`Game_Monster_AddDebuffLastHitMonster('Sleep')`           |为最后一次击中的怪物添加异常状态,不受筛选器影响     |
|Game_Monster_AddDebuffToAllMonsterInRange|`Game_Monster_AddDebuffToAllMonsterInRange('Sleep',0,200)`|为范围内所有的怪物添加异常状态,受筛选器影响     |
|Game_Monster_GetNavigationMonsterCoordinates|`local x,y,z = Game_Monster_GetNavigationMonsterCoordinates()`|获取导航的怪物的坐标       |
|Game_Monster_GetNearestMonsterCoordinates|`local x,y,z = Game_Monster_GetNearestMonsterCoordinates()`|获取距离最近的怪物的坐标       |
|Game_Monster_GetLastHitMonsterCoordinates|`local x,y,z = Game_Monster_GetLastHitMonsterCoordinates()`|获取最后一次击中的怪物的坐标       |

### 环境生物
|                                         |示例                                                      |说明						   |
|-----------------------------------------|----------------------------------------------------------|------------------|
|Game_Environmental_SetFilter             |`Game_Environmental_SetFilter(1,0)`                       |设置环境生物筛选器  |
|Game_Environmental_DisableFilter         |`Game_Environmental_DisableFilter()`                      |清除环境生物筛选器  |
|Gmae_Environmental_SetAllEnvironmentalCoordinatesInRange|`Gmae_Environmental_SetAllEnvironmentalCoordinatesInRange(100.0,100.0,100.0,0,1000)`|设置范围内所有环境生物的坐标,受筛选器影响  |

## 数据表

## 怪物异常状态
|状态名         |示例	     |
|---------------|-----------|
|Retrea         |撤退       |
|Covet          |垂涎       |
|Dizziness      |眩晕       |
|Paralysis      |麻痹       |
|Sleep          |睡眠       |
|Anesthesia     |麻醉       |
|Poisoning      |中毒       |
|Ride           |骑乘       |
|Ridedowna      |骑乘倒地   |
|Reducebreath   |减气       |
|Explode        |爆破       |
|Flicker        |闪光       |
|FlickerG       |闪光G      |
|Smoke          |烟雾       |
|Foreignodor    |异臭       |
|Traphole       |落穴       |
|Stasistrap     |麻痹陷阱   |
