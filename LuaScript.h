#pragma once
#include <lua.hpp> 
#include "loader.h"
lua_State* L;
#pragma region GameFun
static int Gmae_Player_GetPlayerCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Entity.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Entity.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Entity.z);
    return 3;
}
static int Gmae_Player_SetPlayerCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Component::MovePlayerToPoint(Component::Coordinate{ x,y,z });
    return 0;
}
static int Gmae_Player_GetPlayerCollimatorCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.z);
    return 3;
}
static int Gmae_Player_CheckAimingStatus(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::AimingState);
    return 1;
}
static int Gmae_Player_AddEffect(lua_State* pL) {
    int group = (int)lua_tointeger(pL, 1);
    int record = (int)lua_tointeger(pL, 2);
    Base::PlayerData::Effects::GenerateSpecialEffects(group, record);
    return 0;
}
static int Gmae_Player_GetPlayerIncrementCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Increment.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Increment.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Increment.z);
    return 3;
}
static int Gmae_Player_GetPlayerNavigationCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Navigation.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Navigation.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Navigation.z);
    return 3;
}
static int Gmae_Player_GetPlayerVisualCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Visual.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Visual.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Visual.z);
    return 3;
}
static int Gmae_Player_SetPlayerVisualCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    float duration = (float)lua_tonumber(pL, 3);
    Base::PlayerData::SetVisual(x,y,z, duration);
    return 0;
}
static int Gmae_Player_UnbindPlayerVisualCoordinate(lua_State* pL) {
    Base::PlayerData::UnbindVisual();
    return 0;
}
static int Gmae_Player_GetPlayerActionId(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::ActionId);
    return 1;
}
static int Gmae_Player_GetPlayerAngle(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Angle);
    return 1;
}
static int Gmae_Player_Weapon_GetWeaponId(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::WeaponId);
    return 1;
}
static int Gmae_Player_Weapon_GetWeaponType(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::WeaponType);
    return 1;
}
static int Gmae_Player_GetFsmData(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Fsm.Target);
    lua_pushnumber(pL, Base::PlayerData::Fsm.Id);
    return 2;
}
static int Gmae_Player_RunFsmAction(lua_State* pL) {
    int type = (int)lua_tonumber(pL, 1);
    int id = (int)lua_tonumber(pL, 2);
    Base::PlayerData::RunDerivedAction(type, id);
    return 0;
}
static int Gmae_Player_CheckRunFsmActionOver(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::CheckDerivedAction());
    return 1;
}
static int Gmae_World_GetMapId(lua_State* pL) {
    lua_pushnumber(pL, Base::World::MapId);
    return 1;
}
static int Game_Monster_SetFilter(lua_State* pL) {
    int id = (int)lua_tonumber(pL, 1);
    int subId = (int)lua_tonumber(pL, 2);
    Component::SetMonsterFilter(id,subId);
    return 0;
}
static int Game_Monster_DisableFilter(lua_State* pL) {
    Component::DisableMonsterFilter();
    return 0;
}
static int Game_Monster_SetBehaviorOfNavigationMonsters(lua_State* pL) {
    int fsmId = (int)lua_tonumber(pL, -1);
    lua_pushnumber(pL, Component::NavigationMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillNavigationMarkMonster(lua_State* pL) {
    lua_pushnumber(pL, Component::KillNavigationMonster());
    return 1;
}
static int Game_Monster_SetBehaviorOfNearestMonsters(lua_State* pL) {
    int fsmId = (int)lua_tonumber(pL, -1);
    lua_pushnumber(pL, Component::NearestMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillNearestMonster(lua_State* pL) {
    lua_pushnumber(pL, Component::KillNearestMonster());
    return 1;
}
static int Game_Monster_KillNearestMonsterInRange(lua_State* pL) {
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_pushnumber(pL, Component::KillNearestMonster(min, max));
    return 1;
}
static int Game_Monster_SetBehaviorOfLastHitMonsters(lua_State* pL) {
    int fsmId = (int)lua_tonumber(pL, -1);
    lua_pushnumber(pL, Component::LastHitMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillLastHitMonster(lua_State* pL) {
    lua_pushnumber(pL, Component::KillLastHitMonster());
    return 1;
}
static int Game_Monster_AddDebuffToNavigationMarkMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushnumber(pL, Component::SetNavigationMonsterBuff(buff));
    return 1;
}
static int Game_Monster_AddDebuffNearestMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushnumber(pL, Component::SetNearestMonsterBuff(buff));
    return 1;
}
static int Game_Monster_AddDebuffNearestMonsterInRange(lua_State* pL) {
    string buff = (string)lua_tostring(pL, 1);
    float min = (float)lua_tonumber(pL, 2);
    float max = (float)lua_tonumber(pL, 3);
    lua_pushnumber(pL, Component::SetNearestMonsterBuff(buff, min, max));
    return 1;
}
static int Game_Monster_AddDebuffLastHitMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushnumber(pL, Component::SetLastHitMonsterBuff(buff));
    return 1;
}

#pragma endregion
#pragma region SystemFun
static int System_Keyboard_CheckKey(lua_State* pL) {    
    int key = (int)lua_tointeger(pL, -1);
    lua_pushnumber(pL, Base::Keyboard::CheckKey(key));
    return 1;
}
static int System_Keyboard_CheckDoubleKey(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    lua_pushnumber(pL, Base::Keyboard::CheckKey(key, 2));
    return 1;
}
static int System_Chronoscope_AddChronoscope(lua_State* pL) {
    float time = (float)lua_tonumber(pL, 1);
    string name = (string)lua_tostring(pL, 2);
    Base::Chronoscope::AddChronoscope(time, name, true);
    return 0;
}
static int System_Chronoscope_CheckChronoscope(lua_State* pL) {
    string name = (string)lua_tostring(pL, -1);
    lua_pushnumber(pL, Base::Chronoscope::CheckChronoscope(name));
    return 1;
}
static int System_Message_ShowMessage(lua_State* pL) {
    string message = (string)lua_tostring(pL, -1);
    Component::ShowMessage(message);
    return 0;
}
static int System_Console_Info(lua_State* pL) {
    string message = (string)lua_tostring(pL, -1);
    LOG(INFO) << Base::ModConfig::ModName << " LUA INFO:" << message;
    return 0;
}
static int System_Console_Error(lua_State* pL) {
    string message = (string)lua_tostring(pL, -1);
    LOG(ERR) << Base::ModConfig::ModName << " LUA ERR:"<< message;
    return 0;
}
#pragma endregion
//==============================================
// Main Functions
//==============================================
int Lua_Main()
{
    lua_State* L = luaL_newstate();
    luaopen_base(L);     // 加载Lua基本库
    luaL_openlibs(L);
    //L = lua_open();   //新版本被弃用   

   /* load the script */
    #pragma region Game
    //获取玩家坐标
    lua_register(L, "Gmae_Player_GetPlayerCoordinate", Gmae_Player_GetPlayerCoordinate);
    //设置玩家坐标
    lua_register(L, "Gmae_Player_SetPlayerCoordinate", Gmae_Player_SetPlayerCoordinate);
    //获取准星坐标
    lua_register(L, "Gmae_Player_GetPlayerCollimatorCoordinate", Gmae_Player_GetPlayerCollimatorCoordinate);
    //检查瞄准状态
    lua_register(L, "Gmae_Player_CheckAimingStatus", Gmae_Player_CheckAimingStatus);
    //获取增量坐标
    lua_register(L, "Gmae_Player_GetPlayerIncrementCoordinate", Gmae_Player_GetPlayerIncrementCoordinate);
    //获取导航坐标
    lua_register(L, "Gmae_Player_GetPlayerNavigationCoordinate", Gmae_Player_GetPlayerNavigationCoordinate);
    //获取相机坐标
    lua_register(L, "Gmae_Player_GetPlayerVisualCoordinate", Gmae_Player_GetPlayerVisualCoordinate);
    //设置相机坐标（xyz和持续时间4个参数）
    lua_register(L, "Gmae_Player_SetPlayerVisualCoordinate", Gmae_Player_SetPlayerVisualCoordinate);
    //解除相机坐标绑定
    lua_register(L, "Gmae_Player_UnbindPlayerVisualCoordinate", Gmae_Player_UnbindPlayerVisualCoordinate);
    //获取玩家动作id
    lua_register(L, "Gmae_Player_GetPlayerActionId", Gmae_Player_GetPlayerActionId);
    //获取面向角度
    lua_register(L, "Gmae_Player_GetPlayerAngle", Gmae_Player_GetPlayerAngle);
    //添加特效
    lua_register(L, "Gmae_Player_AddEffect", Gmae_Player_AddEffect);
    //获取玩家武器Id
    lua_register(L, "Gmae_Player_Weapon_GetWeaponId", Gmae_Player_Weapon_GetWeaponId);
    //获取玩家武器类型
    lua_register(L, "Gmae_Player_Weapon_GetWeaponType", Gmae_Player_Weapon_GetWeaponType);
    //获取玩家派生信息
    lua_register(L, "Gmae_Player_GetFsmData", Gmae_Player_GetFsmData);
    //执行指定的派生动作
    lua_register(L, "Gmae_Player_RunFsmAction", Gmae_Player_RunFsmAction);
    //检查执行的派生动作是否结束
    lua_register(L, "Gmae_Player_CheckRunFsmActionOver", Gmae_Player_CheckRunFsmActionOver);

    //获取当前地图Id
    lua_register(L, "Gmae_World_GetMapId", Gmae_World_GetMapId);
    
    //设置怪物筛选器
    lua_register(L, "Game_Monster_SetFilter", Game_Monster_SetFilter);
    //清除怪物筛选器
    lua_register(L, "Game_Monster_DisableFilter", Game_Monster_DisableFilter);
    //控制导航怪物的行为
    lua_register(L, "Game_Monster_SetBehaviorOfNavigationMonsters", Game_Monster_SetBehaviorOfNavigationMonsters);
    //杀死导航标记的怪物
    lua_register(L, "Game_Monster_KillNavigationMarkMonster", Game_Monster_KillNavigationMarkMonster);
    //给导航标记的怪物设置异常状态
    lua_register(L, "Game_Monster_AddDebuffToNavigationMarkMonster", Game_Monster_AddDebuffToNavigationMarkMonster);
    //控制距离最近的怪物的行为
    lua_register(L, "Game_Monster_SetBehaviorOfNearestMonsters", Game_Monster_SetBehaviorOfNearestMonsters);
    //杀死距离最近的怪物
    lua_register(L, "Game_Monster_KillNearestMonster", Game_Monster_KillNearestMonster);
    //杀死范围内距离最近的怪物
    lua_register(L, "Game_Monster_KillNearestMonsterInRange", Game_Monster_KillNearestMonsterInRange);
    //给距离最近的怪物设置异常状态
    lua_register(L, "Game_Monster_AddDebuffNearestMonster", Game_Monster_AddDebuffNearestMonster);
    //给范围内距离最近的怪物设置异常状态
    lua_register(L, "Game_Monster_AddDebuffNearestMonsterInRange", Game_Monster_AddDebuffNearestMonsterInRange);
    //控制最后一次击中的怪物的行为
    lua_register(L, "Game_Monster_SetBehaviorOfLastHitMonsters", Game_Monster_SetBehaviorOfLastHitMonsters);
    //杀死最后一次击中的怪物
    lua_register(L, "Game_Monster_KillLastHitMonster", Game_Monster_KillLastHitMonster);
    //给最后一次击中的怪物设置异常状态
    lua_register(L, "Game_Monster_AddDebuffLastHitMonster", Game_Monster_AddDebuffLastHitMonster);
    
    #pragma endregion
    #pragma region System
    //检查按键
    lua_register(L, "System_Keyboard_CheckKey", System_Keyboard_CheckKey);
    //检查按键双击
    lua_register(L, "System_Keyboard_CheckDoubleKey", System_Keyboard_CheckDoubleKey);
    //添加计时器
    lua_register(L, "System_Chronoscope_AddChronoscope", System_Chronoscope_AddChronoscope);
    //检查计时器
    lua_register(L, "System_Chronoscope_CheckChronoscope", System_Chronoscope_CheckChronoscope);
    //向游戏内发送消息
    lua_register(L, "System_Message_ShowMessage", System_Message_ShowMessage);
    //向控制台发送消息
    lua_register(L, "System_Console_Info", System_Console_Info);
    //向控制台发送错误消息
    lua_register(L, "System_Console_Error", System_Console_Error);
    #pragma endregion

    int error = luaL_dofile(L, "nativePC/LuaScript/MainScript.lua");    // 读取Lua源文件到内存编译
    if (error)
    {
        //LOG(ERR) << "dofile error";
        return -1;
    }
    lua_getglobal(L, "run");
    lua_pcall(L, 0, 0, 0);
    lua_close(L);
    return 1;
}