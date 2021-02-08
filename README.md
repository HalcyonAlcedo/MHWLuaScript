# MHWLua脚本载入Mod

可用于载入Lua脚本来控制游戏行为，初始化完成后将加载Monster Hunter World\nativePC\LuaScript中的全部lua文件并运行其中的run函数。

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
|                                   |示例                                                           |说明                     |
|-----------------------------------|---------------------------------------------------------------|-------------------------------------|
|System_Keyboard_CheckKey			|`System_Keyboard_CheckKey(87)`                                 |检查按键是否按下，按键为VK码           |
|System_Keyboard_CheckDoubleKey		|`System_Keyboard_CheckDoubleKey(87)`                           |检查是否双击按键，按键为VK码           |
|System_Keyboard_CheckKeyIsPressed	|`System_Keyboard_CheckKeyIsPressed(87)`                        |检查按键是否处于按下状态，按键为VK码           |
|System_Chronoscope_AddChronoscope	|`System_Chronoscope_AddChronoscope(1.0,'ChronoscopeName')`     |创建计时器，需设定时间和计时器名称      |
|System_Chronoscope_CheckChronoscope|`System_Chronoscope_CheckChronoscope('ChronoscopeName')`       |检查指定名称的计时器是否到期 |
|System_Chronoscope_CheckPresenceChronoscope|`System_Chronoscope_CheckPresenceChronoscope('ChronoscopeName')`|检查指定名称的计时器是存在 |
|System_Chronoscope_DelChronoscope  |`System_Chronoscope_DelChronoscope('ChronoscopeName')`           |删除指定名称的计时器    |
|System_Message_ShowMessage			|`System_Message_ShowMessage('Message')`       	                |向游戏内发送消息                      |
|System_Console_Info				|`System_Console_Info('Message')`       	                    |向控制台发送消息                      |
|System_Console_Error				|`System_Console_Error('Message')`       	                    |向控制台发送错误消息                  |

### 玩家
|                                         |示例							                                         |说明						   |
|-----------------------------------------|----------------------------------------------------------|------------------|
|Gmae_Player_GetPlayerCoordinate          |`local x,y,z = Gmae_Player_GetPlayerCoordinate()`         |获取玩家坐标       |
|Gmae_Player_SetPlayerCoordinate          |`Gmae_Player_SetPlayerCoordinate(1.0,1.0,1.0)`            |设置玩家坐标       |
|Gmae_Player_GetPlayerCollimatorCoordinate|`local x,y,z = Gmae_Player_GetPlayerCollimatorCoordinate()`|获取准星坐标      |
|Gmae_Player_GetPlayerWeaponCoordinate    |`local x,y,z = Gmae_Player_GetPlayerWeaponCoordinate()`   |获取武器坐标       |
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
|Gmae_Player_Weapon_ChangeWeapons         |`Gmae_Player_Weapon_ChangeWeapons(0,20)`                  |更换玩家的武器（武器类型，武器id）   |
|Gmae_Player_GetFsmData                   |`local type,id = Gmae_Player_GetFsmData()`                |获取玩家当前派生动作信息   |
|Gmae_Player_RunFsmAction                 |`Gmae_Player_RunFsmAction(3,5)`                           |执行指定对象的派生动作，第一个参数为对象（玩家1，武器3）第二个参数为派生动作Id   |
|Gmae_Player_CheckRunFsmActionOver        |`Gmae_Player_CheckRunFsmActionOver()`                     |检查执行的派生动作是否结束  |
|Gmae_Player_GetPlayerHealth              |`local BasicHealth,MaxHealth,Health = Gmae_Player_GetPlayerHealth()`|获取玩家血量信息（基础，最大，当前）   |
|Gmae_Player_SetPlayerCurrentHealth       |`Gmae_Player_SetPlayerCurrentHealth(10)`                  |设置玩家当前血量   |
|Gmae_Player_SetPlayerBasicHealth         |`Gmae_Player_SetPlayerBasicHealth(100)`                   |设置玩家基础血量0-150   |
|Gmae_Player_GetPlayerEndurance           |`local MaxEndurance,Endurance = Gmae_Player_GetPlayerEndurance()` |获取玩家耐力信息（最大，当前）   |
|Gmae_Player_SetPlayerCurrentEndurance    |`Gmae_Player_SetPlayerCurrentEndurance(50)`               |设置玩家当前耐力   |
|Gmae_Player_SetPlayerMaxEndurance        |`Gmae_Player_SetPlayerMaxEndurance(25)`                   |设置玩家最大耐力25-150  |
|Gmae_Player_GetPlayerRoleInfo            |`local name,hr,mr = Gmae_Player_GetPlayerRoleInfo()`      |获取玩家角色信息   |
|~~Gmae_Player_CreateProjectiles~~        |`Gmae_Player_CreateProjectiles(12,startX,startY,startZ,endX,endY,endZ)`|1.0.7弃用，请使用特定对象的方法 |
|Gmae_Player_CreateWeaponProjectiles      |`Gmae_Player_CreateWeaponProjectiles(12,startX,startY,startZ,endX,endY,endZ)`|生成玩家武器投射物（投射物id,起始坐标,结束坐标） |
|Gmae_Player_CreateBowgunProjectiles      |`Gmae_Player_CreateBowgunProjectiles(12,startX,startY,startZ,endX,endY,endZ)`|生成玩家手弩投射物（投射物id,起始坐标,结束坐标） |
|Gmae_Player_GetPlayerBuffDuration        |`local buffDuration = Gmae_Player_GetPlayerBuffDuration('BuffName')`|获取玩家Buff剩余时间   |
|Gmae_Player_SetPlayerBuffDuration        |`Gmae_Player_SetPlayerBuffDuration('BuffName',20)`           |设置玩家Buff持续时间   |
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
|Game_Monster_GetAllMonsterCoordinatesInRange|`local monsterList = Game_Monster_GetAllMonsterCoordinatesInRange()`|获取范围内所有怪物的坐标，受筛选器影响，包含属性X,Y,Z,Id,SubId     |

### 环境生物
|                                         |示例                                                      |说明						   |
|-----------------------------------------|----------------------------------------------------------|------------------|
|Game_Environmental_SetFilter             |`Game_Environmental_SetFilter(1,0)`                       |设置环境生物筛选器  |
|Game_Environmental_DisableFilter         |`Game_Environmental_DisableFilter()`                      |清除环境生物筛选器  |
|Gmae_Environmental_SetAllEnvironmentalCoordinatesInRange|`Gmae_Environmental_SetAllEnvironmentalCoordinatesInRange(100.0,100.0,100.0,0,1000)`|设置范围内所有环境生物的坐标,受筛选器影响  |
|Game_Environmental_GetAllEnvironmentalCoordinatesInRange|`local environmentalList = Game_Environmental_GetAllEnvironmentalCoordinatesInRange()`|获取范围内所有环境生物的坐标，受筛选器影响，包含属性X,Y,Z,Id,SubId  |


## 数据表

## 怪物异常状态
|状态名         |说明	     |
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

## 玩家Buff名称
|Buff名称                           |说明             |
|-----------------------------------|----------------|
|Whistle Self Improvement			|笛·自我强化      |
|Whistle Attack Up					|笛·攻击力UP大    |
|Whistle Health Up					|笛·体力UP大      |
|Whistle Stamina Use Reduced		|笛·耐力消耗减轻大 |
|Whistle All Wind Pressure Negated	|笛·风压无效       |
|Whistle Defense Up					|笛·防御力UP大       |
|Whistle Tool Use Drain Reduced		|笛·特殊道具消耗减轻大|
|Whistle Recovery Up				|笛·体力回复速度UP大|
|Whistle Earplugs					|笛·听觉保护大    |
|Whistle Divine Protection			|笛·精灵王的加护  |
|Whistle Scoutfly Power Up			|笛·导虫追踪力强化|
|Whistle Envir. Damage Negated		|笛·地形伤害无效  |
|Whistle Stun Negated				|笛·晕厥无效     |
|Whistle Paralysis Negated			|笛·麻痹无效     |
|Whistle Tremors Negated			|笛·震动无效     |
|Whistle Much/Water/Deep Snow Res	|笛·适应泥沙水场深雪|
|Whistle Fire Res Up				|笛·火属性防御UP大|
|Whistle Water Res Up				|笛·水属性防御UP大|
|Whistle Thunder Res Up				|笛·雷属性防御UP大|
|Whistle Ice Res Up					|笛·冰属性防御UP大|
|Whistle Dragon Res Up				|笛·龙属性防御UP大|
|Whistle Elemental Attack Boost		|笛·属性攻击力提升|
|Whistle Blight Negated				|笛·全属性异常状态无效|
|Whistle Knockbacks Negated			|笛·后仰无效|
|Whistle Blight Resistance Up		|笛·全属性防御强化|
|Whistle Affinity Up				|笛·会心率提升|
|Whistle All Ailments Negated		|笛·全状态异常无效|
|Whistle Abnormal Status Atk. Increase|笛·异常攻击力提升|
|Whistle Max Stamina Up / Recovery	|笛·耐力最大值UP与回复|
|Whistle Extended Health Recovery	|笛·体力最大值UP与回复|
|Whistle Speed Boost / Evade Window Up|笛·速度与回避性能UP|
|Whistle Elemental Effectiveness	|笛·属性效果提升|
|Palico Resuscitate					|猫·复苏|
|Palico Attack Up					|猫·攻击力UP大|
|Palico Defense Up					|猫·防御力UP大|
|Palico Affinity Up					|猫·会心率提升|
|Palico Recovery Up					|猫·恢复速度UP|
|Palico Health Up					|猫·体力UP|
|Palico Stamina Up					|猫·耐力消耗减轻|
|Palico Divine Protection			|猫·精灵王加护|
|Palico Stun Negated				|猫·晕厥无效|
|Palico Thunder Negated				|猫·麻痹无效|
|Palico Seismic						|猫·耐震|
|Palico Hearing Protection			|猫·听觉保护|
|Fire Blight						|火属性异常|
|Thunder Blight						|雷属性异常|
|Water Blight						|水属性异常|
|Ice Blight							|冰属性异常|
|Dragon Blight						|龙属性异常|
|Bleed								|撕裂伤害|
|Effuvial							|瘴气伤害|
|Poison								|中毒|
|High Poison						|猛毒|
|Blastscourge						|爆破黏菌|
|Defense Down						|防御下降|
|Whistle Down						|属性耐性下降|
|Prohibited Articles				|禁止使用物品|
|blasting Blight					|爆破属性异常|
|Bleed Recovery						|撕裂恢复|
|Dash Juice							|强走药|
|Wiggle Litch						|耐力雷虫|
|Recovery Up						|活力剂|
|Might Seed							|怪力种子|
|Adamant Seed						|忍耐种子|
|Demon Powder						|鬼人粉尘|
|Hardshell Powder					|硬化粉尘|
|Attack +12							|攻击力+12|
|Defense +30						|防御力+30|
|Cool Drink							|冷饮|
|Hot Drink							|热饮|
|Hot Springs: HP Regen				|温泉：HP回复|
|Hot Springs: Cold Res				|温泉：寒冷耐性|
|Thawpuff: Ice Res					|冰耐草：冰耐性提升|
|Powercone							|鬼毬果：攻击力up|
|Encouraging						|振奋|
|Surrender							|不屈|
|Slip By Strengthening				|滑走强化|
|Attacks On The Defensive			|攻击守势|
|Turn Calamity Into Blessing		|转祸为福|
|Challenger							|挑战者|
|Resentment							|怨恨|
|Cat Rest							|猫的休息术|
|Snowman Head						|雪人头|
|Snowman Head Duration				|雪人头持续时间|
