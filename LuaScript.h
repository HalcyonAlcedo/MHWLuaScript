#pragma once
//#include <lua.hpp>
#include "loader.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
lua_State* L;
static string Nowlua;
static string Sublua;
#pragma region GameFun
static int Game_Player_GetPlayerCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Entity.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Entity.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Entity.z);
    return 3;
}
static int Game_Player_SetPlayerCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Component::MovePlayerToPoint(Base::Vector3( x,y,z ));
    return 0;
}
static int Game_Player_GetPlayerCollimatorCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Collimator.z);
    return 3;
}
static int Game_Player_GetPlayerParabolaCollimatorCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Parabola.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Parabola.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Parabola.z);
    return 3;
}
static int Game_Player_GetPlayerWeaponCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Weapon.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Weapon.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Weapon.z);
    return 3;
}
static int Game_Player_CheckAimingStatus(lua_State* pL) {
    lua_pushboolean(pL, Base::PlayerData::AimingState);
    return 1;
}
static int Game_Player_AddEffect(lua_State* pL) {
    int group = (int)lua_tointeger(pL, 1);
    int record = (int)lua_tointeger(pL, 2);
    Base::PlayerData::Effects::GenerateSpecialEffects(group, record);
    return 0;
}
static int Game_Player_GetPlayerIncrementCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Increment.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Increment.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Increment.z);
    return 3;
}
static int Game_Player_GetPlayerNavigationCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Navigation.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Navigation.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Navigation.z);
    return 3;
}
static int Game_Player_GetPlayerVisualCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Visual.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Visual.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Visual.z);
    return 3;
}
static int Game_Player_SetPlayerVisualCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::SetVisual(x,y,z);
    return 0;
}
static int Game_Player_UnbindPlayerVisualCoordinate(lua_State* pL) {
    Base::PlayerData::UnbindVisual();
    return 0;
}
static int Game_Player_GetPlayerActionId(lua_State* pL) {
    lua_pushinteger(pL, Base::PlayerData::ActionId);
    return 1;
}
static int Game_Player_GetPlayerAngle(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Angle);
    return 1;
}
static int Game_Player_SetPlayerAngle(lua_State* pL) {
    float angle = (float)lua_tonumber(pL, -1);
    Base::PlayerData::SetPlayerAimAngle(angle);
    return 0;
}
static int Game_Player_SetPlayerAimToCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float z = (float)lua_tonumber(pL, 2);
    Base::PlayerData::SetPlayerAimCoordinate(x,z);
    return 0;
}
static int Game_Player_GetPlayerGravity(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Gravity);
    return 1;
}
static int Game_Player_GetPlayerFallSpeedRate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Fallspeedrate);
    return 1;
}
static int Game_Player_SetPlayerGravity(lua_State* pL) {
    float gravity = (float)lua_tonumber(pL, 1);
    Base::PlayerData::SetGravity(gravity);
    return 0;
}
static int Game_Player_SetPlayerFallSpeedRate(lua_State* pL) {
    float fallSpeedRate = (float)lua_tonumber(pL, 1);
    Base::PlayerData::SetFallSpeedRate(fallSpeedRate);
    return 0;
}
static int Game_Player_CheckPlayerAirState(lua_State* pL) {
    lua_pushboolean(pL, Base::PlayerData::PlayerAirState);
    return 1;
}
static int Game_Player_Weapon_GetWeaponId(lua_State* pL) {
    lua_pushinteger(pL, Base::PlayerData::Weapons::WeaponId);
    return 1;
}
static int Game_Player_Weapon_GetWeaponType(lua_State* pL) {
    lua_pushinteger(pL, Base::PlayerData::Weapons::WeaponType);
    return 1;
}
static int Game_Player_Weapon_ChangeWeapons(lua_State* pL) {
    int type = (int)lua_tointeger(pL, 1);
    int id = (int)lua_tointeger(pL, 2);
    Base::PlayerData::Weapons::ChangeWeapons(type, id, false);
    return 0;
}
static int Game_Player_Weapon_CompleteChangeWeapons(lua_State* pL) {
    int type = (int)lua_tointeger(pL, 1);
    int id = (int)lua_tointeger(pL, 2);
    Base::PlayerData::Weapons::ChangeWeapons(type, id);
    return 0;
}
static int Game_Player_Weapon_GetOrnamentsCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsCoordinate.x);
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsCoordinate.y);
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsCoordinate.z);
    return 3;
}
static int Game_Player_Weapon_GetOrnamentsSize(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsSize.x);
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsSize.y);
    lua_pushnumber(pL, Base::PlayerData::WeaponOrnaments::OrnamentsSize.z);
    return 3;
}
static int Game_Player_Weapon_SetOrnamentsCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::WeaponOrnaments::SetOrnamentsCoordinate(x, y, z);
    return 0;
}
static int Game_Player_Weapon_SetOrnamentsSize(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::WeaponOrnaments::SetOrnamentsSize(x, y, z);
    return 0;
}
static int Game_Player_Weapon_DecontrolOrnamentsCoordinate(lua_State* pL) {
    Base::PlayerData::WeaponOrnaments::DecontrolOrnamentsCoordinate();
    return 0;
}
static int Game_Player_Weapon_DecontrolOrnamentsSize(lua_State* pL) {
    Base::PlayerData::WeaponOrnaments::DecontrolOrnamentsSize();
    return 0;
}
static int Game_Player_Weapon_GetMainWeaponCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponCoordinate.x);
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponCoordinate.y);
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponCoordinate.z);
    return 3;
}
static int Game_Player_Weapon_GetMainWeaponSize(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponSize.x);
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponSize.y);
    lua_pushnumber(pL, Base::PlayerData::Weapons::MainWeaponSize.z);
    return 3;
}
static int Game_Player_Weapon_SetMainWeaponCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::Weapons::SetMainWeaponCoordinate(x, y, z);
    return 0;
}
static int Game_Player_Weapon_SetMainWeaponSize(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::Weapons::SetMainWeaponSize(x, y, z);
    return 0;
}
static int Game_Player_Weapon_DecontrolMainWeaponCoordinate(lua_State* pL) {
    Base::PlayerData::Weapons::DecontrolMainWeaponCoordinate();
    return 0;
}
static int Game_Player_Weapon_DecontrolMainWeaponSize(lua_State* pL) {
    Base::PlayerData::Weapons::DecontrolMainWeaponSize();
    return 0;
}
static int Game_Player_Weapon_GetSecondaryWeaponCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponCoordinate.x);
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponCoordinate.y);
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponCoordinate.z);
    return 3;
}
static int Game_Player_Weapon_GetSecondaryWeaponSize(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponSize.x);
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponSize.y);
    lua_pushnumber(pL, Base::PlayerData::Weapons::SecondaryWeaponSize.z);
    return 3;
}
static int Game_Player_Weapon_SetSecondaryWeaponCoordinate(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::Weapons::SetSecondaryWeaponCoordinate(x, y, z);
    return 0;
}
static int Game_Player_Weapon_SetSecondaryWeaponSize(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Base::PlayerData::Weapons::SetSecondaryWeaponSize(x, y, z);
    return 0;
}
static int Game_Player_Weapon_DecontrolSecondaryWeaponCoordinate(lua_State* pL) {
    Base::PlayerData::Weapons::DecontrolSecondaryWeaponCoordinate();
    return 0;
}
static int Game_Player_Weapon_DecontrolSecondaryWeaponSize(lua_State* pL) {
    Base::PlayerData::Weapons::DecontrolSecondaryWeaponSize();
    return 0;
}
static int Game_Player_Weapon_CharacteristicIntValue(lua_State* pL) {
    string ptr = "0x" + (string)lua_tostring(pL, 1);
    lua_pushinteger(pL, Component::GetWeaponCharacteristicIntValue(ptr));
    return 1;
}
static int Game_Player_Weapon_CharacteristicFloatValue(lua_State* pL) {
    string ptr = "0x" + (string)lua_tostring(pL, 1);
    lua_pushnumber(pL, Component::GetWeaponCharacteristicFloatValue(ptr));
    return 1;
}
static int Game_Player_Weapon_CharacteristicByteValue(lua_State* pL) {
    string ptr = "0x" + (string)lua_tostring(pL, 1);
    lua_pushinteger(pL, Component::GetWeaponCharacteristicByteValue(ptr));
    return 1;
}
static int Game_Player_Weapon_GetHitCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Weapons::HitCoordinate.x);
    lua_pushnumber(pL, Base::PlayerData::Weapons::HitCoordinate.y);
    lua_pushnumber(pL, Base::PlayerData::Weapons::HitCoordinate.z);
    return 3;
}
static int Game_Player_Weapon_GetAttackMonster(lua_State* pL) {
    ostringstream ptr;
    ptr << Base::PlayerData::AttackMonsterPlot;
    string ptrstr = ptr.str();
    lua_pushstring(pL, ptrstr.c_str());
    return 1;
}
static int Game_Player_GetFsmData(lua_State* pL) {
    lua_pushinteger(pL, Base::PlayerData::NowFsm.Target);
    lua_pushinteger(pL, Base::PlayerData::NowFsm.Id);
    return 2;
}
static int Game_Player_RunFsmAction(lua_State* pL) {
    int type = (int)lua_tointeger(pL, 1);
    int id = (int)lua_tointeger(pL, 2);
    Base::PlayerData::RunDerivedAction(type, id);
    return 0;
}
static int Game_Player_CheckRunFsmActionOver(lua_State* pL) {
    lua_pushboolean(pL, Base::PlayerData::CheckDerivedAction());
    return 1;
}
static int Game_Player_RunLmtAction(lua_State* pL) {
    int id = (int)lua_tointeger(pL, -1);
    Base::PlayerData::RunAction(id);
    return 0;
}
static int Game_Player_GetActionFrame(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::ActionFrame);
    lua_pushnumber(pL, Base::PlayerData::ActionFrameEnd);
    return 2;
}
static int Game_Player_SetActionFrame(lua_State* pL) {
    float frame = (float)lua_tonumber(pL, -1);
    Base::PlayerData::SetActionFrame(frame);
    return 0;
}
static int Game_Player_SetActionFrameSpeed(lua_State* pL) {
    float frameSpeed = (float)lua_tonumber(pL, 1);
    Base::PlayerData::TempData::t_ActionFrameSpeedTarget = (int)lua_tointeger(pL, 2);
    if(frameSpeed < 0)
        Base::PlayerData::TempData::t_SetActionFrameSpeed = false;
    else
        Base::PlayerData::TempData::t_SetActionFrameSpeed = true;
    Base::PlayerData::TempData::t_ActionFrameSpeed = frameSpeed;
    return 0;
}
static int Game_Player_GetPlayerHealth(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::BasicHealth);
    lua_pushnumber(pL, Base::PlayerData::MaxHealth);
    lua_pushnumber(pL, Base::PlayerData::CurrentHealth);
    return 3;
}
static int Game_Player_SetPlayerCurrentHealth(lua_State* pL) {
    float health = (float)lua_tonumber(pL, 1);
    Component::SetPlayerHealth(health);
    return 0;
}
static int Game_Player_SetPlayerBasicHealth(lua_State* pL) {
    float health = (float)lua_tonumber(pL, 1);
    Component::SetPlayerBasicHealth(health);
    return 0;
}
static int Game_Player_GetPlayerEndurance(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::MaxEndurance);
    lua_pushnumber(pL, Base::PlayerData::CurrentEndurance);
    return 2;
}
static int Game_Player_SetPlayerCurrentEndurance(lua_State* pL) {
    float endurance = (float)lua_tonumber(pL, 1);
    Component::SetPlayerEndurance(endurance);
    return 0;
}
static int Game_Player_SetPlayerMaxEndurance(lua_State* pL) {
    float endurance = (float)lua_tonumber(pL, 1);
    Component::SetPlayerMaxEndurance(endurance);
    return 0;
}
static int Game_Player_GetPlayerRoleInfo(lua_State* pL) {
    //lua_pushstring(pL, Base::PlayerData::Name.c_str());
    lua_pushinteger(pL, Base::PlayerData::Hr);
    lua_pushinteger(pL, Base::PlayerData::Mr);
    return 2;
}
static int Game_World_GetMapId(lua_State* pL) {
    lua_pushinteger(pL, Base::World::MapId);
    return 1;
}
static int Game_World_Message(lua_State* pL) {
    lua_pushstring(pL, Base::World::Massage.c_str());
    return 1;
}
static int Game_Monster_SetFilter(lua_State* pL) {
    int id = (int)lua_tointeger(pL, 1);
    int subId = (int)lua_tointeger(pL, 2);
    Component::SetMonsterFilter(id,subId);
    return 0;
}
static int Game_Monster_DisableFilter(lua_State* pL) {
    Component::DisableMonsterFilter();
    return 0;
}
static int Game_Monster_SetBehaviorOfNavigationMonsters(lua_State* pL) {
    int fsmId = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Component::NavigationMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillNavigationMarkMonster(lua_State* pL) {
    lua_pushboolean(pL, Component::KillNavigationMonster());
    return 1;
}
static int Game_Monster_SetBehaviorOfNearestMonsters(lua_State* pL) {
    int fsmId = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Component::NearestMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillNearestMonster(lua_State* pL) {
    lua_pushboolean(pL, Component::KillNearestMonster());
    return 1;
}
static int Game_Monster_KillNearestMonsterInRange(lua_State* pL) {
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_pushboolean(pL, Component::KillNearestMonster(min, max));
    return 1;
}
static int Game_Monster_SetBehaviorOfLastHitMonsters(lua_State* pL) {
    int fsmId = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Component::LastHitMonsterBehaviorControl(fsmId));
    return 1;
}
static int Game_Monster_KillLastHitMonster(lua_State* pL) {
    lua_pushboolean(pL, Component::KillLastHitMonster());
    return 1;
}
static int Game_Monster_KillAllMonsterInRange(lua_State* pL) {
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    Component::KillAllMonster(min, max);
    return 0;
}
static int Game_Monster_AddDebuffToNavigationMarkMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushboolean(pL, Component::SetNavigationMonsterBuff(buff));
    return 1;
}
static int Game_Monster_AddDebuffNearestMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushboolean(pL, Component::SetNearestMonsterBuff(buff));
    return 1;
}
static int Game_Monster_AddDebuffNearestMonsterInRange(lua_State* pL) {
    string buff = (string)lua_tostring(pL, 1);
    float min = (float)lua_tonumber(pL, 2);
    float max = (float)lua_tonumber(pL, 3);
    lua_pushboolean(pL, Component::SetNearestMonsterBuff(buff, min, max));
    return 1;
}
static int Game_Monster_AddDebuffLastHitMonster(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushboolean(pL, Component::SetLastHitMonsterBuff(buff));
    return 1;
}
static int Game_Monster_AddDebuffToAllMonsterInRange(lua_State* pL) {
    string buff = (string)lua_tostring(pL, 1);
    float min = (float)lua_tonumber(pL, 2);
    float max = (float)lua_tonumber(pL, 3);
    Component::SetAllMonsterBuff(buff, min, max);
    return 0;
}
static int Game_Monster_GetNavigationMonsterCoordinates(lua_State* pL) {
    Base::Vector3 Coordinate = Component::GetNavigationMonsterCoordinates();
    lua_pushnumber(pL, Coordinate.x);
    lua_pushnumber(pL, Coordinate.y);
    lua_pushnumber(pL, Coordinate.z);
    return 3;
}
static int Game_Monster_GetNearestMonsterCoordinates(lua_State* pL) {
    Base::Vector3 Coordinate = Component::GetNearestMonsterCoordinates();
    lua_pushnumber(pL, Coordinate.x);
    lua_pushnumber(pL, Coordinate.y);
    lua_pushnumber(pL, Coordinate.z);
    return 3;
}
static int Game_Monster_GetLastHitMonsterCoordinates(lua_State* pL) {
    Base::Vector3 Coordinate = Component::GetLastHitMonsterCoordinates();
    lua_pushnumber(pL, Coordinate.x);
    lua_pushnumber(pL, Coordinate.y);
    lua_pushnumber(pL, Coordinate.z);
    return 3;
}
static int Game_Monster_GetMonsterCNName(lua_State* pL) {
    int monsterId = (int)lua_tointeger(pL, -1);
    lua_pushstring(pL, Component::GetMonstersName_CN(monsterId).c_str());
    return 1;
}
static int Game_Environmental_SetFilter(lua_State* pL) {
    int id = (int)lua_tointeger(pL, 1);
    int subId = (int)lua_tointeger(pL, 2);
    Component::SetEnvironmentalFilter(id, subId);
    return 0;
}
static int Game_Environmental_DisableFilter(lua_State* pL) {
    Component::DisableEnvironmentalFilter();
    return 0;
}
static int Game_Environmental_SetAllEnvironmentalCoordinatesInRange(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    float min = (float)lua_tonumber(pL, 4);
    float max = (float)lua_tonumber(pL, 5);
    Component::SetAllEnvironmentalCoordinates(Base::Vector3(x,y,z), min, max);
    return 0;
}
static int Game_Player_CreateWeaponProjectiles(lua_State* pL) {
    int id = (int)lua_tointeger(pL, 1);
    float startx = (float)lua_tonumber(pL, 2);
    float starty = (float)lua_tonumber(pL, 3);
    float startz = (float)lua_tonumber(pL, 4);
    float endx = (float)lua_tonumber(pL, 5);
    float endy = (float)lua_tonumber(pL, 6);
    float endz = (float)lua_tonumber(pL, 7);
    lua_pushboolean(pL, Base::ProjectilesOperation::CreateProjectiles(
        id, Base::Vector3(startx, starty, startz), Base::Vector3(endx, endy, endz),0
    ));
    return 1;
}
static int Game_Player_CreateBowgunProjectiles(lua_State* pL) {
    int id = (int)lua_tointeger(pL, 1);
    float startx = (float)lua_tonumber(pL, 2);
    float starty = (float)lua_tonumber(pL, 3);
    float startz = (float)lua_tonumber(pL, 4);
    float endx = (float)lua_tonumber(pL, 5);
    float endy = (float)lua_tonumber(pL, 6);
    float endz = (float)lua_tonumber(pL, 7);
    lua_pushboolean(pL, Base::ProjectilesOperation::CreateProjectiles(
        id, Base::Vector3(startx, starty, startz), Base::Vector3(endx, endy, endz),1
    ));
    return 1;
}
static int Game_Monster_GetAllMonsterCoordinates(lua_State* pL)
{
    lua_newtable(pL);//����һ����񣬷���ջ��
    for (auto [id, monsterData] : Component::GetAllMonsterCoordinates()) {
        lua_pushinteger(pL, id);//ѹ����
        lua_newtable(pL);//ѹ������Ϣ��
        lua_pushstring(pL, "X");//X����
        lua_pushnumber(pL, monsterData.CoordinatesX);//value
        lua_settable(pL, -3);//����X����
        lua_pushstring(pL, "Y");//Y����
        lua_pushnumber(pL, monsterData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z����
        lua_pushnumber(pL, monsterData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//����Id
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//����SubId
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//����ָ��
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//����������
    }
    return 1;
}
static int Game_Monster_GetAllMonsterHealth(lua_State* pL)
{
    lua_newtable(pL);
    for (auto [id, monsterData] : Component::GetAllMonsterHealth()) {
        lua_pushinteger(pL, id);
        lua_newtable(pL);
        lua_pushstring(pL, "Health");
        lua_pushnumber(pL, monsterData.Health);
        lua_settable(pL, -3);
        lua_pushstring(pL, "MaxHealth");
        lua_pushnumber(pL, monsterData.MaxHealth);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//����ָ��
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);
    }
    return 1;
}
static int Game_Monster_GetAllMonsterDebuff(lua_State* pL)
{
    lua_newtable(pL);
    for (auto [id, monsterData] : Component::GetAllMonsterDeBuff()) {
        lua_pushinteger(pL, id);
        lua_newtable(pL);
        lua_pushstring(pL, "Debuff");
        lua_newtable(pL);
        for (string debuff : vector<string>{ "Covet","Dizziness","Paralysis","Sleep","Poisoning","Ride","Ridedowna","Reducebreath","Explode","Flicker","FlickerG","Smoke","Traphole","Stasistrap" }) {
            lua_pushstring(pL, debuff.c_str());
            lua_newtable(pL);
            lua_pushstring(pL, "State");
            lua_pushnumber(pL, monsterData.DeBuff[debuff].StateValue / monsterData.DeBuff[debuff].MaxStateValue);
            lua_settable(pL, -3);
            lua_pushstring(pL, "Recovery");
            lua_pushnumber(pL, monsterData.DeBuff[debuff].RecoveryValue / monsterData.DeBuff[debuff].MaxRecoveryValue);
            lua_settable(pL, -3);
            lua_settable(pL, -3);
        }
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//����ָ��
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);
    }
    return 1;
}
static int Game_Monster_GetAllMonsterCoordinatesInRange(lua_State* pL)
{
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_newtable(pL);//����һ����񣬷���ջ��
    for (auto [id, monsterData] : Component::GetAllMonsterCoordinatesRelativeToPlayers(min, max)) {
        lua_pushinteger(pL, id);//ѹ����
        lua_newtable(pL);//ѹ������Ϣ��
        lua_pushstring(pL, "X");//X����
        lua_pushnumber(pL, monsterData.CoordinatesX);//value
        lua_settable(pL, -3);//����X����
        lua_pushstring(pL, "Y");//Y����
        lua_pushnumber(pL, monsterData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z����
        lua_pushnumber(pL, monsterData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//����Id
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//����SubId
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//����ָ��
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//����������
    }
    return 1;
}
static int Game_Monster_GetAllMonsterHealthInRange(lua_State* pL)
{
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_newtable(pL);
    for (auto [id, monsterData] : Component::GetAllMonsterHealthRelativeToPlayers(min, max)) {
        lua_pushinteger(pL, id);
        lua_newtable(pL);
        lua_pushstring(pL, "Health");
        lua_pushnumber(pL, monsterData.Health);
        lua_settable(pL, -3);
        lua_pushstring(pL, "MaxHealth");
        lua_pushnumber(pL, monsterData.MaxHealth);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//����ָ��
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);
    }
    return 1;
}
static int Game_Monster_GetAllMonsterDebuffInRange(lua_State* pL)
{
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_newtable(pL);
    for (auto [id, monsterData] : Component::GetAllMonsterDeBuffRelativeToTarget(min, max)) {
        lua_pushinteger(pL, id);
        lua_newtable(pL);
        lua_pushstring(pL, "Debuff");
        lua_newtable(pL);
        for (string debuff : vector<string>{ "Covet","Dizziness","Paralysis","Sleep","Poisoning","Ride","Ridedowna","Reducebreath","Explode","Flicker","FlickerG","Smoke","Traphole","Stasistrap" }) {
            lua_pushstring(pL, debuff.c_str());
            lua_newtable(pL);
            lua_pushstring(pL, "State");
            lua_pushnumber(pL, monsterData.DeBuff[debuff].StateValue / monsterData.DeBuff[debuff].MaxStateValue);
            lua_settable(pL, -3);
            lua_pushstring(pL, "Recovery");
            lua_pushnumber(pL, monsterData.DeBuff[debuff].RecoveryValue / monsterData.DeBuff[debuff].MaxRecoveryValue);
            lua_settable(pL, -3);
            lua_settable(pL, -3);
        }
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//����ָ��
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);
    }
    return 1;
}
static int Game_Monster_GetAllMonsterCoordinatesInTargetPointRange(lua_State* pL)
{
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    float min = (float)lua_tonumber(pL, 4);
    float max = (float)lua_tonumber(pL, 5);
    lua_newtable(pL);//����һ����񣬷���ջ��
    for (auto [id, monsterData] : Component::GetAllMonsterCoordinatesRelativeToTarget(Base::Vector3(x,y,z),min, max)) {
        lua_pushinteger(pL, id);//ѹ����
        lua_newtable(pL);//ѹ������Ϣ��
        lua_pushstring(pL, "X");//X����
        lua_pushnumber(pL, monsterData.CoordinatesX);//value
        lua_settable(pL, -3);//����X����
        lua_pushstring(pL, "Y");//Y����
        lua_pushnumber(pL, monsterData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z����
        lua_pushnumber(pL, monsterData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//����Id
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//����SubId
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//����ָ��
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//����������
    }
    return 1;
}
static int Game_Monster_GetAllMonsterHealthInTargetPointRange(lua_State* pL)
{
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    float min = (float)lua_tonumber(pL, 4);
    float max = (float)lua_tonumber(pL, 5);
    lua_newtable(pL);
    for (auto [id, monsterData] : Component::GetAllMonsterHealthRelativeToTarget(Base::Vector3(x, y, z), min, max)) {
        lua_pushinteger(pL, id);
        lua_newtable(pL);
        lua_pushstring(pL, "Health");
        lua_pushnumber(pL, monsterData.Health);
        lua_settable(pL, -3);
        lua_pushstring(pL, "MaxHealth");
        lua_pushnumber(pL, monsterData.MaxHealth);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//����ָ��
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);
    }
    return 1;
}
static int Game_Monster_GetAllMonsterDebuffInTargetPointRange(lua_State* pL)
{
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    float min = (float)lua_tonumber(pL, 4);
    float max = (float)lua_tonumber(pL, 5);
    lua_newtable(pL);
    for (auto [id, monsterData] : Component::GetAllMonsterDeBuffRelativeToTarget(Base::Vector3(x, y, z), min, max)) {
        lua_pushinteger(pL, id);
        lua_newtable(pL);
            lua_pushstring(pL, "Debuff");
            lua_newtable(pL);
                for (string debuff : vector<string>{ "Covet","Dizziness","Paralysis","Sleep","Poisoning","Ride","Ridedowna","Reducebreath","Explode","Flicker","FlickerG","Smoke","Traphole","Stasistrap" }) {
                    lua_pushstring(pL, debuff.c_str());
                    lua_newtable(pL);
                        lua_pushstring(pL, "State");
                        lua_pushnumber(pL, monsterData.DeBuff[debuff].StateValue / monsterData.DeBuff[debuff].MaxStateValue);
                        lua_settable(pL, -3);
                        lua_pushstring(pL, "Recovery");
                        lua_pushnumber(pL, monsterData.DeBuff[debuff].RecoveryValue / monsterData.DeBuff[debuff].MaxRecoveryValue);
                        lua_settable(pL, -3);
                    lua_settable(pL, -3);
                }
            lua_settable(pL, -3);
        lua_pushstring(pL, "Id");
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//����ָ��
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);
    }
    return 1;
}
static int Game_Environmental_GetAllEnvironmentalCoordinatesInRange(lua_State* pL)
{
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_newtable(pL);//����һ����񣬷���ջ��
    for (auto [id, environmentalData] : Component::GetAllEnvironmentalCoordinates(min, max)) {
        lua_pushinteger(pL, id);//ѹ����
        lua_newtable(pL);//ѹ������Ϣ��
        lua_pushstring(pL, "X");//X����
        lua_pushnumber(pL, environmentalData.CoordinatesX);//value
        lua_settable(pL, -3);//����X����
        lua_pushstring(pL, "Y");//Y����
        lua_pushnumber(pL, environmentalData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z����
        lua_pushnumber(pL, environmentalData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//����Id
        lua_pushinteger(pL, environmentalData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//����SubId
        lua_pushinteger(pL, environmentalData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//����ָ��
        ostringstream ptr;
        ptr << environmentalData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//����������
    }
    return 1;
}
static int Game_Player_GetPlayerBuffDuration(lua_State* pL) {
    string buff = (string)lua_tostring(pL, -1);
    lua_pushnumber(pL, Base::PlayerData::GetPlayerBuff(buff));
    return 1;
}
static int Game_Player_SetPlayerBuffDuration(lua_State* pL) {
    string buff = (string)lua_tostring(pL, 1);
    float duration = (float)lua_tonumber(pL, 2);
    Base::PlayerData::SetPlayerBuff(buff, duration);
    return 0;
}
static int Game_Player_GetPlayerHookCoordinate(lua_State* pL) {
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Hook.x);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Hook.y);
    lua_pushnumber(pL, Base::PlayerData::Coordinate::Hook.z);
    return 3;
}
static int Game_Player_GetMonstersHateToPlayers(lua_State* pL) {
    lua_newtable(pL);
    vector<void*> Monster = Component::GetMonstersHateToPlayers();
    vector<void*>::iterator it = Monster.begin();
    for (; it != Monster.end(); ++it)
    {
        ostringstream ptr;
        ptr << *it;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
    }
    lua_settable(pL, -3);
    return 1;
}
static int Game_Player_SetHookCoordinateChange(lua_State* pL) {
    float x = (float)lua_tonumber(pL, 1);
    float y = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Component::SetHookCoordinateChange(Base::Vector3(x, y, z));
    return 0;
}
static int Game_Player_CancelHookCoordinateChange(lua_State* pL) {
    Base::PlayerData::HookChange = false;
    return 0;
}
static int Game_Player_GetPlayerVisualDistance(lua_State* pL) {
    void* VisualOffset = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7690);
    lua_pushnumber(pL, *offsetPtr<float>(VisualOffset, 0x5E8));
    return 1;
}
static int Game_Player_GetPlayerVisualHeight(lua_State* pL) {
    void* VisualOffset = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7690);
    lua_pushnumber(pL, *offsetPtr<float>(VisualOffset, 0x5E4));
    return 1;
}
static int Game_Player_SetPlayerVisualDistance(lua_State* pL) {
    float distance = (float)lua_tonumber(pL, -1);
    void* VisualOffset = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7690);
    *offsetPtr<float>(VisualOffset, 0x5E8) = distance;
    return 0;
}
static int Game_Player_SetPlayerVisualHeight(lua_State* pL) {
    float height = (float)lua_tonumber(pL, -1);
    void* VisualOffset = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7690);
    *offsetPtr<float>(VisualOffset, 0x5E4) = height;
    return 0;
}
static int Game_Entity_GetPlayerPtr(lua_State* pL) {
    ostringstream ptr;
    ptr << Base::BasicGameData::PlayerPlot;
    string ptrstr = ptr.str();
    lua_pushstring(pL, ptrstr.c_str());
    return 1;
}
static int Game_Entity_GetEntityProperties(lua_State* pL) {
    string entity = "0x" + (string)lua_tostring(pL, -1);
    Component::EntityProperties entityProperties = Component::GetEntityProperties(entity);
    lua_newtable(pL);
    lua_pushstring(pL, "Coordinate");
        lua_newtable(pL);
        lua_pushstring(pL, "x");
        lua_pushnumber(pL, entityProperties.Coordinate.x);
        lua_settable(pL, -3);
        lua_pushstring(pL, "y");
        lua_pushnumber(pL, entityProperties.Coordinate.y);
        lua_settable(pL, -3);
        lua_pushstring(pL, "z");
        lua_pushnumber(pL, entityProperties.Coordinate.z);
        lua_settable(pL, -3);
    lua_settable(pL, -3);

    lua_pushstring(pL, "Size");
        lua_newtable(pL);
        lua_pushstring(pL, "x");
        lua_pushnumber(pL, entityProperties.Size.x);
        lua_settable(pL, -3);
        lua_pushstring(pL, "y");
        lua_pushnumber(pL, entityProperties.Size.y);
        lua_settable(pL, -3);
        lua_pushstring(pL, "z");
        lua_pushnumber(pL, entityProperties.Size.z);
        lua_settable(pL, -3);
    lua_settable(pL, -3);

    lua_pushstring(pL, "Action");
        lua_newtable(pL);
        lua_pushstring(pL, "Id");
        lua_pushnumber(pL, entityProperties.Action.x);
        lua_settable(pL, -3);
        lua_pushstring(pL, "NowFrame");
        lua_pushnumber(pL, entityProperties.Action.y);
        lua_settable(pL, -3);
        lua_pushstring(pL, "EndFrame");
        lua_pushnumber(pL, entityProperties.Action.z);
        lua_settable(pL, -3);
    lua_settable(pL, -3);

    lua_pushstring(pL, "Angle");
    lua_pushnumber(pL, entityProperties.Angle);
    lua_settable(pL, -3);

    return 1;
}
static int Game_Entity_SetEntityCoordinate(lua_State* pL) {
    string entity = "0x" + (string)lua_tostring(pL, 1);
    float x = (float)lua_tonumber(pL, 2);
    float y = (float)lua_tonumber(pL, 3);
    float z = (float)lua_tonumber(pL, 4);
    Component::SetEntityCoordinate(entity, Base::Vector3(x, y, z));
    return 0;
}
static int Game_Entity_SetEntitySize(lua_State* pL) {
    string entity = "0x" + (string)lua_tostring(pL, 1);
    float x = (float)lua_tonumber(pL, 2);
    float y = (float)lua_tonumber(pL, 3);
    float z = (float)lua_tonumber(pL, 4);
    Component::SetEntitySize(entity, Base::Vector3(x, y, z));
    return 0;
}
static int Game_Entity_SetEntityActionFrame(lua_State* pL) {
    string entity = "0x" + (string)lua_tostring(pL, 1);
    float nowFrame = (float)lua_tonumber(pL, 2);
    Component::SetEntityActionFrame(entity, nowFrame);
    return 0;
}
static int Game_Entity_SetEntityAngle(lua_State* pL) {
    string entity = "0x" + (string)lua_tostring(pL, 1);
    float angle = (float)lua_tonumber(pL, 2);
    Component::SetEntityAngle(entity, angle);
    return 0;
}
static int Game_Entity_SetEntityAimCoordinate(lua_State* pL) {
    string entity = "0x" + (string)lua_tostring(pL, 1);
    float x = (float)lua_tonumber(pL, 2);
    float z = (float)lua_tonumber(pL, 3);
    Component::SetEntityAimCoordinate(entity, Base::Vector2(x,z));
    return 0;
}
static int Game_Entity_SetEntityFrameSpeed(lua_State* pL) {
    string entity = "0x" + (string)lua_tostring(pL, 1);
    float frameSpeed = (float)lua_tonumber(pL, 2);
    Component::SetEntityFrameSpeed(entity, frameSpeed);
    return 0;
}
static int Game_Entity_ClearEntityFrameSpeed(lua_State* pL) {
    Base::World::FrameSpeed.clear();
    return 0;
}
static int Game_Entity_BehaviorControl(lua_State* pL) {
    string entity = "0x" + (string)lua_tostring(pL, 1);
    int id = (int)lua_tointeger(pL, 2);
    Component::EntityBehaviorControl(entity, id);
    return 0;
}
#pragma endregion
#pragma region SystemFun
static int System_Keyboard_CheckKey(lua_State* pL) {    
    int key = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Base::Keyboard::CheckKey(key));
    return 1;
}
static int System_Keyboard_CheckDoubleKey(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Base::Keyboard::CheckKey(key, 2));
    return 1;
}
static int System_Keyboard_CheckKeyIsPressed(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    bool ret = GetKeyState(key) < 0;
    if (!Base::Keyboard::CheckWindows())
        ret = false;
    lua_pushboolean(pL, ret);
    return 1;
}
static int System_HotKey_AddHotKey(lua_State* pL) {
    string name = (string)lua_tostring(pL, 1);
    string describe = (string)lua_tostring(pL, 2);
    unsigned int key = (unsigned int)lua_tointeger(pL, 3);
    ImHotKey::AddHotKey(name.c_str(), describe.c_str(), key);
    return 0;
}
static int System_HotKey_CheckKey(lua_State* pL) {
    string name = (string)lua_tostring(pL, -1);
    if (ControlProgram::Checkhotkey.find(name) != ControlProgram::Checkhotkey.end()) {
        lua_pushboolean(pL, ControlProgram::Checkhotkey[name]);
        ControlProgram::Checkhotkey[name] = false;
    } else
    lua_pushboolean(pL, false);
    return 1;
}
static int System_Chronoscope_AddChronoscope(lua_State* pL) {
    float time = (float)lua_tonumber(pL, 1);
    string name = (string)lua_tostring(pL, 2);
    Base::Chronoscope::AddChronoscope(time, name, true);
    return 0;
}
static int System_Chronoscope_CheckPresenceChronoscope(lua_State* pL) {
    string name = (string)lua_tostring(pL, -1);
    lua_pushboolean(pL, Base::Chronoscope::CheckPresenceChronoscope(name));
    return 1;
}
static int System_Chronoscope_DelChronoscope(lua_State* pL) {
    string name = (string)lua_tostring(pL, -1);
    Base::Chronoscope::DelChronoscope(name);
    return 0;
}
static int System_Chronoscope_CheckChronoscope(lua_State* pL) {
    string name = (string)lua_tostring(pL, -1);
    lua_pushboolean(pL, Base::Chronoscope::CheckChronoscope(name));
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
static int System_XboxPad_CheckKey(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Base::XboxPad::CheckKey(key));
    return 1;
}
static int System_XboxPad_CheckDoubleKey(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    lua_pushboolean(pL, Base::XboxPad::CheckKey(key, 2));
    return 1;
}
static int System_XboxPad_CheckKeyIsPressed(lua_State* pL) {
    int key = (int)lua_tointeger(pL, -1);
    bool ret = Base::XboxPad::KeyIdHandle(key);
    lua_pushboolean(pL, ret);
    return 1;
}
static int System_LuaScript_Build(lua_State* pL) {
    lua_pushnumber(pL, Base::ModConfig::ModBuild);
    return 1;
}
static int System_LuaScript_Version(lua_State* pL) {
    lua_pushstring(pL, Base::ModConfig::ModVersion.c_str());
    return 1;
}
static int System_GetUUID(lua_State* pL) {
    lua_pushstring(pL, Base::Calculation::GetUUID().c_str());
    return 1;
}
static int System_DeBug_OpenDeBugConsole(lua_State* pL) {
    Base::ModConfig::ModConsole = true;
    return 0;
}
static int System_DeBug_CloseDeBugConsole(lua_State* pL) {
    Base::ModConfig::ModConsole = false;
    return 0;
}
static int System_Memory_GetOffsetAddress(lua_State* pL) {
    string ptr = "0x" + (string)lua_tostring(pL, 1);
    string offset = "0x" + (string)lua_tostring(pL, 2);
    //ptr����
    long long Ptr = 0;
    sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
    void* ptrAddress = (void*)Ptr;
    //offset����
    long long Offset = 0;
    sscanf_s(offset.c_str(), "%p", &Offset, sizeof(long long));

    if (ptrAddress != nullptr) {
        void* offsetAddress = *offsetPtr<undefined**>((undefined(*)())ptrAddress, Offset);
        ostringstream ostptr;
        ostptr << offsetAddress;
        string ptrstr = ostptr.str();
        lua_pushstring(pL, ptrstr.c_str());
    } else
        lua_pushstring(pL, "1");
    return 1;
}
static int System_Memory_GetAddressData(lua_State* pL) {
    string ptr = "0x" + (string)lua_tostring(pL, 1);
    string type = (string)lua_tostring(pL, 2);
    long long Ptr = 0;
    sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
    void* ptrAddress = (void*)Ptr;
    if (ptrAddress != nullptr) {
        if (type == "int")
            lua_pushinteger(pL, *(int*)(Ptr));
        else if (type == "float")
            lua_pushnumber(pL, *(float*)(Ptr));
        else if (type == "bool")
            lua_pushboolean(pL, *(bool*)(Ptr));
        else if (type == "byte")
            lua_pushinteger(pL, *(char*)(Ptr));
        else
            lua_pushinteger(pL, *(char*)(Ptr));
    } else
        lua_pushstring(pL, "Address error");
    return 1;
}
static int System_Memory_SetAddressData(lua_State* pL) {
    string ptr = "0x" + (string)lua_tostring(pL, 1);
    string type = (string)lua_tostring(pL, 2);
    long long Ptr = 0;
    sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
    void* ptrAddress = (void*)Ptr;
    if (ptrAddress != nullptr) {
        if (type == "int") {
            *(int*)(Ptr) = (int)lua_tointeger(pL, 3);
            lua_pushboolean(pL, true);
        }
        else if (type == "float") {
            *(float*)(Ptr) = (float)lua_tonumber(pL, 3);
            lua_pushboolean(pL, true);
        }
        else if (type == "bool") {
            *(bool*)(Ptr) = (bool)lua_toboolean(pL, 3);
            lua_pushboolean(pL, true);
        }
        else if (type == "byte") {
            *(char*)(Ptr) = (char)lua_tointeger(pL, 3);
            lua_pushboolean(pL, true);
        }
        else
            lua_pushboolean(pL, false);
    }
    else
        lua_pushboolean(pL, false);
    return 1;
}
static int System_UI_DrawImage(lua_State* pL) {
    string name = (string)lua_tostring(pL, 1);
    string img = (string)lua_tostring(pL, 2);
    float x = (float)lua_tonumber(pL, 3);
    float y = (float)lua_tonumber(pL, 4);
    Base::Vector3 Channel = Base::Vector3(1,1,1);
    float alpha = 1;
    if (lua_gettop(pL) > 4) {
        alpha = (float)lua_tonumber(pL, 5);
    }
    if (lua_gettop(pL) > 5) {
        Channel = Base::Vector3(
            (float)lua_tonumber(pL, 6),
            (float)lua_tonumber(pL, 7),
            (float)lua_tonumber(pL, 8)
        );
    }
    Base::Draw::Img[name] = Base::Draw::NewImage(alpha, Channel, Base::Vector2(x, y), name, img);
    return 0;
}
static int System_UI_DrawBase64Image(lua_State* pL) {
    string name = (string)lua_tostring(pL, 1);
    string img = (string)lua_tostring(pL, 2);
    float x = (float)lua_tonumber(pL, 3);
    float y = (float)lua_tonumber(pL, 4);
    int width = (float)lua_tointeger(pL, 5);
    int height = (float)lua_tointeger(pL, 6);
    Base::Vector3 Channel = Base::Vector3(1, 1, 1);
    float alpha = 1;
    if (lua_gettop(pL) > 6) {
        alpha = (float)lua_tonumber(pL, 7);
    }
    if (lua_gettop(pL) > 7) {
        Channel = Base::Vector3(
            (float)lua_tonumber(pL, 8),
            (float)lua_tonumber(pL, 9),
            (float)lua_tonumber(pL, 10)
        );
    }
    Base::Draw::Img[name] = Base::Draw::NewImage(alpha, Channel, Base::Vector2(x, y), name, img, true, width, height);
    return 0;
}
static int System_UI_RemoveImage(lua_State* pL) {
    string name = (string)lua_tostring(pL, 1);
    Base::Draw::Img.erase(name);
    return 0;
}
static int System_UI_DrawText(lua_State* pL) {
    string name = (string)lua_tostring(pL, 1);
    string text = (string)lua_tostring(pL, 2);
    float x = (float)lua_tonumber(pL, 3);
    float y = (float)lua_tonumber(pL, 4);
    Base::Vector3 color = Base::Vector3(1,1,1);
    float alpha = 1;
    float size = 1;
    if (lua_gettop(pL) > 4) {
        size = (float)lua_tonumber(pL, 5);
    }
    if (lua_gettop(pL) > 5) {
        alpha = (float)lua_tonumber(pL, 6);
    }
    if (lua_gettop(pL) > 6) {
        color = Base::Vector3(
            (float)lua_tonumber(pL, 7),
            (float)lua_tonumber(pL, 8),
            (float)lua_tonumber(pL, 9)
        );
    }
    Base::Draw::Text[name] = Base::Draw::NewText(alpha,color,Base::Vector2(x,y),name,text,size);
    return 0;
}
static int System_UI_RemoveText(lua_State* pL) {
    string name = (string)lua_tostring(pL, 1);
    Base::Draw::Text.erase(name);
    return 0;
}

#pragma endregion
#pragma region LuaFun
//������������
static int Lua_Variable_SaveIntVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 1);
    int variableValue = (int)lua_tointeger(pL, 2);
    LuaData::IntVariable[variableName] = variableValue;
    return 0;
}
//����ȫ����������
static int Lua_Variable_SaveGlobalIntVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, 1);
    int variableValue = (int)lua_tointeger(pL, 2);
    LuaData::IntVariable[variableName] = variableValue;
    return 0;
}
//���븡��������
static int Lua_Variable_SaveFloatVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 1);
    float variableValue = (float)lua_tonumber(pL, 2);
    LuaData::FloatVariable[variableName] = variableValue;
    return 0;
}
//����ȫ�ָ���������
static int Lua_Variable_SaveGlobalFloatVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, 1);
    float variableValue = (float)lua_tonumber(pL, 2);
    LuaData::FloatVariable[variableName] = variableValue;
    return 0;
}
//�����ַ�������
static int Lua_Variable_SaveStringVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 1);
    string variableValue = (string)lua_tostring(pL, 2);
    LuaData::StringVariable[variableName] = variableValue;
    return 0;
}
//����ȫ���ַ�������
static int Lua_Variable_SaveGlobalStringVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, 1);
    string variableValue = (string)lua_tostring(pL, 2);
    LuaData::StringVariable[variableName] = variableValue;
    return 0;
}
//��ȡ��������
static int Lua_Variable_ReadIntVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, -1);
    int ret;
    if (LuaData::IntVariable.find(variableName) == LuaData::IntVariable.end())
        ret = 0;
    else
        ret = LuaData::IntVariable[variableName];
    lua_pushinteger(pL, ret);
    return 1;
}
//��ȡȫ����������
static int Lua_Variable_ReadGlobalIntVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, -1);
    int ret;
    if (LuaData::IntVariable.find(variableName) == LuaData::IntVariable.end())
        ret = 0;
    else
        ret = LuaData::IntVariable[variableName];
    lua_pushinteger(pL, ret);
    return 1;
}
//��ȡ����������
static int Lua_Variable_ReadFloatVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, -1);
    float ret;
    if (LuaData::FloatVariable.find(variableName) == LuaData::FloatVariable.end())
        ret = 0;
    else
        ret = LuaData::FloatVariable[variableName];
    lua_pushnumber(pL, ret);
    return 1;
}
//��ȡȫ�ָ���������
static int Lua_Variable_ReadGlobalFloatVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, -1);
    float ret;
    if (LuaData::FloatVariable.find(variableName) == LuaData::FloatVariable.end())
        ret = 0;
    else
        ret = LuaData::FloatVariable[variableName];
    lua_pushnumber(pL, ret);
    return 1;
}
//��ȡ�ַ�������
static int Lua_Variable_ReadStringVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, -1);
    string ret;
    if (LuaData::StringVariable.find(variableName) == LuaData::StringVariable.end())
        ret = "";
    else
        ret = LuaData::StringVariable[variableName];
    lua_pushstring(pL, ret.c_str());
    return 1;
}
//��ȡȫ���ַ�������
static int Lua_Variable_ReadGlobalStringVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, -1);
    string ret;
    if (LuaData::StringVariable.find(variableName) == LuaData::StringVariable.end())
        ret = "";
    else
        ret = LuaData::StringVariable[variableName];
    lua_pushstring(pL, ret.c_str());
    return 1;
}
//���ٱ���
static int Lua_Variable_DestroyVariable(lua_State* pL) {
    string variableTpye = (string)lua_tostring(pL, 1);
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 2);
    if (variableTpye == "Int")
        LuaData::IntVariable.erase(variableName);
    else if (variableTpye == "Float")
        LuaData::FloatVariable.erase(variableName);
    else if (variableTpye == "String")
        LuaData::StringVariable.erase(variableName);
    return 0;
}
//����ȫ�ֱ���
static int Lua_Variable_DestroyGlobalVariable(lua_State* pL) {
    string variableTpye = "G_" + (string)lua_tostring(pL, 1);
    string variableName = (string)lua_tostring(pL, 2);
    if (variableTpye == "Int")
        LuaData::IntVariable.erase(variableName);
    else if (variableTpye == "Float")
        LuaData::FloatVariable.erase(variableName);
    else if (variableTpye == "String")
        LuaData::StringVariable.erase(variableName);
    return 0;
}
//�����ӽű�����ǰ׺
static int Lua_Variable_SetSubScriptVariablePrefix(lua_State* pL) {
    string variablePrefix = (string)lua_tostring(pL, -1);
    Sublua = variablePrefix;
    return 0;
}
//��ȡ�����
static int Lua_Math_Rander(lua_State* pL) {
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_pushnumber(pL, Base::Calculation::myRander(min, max));
    return 1;
}
//��ȡ��������
static int Lua_Http_GetHttpData(lua_State* pL) {
    string httpUrl = (string)lua_tostring(pL, -1);
    lua_pushstring(pL, NetworkServer::GetHttpData(httpUrl).c_str());
    return 1;
}
//���ӵ�WS������
static int Lua_WS_LinkWSServer(lua_State* pL) {
    string WSSLink = (string)lua_tostring(pL, -1);
    NetworkServer::LinkWS(WSSLink);
    return 0;
}
//������Ϣ��WS������
static int Lua_WS_SendMessage(lua_State* pL) {
    string Message = (string)lua_tostring(pL, -1);
    NetworkServer::WSSendMessage(Message);
    return 0;
}
//�ӷ�������Ϣ��ջ�н���һ����Ϣ������
static int Lua_WS_GetMessage(lua_State* pL) {
    if (!NetworkServer::MessageCache.empty()) {
        lua_pushstring(pL, NetworkServer::MessageCache.front().c_str());
        NetworkServer::MessageCache.pop();
    }
    else 
        lua_pushstring(pL, "");
    return 1;
}
//�ӷ�������Ϣ��ջ�н���һ����Ϣ������
static int Lua_WS_GetLinkState(lua_State* pL) {
    lua_pushboolean(pL, NetworkServer::WSState());
    return 1;
}
//¼��ű�������Ϣ
static int Lua_About(lua_State* pL) {
    string About = (string)lua_tostring(pL, -1);
    Base::Draw::About[Nowlua] = About;
    return 0;
}
#pragma endregion
//==============================================
// Handling error
//==============================================
//����ص�
int LuaErrorCallBack(lua_State *L)
{
    lua_Debug debug = {};
    //���������ĵĵ��ò㼶
    int rank = 0;
    //����ȡlua�׳��Ĵ���ֱ����ȡ��
    while (lua_getstack(L, rank, &debug)) {
        rank++;
    }
    //�ж�ջ���Ƿ�Ϊ�ַ�������
    int type = lua_type(L, -1);
    if (type != 4)
        return 0;
    std::string error = lua_tostring(L, -1);
    std::string errorShort = debug.short_src;
    int errorLine = debug.currentline;
    std::string errorMsg = "error:" + error + ",errorShort:" + errorShort
        + ",line:" + std::to_string(errorLine);
    //��������Ϣѹ��ջ
    lua_pushstring(L, errorMsg.c_str());
    return 1;
}
int LuaErrorRecord(string error) {
    vector<string>::iterator it;
    for (it = Base::LuaHandle::LuaError.begin(); it != Base::LuaHandle::LuaError.end(); it++)
    {
        if (*it == error) return 0;
    }
    Base::LuaHandle::LuaError.push_back(error);

    return 1;
}
//==============================================
// Main Functions
//==============================================
int Lua_Main(string LuaFile)
{
    lua_State* L = luaL_newstate();
    //luaopen_base(L);
    luaL_openlibs(L);

#pragma region Game
    #pragma region Player
    //��ȡ�������
    lua_register(L, "Game_Player_GetPlayerCoordinate", Game_Player_GetPlayerCoordinate);
    //�����������
    lua_register(L, "Game_Player_SetPlayerCoordinate", Game_Player_SetPlayerCoordinate);
    //��ȡ׼������
    lua_register(L, "Game_Player_GetPlayerCollimatorCoordinate", Game_Player_GetPlayerCollimatorCoordinate);
    //��ȡ������׼������
    lua_register(L, "Game_Player_GetPlayerParabolaCollimatorCoordinate", Game_Player_GetPlayerParabolaCollimatorCoordinate);
    //��ȡ��������
    lua_register(L, "Game_Player_GetPlayerWeaponCoordinate", Game_Player_GetPlayerWeaponCoordinate);
    //�����׼״̬
    lua_register(L, "Game_Player_CheckAimingStatus", Game_Player_CheckAimingStatus);
    //��ȡ��������
    lua_register(L, "Game_Player_GetPlayerIncrementCoordinate", Game_Player_GetPlayerIncrementCoordinate);
    //��ȡ��������
    lua_register(L, "Game_Player_GetPlayerNavigationCoordinate", Game_Player_GetPlayerNavigationCoordinate);
    //��ȡ�������
    lua_register(L, "Game_Player_GetPlayerVisualCoordinate", Game_Player_GetPlayerVisualCoordinate);
    //����������꣨xyz�ͳ���ʱ��4��������
    lua_register(L, "Game_Player_SetPlayerVisualCoordinate", Game_Player_SetPlayerVisualCoordinate);
    //�����������
    lua_register(L, "Game_Player_UnbindPlayerVisualCoordinate", Game_Player_UnbindPlayerVisualCoordinate);
    //��ȡ�������
    lua_register(L, "Game_Player_GetPlayerVisualDistance", Game_Player_GetPlayerVisualDistance);
    //��ȡ����߶�
    lua_register(L, "Game_Player_GetPlayerVisualHeight", Game_Player_GetPlayerVisualHeight);
    //�����������
    lua_register(L, "Game_Player_SetPlayerVisualDistance", Game_Player_SetPlayerVisualDistance);
    //��������߶�
    lua_register(L, "Game_Player_SetPlayerVisualHeight", Game_Player_SetPlayerVisualHeight);
    //��ȡ��Ҷ���id
    lua_register(L, "Game_Player_GetPlayerActionId", Game_Player_GetPlayerActionId);
    //��ȡ����Ƕ�
    lua_register(L, "Game_Player_GetPlayerAngle", Game_Player_GetPlayerAngle);
    //���ó���Ƕ�
    lua_register(L, "Game_Player_SetPlayerAngle", Game_Player_SetPlayerAngle);
    //���ó�������
    lua_register(L, "Game_Player_SetPlayerAimToCoordinate", Game_Player_SetPlayerAimToCoordinate);
    //��ȡ����������ٶ�
    lua_register(L, "Game_Player_GetPlayerGravity", Game_Player_GetPlayerGravity);
    //��ȡ��������ٶ�
    lua_register(L, "Game_Player_GetPlayerFallSpeedRate", Game_Player_GetPlayerFallSpeedRate);
    //��������������ٶ�
    lua_register(L, "Game_Player_SetPlayerGravity", Game_Player_SetPlayerGravity);
    //������������ٶ�
    lua_register(L, "Game_Player_SetPlayerFallSpeedRate", Game_Player_SetPlayerFallSpeedRate);
    //��ȡ��ҿ���״̬
    lua_register(L, "Game_Player_CheckPlayerAirState", Game_Player_CheckPlayerAirState);
    //�����Ч
    lua_register(L, "Game_Player_AddEffect", Game_Player_AddEffect);

    //��ȡ�������Id
    lua_register(L, "Game_Player_Weapon_GetWeaponId", Game_Player_Weapon_GetWeaponId);
    //��ȡ�����������
    lua_register(L, "Game_Player_Weapon_GetWeaponType", Game_Player_Weapon_GetWeaponType);
    //������ҵ�����
    lua_register(L, "Game_Player_Weapon_ChangeWeapons", Game_Player_Weapon_ChangeWeapons);
    //��ȫ������ҵ�����
    lua_register(L, "Game_Player_Weapon_CompleteChangeWeapons", Game_Player_Weapon_CompleteChangeWeapons);
    //��ȡ�������װ��������
    lua_register(L, "Game_Player_Weapon_GetOrnamentsCoordinate", Game_Player_Weapon_GetOrnamentsCoordinate);
    //��ȡ�������װ����ģ�ʹ�С
    lua_register(L, "Game_Player_Weapon_GetOrnamentsSize", Game_Player_Weapon_GetOrnamentsSize);
    //�����������װ��������
    lua_register(L, "Game_Player_Weapon_SetOrnamentsCoordinate", Game_Player_Weapon_SetOrnamentsCoordinate);
    //�����������װ����ģ�ʹ�С
    lua_register(L, "Game_Player_Weapon_SetOrnamentsSize", Game_Player_Weapon_SetOrnamentsSize);
    //����������װ������������
    lua_register(L, "Game_Player_Weapon_DecontrolOrnamentsCoordinate", Game_Player_Weapon_DecontrolOrnamentsCoordinate);
    //����������װ����ģ�ʹ�С����
    lua_register(L, "Game_Player_Weapon_DecontrolOrnamentsSize", Game_Player_Weapon_DecontrolOrnamentsSize);
    //��ȡ�������������
    lua_register(L, "Game_Player_Weapon_GetMainWeaponCoordinate", Game_Player_Weapon_GetMainWeaponCoordinate);
    //��ȡ���������ģ�ʹ�С
    lua_register(L, "Game_Player_Weapon_GetMainWeaponSize", Game_Player_Weapon_GetMainWeaponSize);
    //�����������������
    lua_register(L, "Game_Player_Weapon_SetMainWeaponCoordinate", Game_Player_Weapon_SetMainWeaponCoordinate);
    //�������������ģ�ʹ�С
    lua_register(L, "Game_Player_Weapon_SetMainWeaponSize", Game_Player_Weapon_SetMainWeaponSize);
    //��������������������
    lua_register(L, "Game_Player_Weapon_DecontrolMainWeaponCoordinate", Game_Player_Weapon_DecontrolMainWeaponCoordinate);
    //������������ģ�ʹ�С����
    lua_register(L, "Game_Player_Weapon_DecontrolMainWeaponSize", Game_Player_Weapon_DecontrolMainWeaponSize);
    //��ȡ��Ҹ���������
    lua_register(L, "Game_Player_Weapon_GetSecondaryWeaponCoordinate", Game_Player_Weapon_GetSecondaryWeaponCoordinate);
    //��ȡ��Ҹ�����ģ�ʹ�С
    lua_register(L, "Game_Player_Weapon_GetSecondaryWeaponSize", Game_Player_Weapon_GetSecondaryWeaponSize);
    //������Ҹ���������
    lua_register(L, "Game_Player_Weapon_SetSecondaryWeaponCoordinate", Game_Player_Weapon_SetSecondaryWeaponCoordinate);
    //������Ҹ�����ģ�ʹ�С
    lua_register(L, "Game_Player_Weapon_SetSecondaryWeaponSize", Game_Player_Weapon_SetSecondaryWeaponSize);
    //�����Ҹ�������������
    lua_register(L, "Game_Player_Weapon_DecontrolSecondaryWeaponCoordinate", Game_Player_Weapon_DecontrolSecondaryWeaponCoordinate);
    //�����Ҹ�����ģ�ʹ�С����
    lua_register(L, "Game_Player_Weapon_DecontrolSecondaryWeaponSize", Game_Player_Weapon_DecontrolSecondaryWeaponSize);
    //��ȡ�������������ֵ(������)
    lua_register(L, "Game_Player_Weapon_CharacteristicIntValue", Game_Player_Weapon_CharacteristicIntValue);
    //��ȡ�������������ֵ(������)
    lua_register(L, "Game_Player_Weapon_CharacteristicFloatValue", Game_Player_Weapon_CharacteristicFloatValue);
    //��ȡ�������������ֵ(�ֽ�)
    lua_register(L, "Game_Player_Weapon_CharacteristicByteValue", Game_Player_Weapon_CharacteristicByteValue);
    //��ȡ�������������е�����
    lua_register(L, "Game_Player_Weapon_GetHitCoordinate", Game_Player_Weapon_GetHitCoordinate);
    //��ȡ�������������еĹ����ַ
    lua_register(L, "Game_Player_Weapon_GetAttackMonster", Game_Player_Weapon_GetAttackMonster);

    //��ȡ���������Ϣ
    lua_register(L, "Game_Player_GetFsmData", Game_Player_GetFsmData);
    //ִ��ָ������������
    lua_register(L, "Game_Player_RunFsmAction", Game_Player_RunFsmAction);
    //���ִ�е����������Ƿ����
    lua_register(L, "Game_Player_CheckRunFsmActionOver", Game_Player_CheckRunFsmActionOver);
    //ִ��ָ������������
    lua_register(L, "Game_Player_RunLmtAction", Game_Player_RunLmtAction);
    //��ȡ��ǰ����֡
    lua_register(L, "Game_Player_GetActionFrame", Game_Player_GetActionFrame);
    //���õ�ǰ����֡
    lua_register(L, "Game_Player_SetActionFrame", Game_Player_SetActionFrame);
    //���õ�ǰ����֡����
    lua_register(L, "Game_Player_SetActionFrameSpeed", Game_Player_SetActionFrameSpeed);
    //��ȡ���Ѫ����Ϣ
    lua_register(L, "Game_Player_GetPlayerHealth", Game_Player_GetPlayerHealth);
    //������ҵ�ǰѪ��
    lua_register(L, "Game_Player_SetPlayerCurrentHealth", Game_Player_SetPlayerCurrentHealth);
    //������һ���Ѫ��
    lua_register(L, "Game_Player_SetPlayerBasicHealth", Game_Player_SetPlayerBasicHealth);
    //��ȡ���������Ϣ
    lua_register(L, "Game_Player_GetPlayerEndurance", Game_Player_GetPlayerEndurance);
    //������ҵ�ǰ����
    lua_register(L, "Game_Player_SetPlayerCurrentEndurance", Game_Player_SetPlayerCurrentEndurance);
    //��������������
    lua_register(L, "Game_Player_SetPlayerMaxEndurance", Game_Player_SetPlayerMaxEndurance);
    //��ȡ��ҽ�ɫ��Ϣ
    lua_register(L, "Game_Player_GetPlayerRoleInfo", Game_Player_GetPlayerRoleInfo);
    //�����������Ͷ����
    lua_register(L, "Game_Player_CreateWeaponProjectiles", Game_Player_CreateWeaponProjectiles);
    //�����������Ͷ����
    lua_register(L, "Game_Player_CreateBowgunProjectiles", Game_Player_CreateBowgunProjectiles);
    //��ȡ���Buffʣ��ʱ��
    lua_register(L, "Game_Player_GetPlayerBuffDuration", Game_Player_GetPlayerBuffDuration);
    //�������Buffʣ��ʱ��
    lua_register(L, "Game_Player_SetPlayerBuffDuration", Game_Player_SetPlayerBuffDuration);
    //��ȡ��ҹ�צ����
    lua_register(L, "Game_Player_GetPlayerHookCoordinate", Game_Player_GetPlayerHookCoordinate);
    //��ȡ����ҳ�޵Ĺ���
    lua_register(L, "Game_Player_GetMonstersHateToPlayers", Game_Player_GetMonstersHateToPlayers);
    //���ù�צ���������
    lua_register(L, "Game_Player_SetHookCoordinateChange", Game_Player_SetHookCoordinateChange);
    //ȡ����צ�������������
    lua_register(L, "Game_Player_CancelHookCoordinateChange", Game_Player_CancelHookCoordinateChange);
    
    #pragma endregion
    //��ȡ��ǰ��ͼId
    lua_register(L, "Game_World_GetMapId", Game_World_GetMapId);
    //��ȡ������Ϣ
    lua_register(L, "Game_World_Message", Game_World_Message);
    #pragma region Monster
    //���ù���ɸѡ��
    lua_register(L, "Game_Monster_SetFilter", Game_Monster_SetFilter);
    //�������ɸѡ��
    lua_register(L, "Game_Monster_DisableFilter", Game_Monster_DisableFilter);
    //���Ƶ����������Ϊ
    lua_register(L, "Game_Monster_SetBehaviorOfNavigationMonsters", Game_Monster_SetBehaviorOfNavigationMonsters);
    //ɱ��������ǵĹ���
    lua_register(L, "Game_Monster_KillNavigationMarkMonster", Game_Monster_KillNavigationMarkMonster);
    //��������ǵĹ��������쳣״̬
    lua_register(L, "Game_Monster_AddDebuffToNavigationMarkMonster", Game_Monster_AddDebuffToNavigationMarkMonster);
    //���ƾ�������Ĺ������Ϊ
    lua_register(L, "Game_Monster_SetBehaviorOfNearestMonsters", Game_Monster_SetBehaviorOfNearestMonsters);
    //ɱ����������Ĺ���
    lua_register(L, "Game_Monster_KillNearestMonster", Game_Monster_KillNearestMonster);
    //ɱ����Χ�ھ�������Ĺ���
    lua_register(L, "Game_Monster_KillNearestMonsterInRange", Game_Monster_KillNearestMonsterInRange);
    //����������Ĺ��������쳣״̬
    lua_register(L, "Game_Monster_AddDebuffNearestMonster", Game_Monster_AddDebuffNearestMonster);
    //����Χ�ھ�������Ĺ��������쳣״̬
    lua_register(L, "Game_Monster_AddDebuffNearestMonsterInRange", Game_Monster_AddDebuffNearestMonsterInRange);
    //�������һ�λ��еĹ������Ϊ
    lua_register(L, "Game_Monster_SetBehaviorOfLastHitMonsters", Game_Monster_SetBehaviorOfLastHitMonsters);
    //ɱ�����һ�λ��еĹ���
    lua_register(L, "Game_Monster_KillLastHitMonster", Game_Monster_KillLastHitMonster);
    //�����һ�λ��еĹ��������쳣״̬
    lua_register(L, "Game_Monster_AddDebuffLastHitMonster", Game_Monster_AddDebuffLastHitMonster);
    //ɱ����Χ�����й���
    lua_register(L, "Game_Monster_KillAllMonsterInRange", Game_Monster_KillAllMonsterInRange);
    //����Χ�����й��������쳣״̬
    lua_register(L, "Game_Monster_AddDebuffToAllMonsterInRange", Game_Monster_AddDebuffToAllMonsterInRange);
    //��ȡ�����Ĺ��������
    lua_register(L, "Game_Monster_GetNavigationMonsterCoordinates", Game_Monster_GetNavigationMonsterCoordinates);
    //��ȡ��������Ĺ��������
    lua_register(L, "Game_Monster_GetNearestMonsterCoordinates", Game_Monster_GetNearestMonsterCoordinates);
    //��ȡ���һ�λ��еĹ��������
    lua_register(L, "Game_Monster_GetLastHitMonsterCoordinates", Game_Monster_GetLastHitMonsterCoordinates);
    //��ȡ���й��������
    lua_register(L, "Game_Monster_GetAllMonsterCoordinates", Game_Monster_GetAllMonsterCoordinates);
    //��ȡ���й��������
    lua_register(L, "Game_Monster_GetAllMonsterHealth", Game_Monster_GetAllMonsterHealth);
    //��ȡ���й�����쳣״̬
    lua_register(L, "Game_Monster_GetAllMonsterDebuff", Game_Monster_GetAllMonsterDebuff);
    //��ȡ��Χ�����й��������
    lua_register(L, "Game_Monster_GetAllMonsterCoordinatesInRange", Game_Monster_GetAllMonsterCoordinatesInRange);
    //��ȡ��Χ�����й��������
    lua_register(L, "Game_Monster_GetAllMonsterHealthInRange", Game_Monster_GetAllMonsterHealthInRange);
    //��ȡ��Χ�����й�����쳣״̬(�ƻ���)
    lua_register(L, "Game_Monster_GetAllMonsterDebuffInRange", Game_Monster_GetAllMonsterDebuffInRange);
    //��ȡĿ��㷶Χ�����й��������
    lua_register(L, "Game_Monster_GetAllMonsterCoordinatesInTargetPointRange", Game_Monster_GetAllMonsterCoordinatesInTargetPointRange);
    //��ȡĿ��㷶Χ�����й��������
    lua_register(L, "Game_Monster_GetAllMonsterHealthInTargetPointRange", Game_Monster_GetAllMonsterHealthInTargetPointRange);
    //��ȡĿ��㷶Χ�����й�����쳣״̬(�ƻ���)
    lua_register(L, "Game_Monster_GetAllMonsterDebuffInTargetPointRange", Game_Monster_GetAllMonsterDebuffInTargetPointRange);
    //��ȡָ��id�����������
    lua_register(L, "Game_Monster_GetMonsterCNName", Game_Monster_GetMonsterCNName);
    #pragma endregion
    #pragma region Environmental
    //���û�������ɸѡ��
    lua_register(L, "Game_Environmental_SetFilter", Game_Environmental_SetFilter);
    //�����������ɸѡ��
    lua_register(L, "Game_Environmental_DisableFilter", Game_Environmental_DisableFilter);
    //���÷�Χ�����л������������
    lua_register(L, "Game_Environmental_SetAllEnvironmentalCoordinatesInRange", Game_Environmental_SetAllEnvironmentalCoordinatesInRange);
    //��ȡ��Χ�����л������������
    lua_register(L, "Game_Environmental_GetAllEnvironmentalCoordinatesInRange", Game_Environmental_GetAllEnvironmentalCoordinatesInRange);
    #pragma endregion
    #pragma region Entity
    //��ȡʵ������
    lua_register(L, "Game_Entity_GetEntityProperties", Game_Entity_GetEntityProperties);
    //����ʵ������
    lua_register(L, "Game_Entity_SetEntityCoordinate", Game_Entity_SetEntityCoordinate);
    //����ʵ��ģ�ʹ�С
    lua_register(L, "Game_Entity_SetEntitySize", Game_Entity_SetEntitySize);
    //����ʵ�嵱ǰ����֡
    lua_register(L, "Game_Entity_SetEntityActionFrame", Game_Entity_SetEntityActionFrame);
    //����ʵ�峯��Ƕ�
    lua_register(L, "Game_Entity_SetEntityAngle", Game_Entity_SetEntityAngle);
    //��ʵ�峯��ָ��������
    lua_register(L, "Game_Entity_SetEntityAimCoordinate", Game_Entity_SetEntityAimCoordinate);
    //��ʵ�嶯��֡����
    lua_register(L, "Game_Entity_SetEntityFrameSpeed", Game_Entity_SetEntityFrameSpeed);
    //���ȫ��ʵ�嶯��֡��������
    lua_register(L, "Game_Entity_ClearEntityFrameSpeed", Game_Entity_ClearEntityFrameSpeed);
    //ʹʵ��ִ�ж���
    lua_register(L, "Game_Entity_BehaviorControl", Game_Entity_BehaviorControl);
    #pragma endregion
    
#pragma endregion
#pragma region System
    //��鰴��
    lua_register(L, "System_Keyboard_CheckKey", System_Keyboard_CheckKey);
    //��鰴��˫��
    lua_register(L, "System_Keyboard_CheckDoubleKey", System_Keyboard_CheckDoubleKey);
    //��鰴���Ƿ��ڰ���״̬
    lua_register(L, "System_Keyboard_CheckKeyIsPressed", System_Keyboard_CheckKeyIsPressed);
    //ע���ݼ�
    lua_register(L, "System_HotKey_AddHotKey", System_HotKey_AddHotKey);
    //����ݼ�
    lua_register(L, "System_HotKey_CheckKey", System_HotKey_CheckKey);
    //���Xbox����
    lua_register(L, "System_XboxPad_CheckKey", System_XboxPad_CheckKey);
    //���Xbox����˫��
    lua_register(L, "System_XboxPad_CheckDoubleKey", System_XboxPad_CheckDoubleKey);
    //���Xbox�����Ƿ��ڰ���״̬
    lua_register(L, "System_XboxPad_CheckKeyIsPressed", System_XboxPad_CheckKeyIsPressed);
    //��Ӽ�ʱ��
    lua_register(L, "System_Chronoscope_AddChronoscope", System_Chronoscope_AddChronoscope);
    //����ʱ��
    lua_register(L, "System_Chronoscope_CheckChronoscope", System_Chronoscope_CheckChronoscope);
    //����ʱ���Ƿ����
    lua_register(L, "System_Chronoscope_CheckPresenceChronoscope", System_Chronoscope_CheckPresenceChronoscope);
    //ɾ����ʱ��
    lua_register(L, "System_Chronoscope_DelChronoscope", System_Chronoscope_DelChronoscope);
    //����Ϸ�ڷ�����Ϣ
    lua_register(L, "System_Message_ShowMessage", System_Message_ShowMessage);
    //�����̨������Ϣ
    lua_register(L, "System_Console_Info", System_Console_Info);
    //�����̨���ʹ�����Ϣ
    lua_register(L, "System_Console_Error", System_Console_Error);
    //��ȡLuaScript��������汾
    lua_register(L, "System_LuaScript_Build", System_LuaScript_Build);
    //��ȡLuaScript��������汾
    lua_register(L, "System_LuaScript_Version", System_LuaScript_Version);
    //��ȡUUID
    lua_register(L, "System_GetUUID", System_GetUUID);
    //�򿪵��Կ���̨
    lua_register(L, "System_DeBug_OpenDeBugConsole", System_DeBug_OpenDeBugConsole);
    //�رյ��Կ���̨
    lua_register(L, "System_DeBug_CloseDeBugConsole", System_DeBug_CloseDeBugConsole);
    //��ȡƫ���ڴ��ַ
    lua_register(L, "System_Memory_GetOffsetAddress", System_Memory_GetOffsetAddress);
    //��ȡ�ڴ��ַ����
    lua_register(L, "System_Memory_GetAddressData", System_Memory_GetAddressData);
    //��ȡ�ڴ��ַ����
    lua_register(L, "System_Memory_SetAddressData", System_Memory_SetAddressData);
    //����Ļ���ͼƬ
    lua_register(L, "System_UI_DrawImage", System_UI_DrawImage);
    //����Ļ���Base64ͼƬ
    lua_register(L, "System_UI_DrawBase64Image", System_UI_DrawBase64Image);
    //�Ƴ���ӵ�ͼƬ
    lua_register(L, "System_UI_RemoveImage", System_UI_RemoveImage);
    //����Ļ�������
    lua_register(L, "System_UI_DrawText", System_UI_DrawText);
    //�Ƴ���ӵ�����
    lua_register(L, "System_UI_RemoveText", System_UI_RemoveText);
#pragma endregion
#pragma region Lua
    //������������
    lua_register(L, "Lua_Variable_SaveIntVariable", Lua_Variable_SaveIntVariable);
    //���븡��������
    lua_register(L, "Lua_Variable_SaveFloatVariable", Lua_Variable_SaveFloatVariable);
    //�����ַ�������
    lua_register(L, "Lua_Variable_SaveStringVariable", Lua_Variable_SaveStringVariable);
    //��ȡ��������
    lua_register(L, "Lua_Variable_ReadIntVariable", Lua_Variable_ReadIntVariable);
    //��ȡ����������
    lua_register(L, "Lua_Variable_ReadFloatVariable", Lua_Variable_ReadFloatVariable);
    //��ȡ�ַ�������
    lua_register(L, "Lua_Variable_ReadStringVariable", Lua_Variable_ReadStringVariable);
    //���ٱ���
    lua_register(L, "Lua_Variable_DestroyVariable", Lua_Variable_DestroyVariable);
    //�����ӽű�������
    lua_register(L, "Lua_Variable_SetSubScriptVariablePrefix", Lua_Variable_SetSubScriptVariablePrefix);
    //��ȡ�����
    lua_register(L, "Lua_Math_Rander", Lua_Math_Rander);
    //����ȫ����������
    lua_register(L, "Lua_Variable_SaveGlobalIntVariable", Lua_Variable_SaveGlobalIntVariable);
    //����ȫ�ָ���������
    lua_register(L, "Lua_Variable_SaveGlobalFloatVariable", Lua_Variable_SaveGlobalFloatVariable);
    //����ȫ���ַ�������
    lua_register(L, "Lua_Variable_SaveGlobalStringVariable", Lua_Variable_SaveGlobalStringVariable);
    //��ȡȫ����������
    lua_register(L, "Lua_Variable_ReadGlobalIntVariable", Lua_Variable_ReadGlobalIntVariable);
    //��ȡȫ�ָ���������
    lua_register(L, "Lua_Variable_ReadGlobalFloatVariable", Lua_Variable_ReadGlobalFloatVariable);
    //��ȡȫ���ַ�������
    lua_register(L, "Lua_Variable_ReadGlobalStringVariable", Lua_Variable_ReadGlobalStringVariable);
    //����ȫ�ֱ���
    lua_register(L, "Lua_Variable_DestroyGlobalVariable", Lua_Variable_DestroyGlobalVariable);
    //��ȡ��������
    lua_register(L, "Lua_Http_GetHttpData", Lua_Http_GetHttpData);
    //���ӵ�websocket������
    lua_register(L, "Lua_WS_LinkWSServer", Lua_WS_LinkWSServer);
    //������Ϣ��WS������
    lua_register(L, "Lua_WS_SendMessage", Lua_WS_SendMessage);
    //��ȡ��������Ϣ��ջ�е�һ�����ݲ�����������
    lua_register(L, "Lua_WS_GetMessage", Lua_WS_GetMessage);
    //��ȡ����������״̬
    lua_register(L, "Lua_WS_GetLinkState", Lua_WS_GetLinkState);
    
    //¼��ű�������Ϣ
    lua_register(L, "Lua_About", Lua_About);
#pragma endregion
    int err = 0;
    
    if (Base::LuaHandle::LuaCode[LuaFile].hotReload) {
        err = luaL_dofile(L, Base::LuaHandle::LuaCode[LuaFile].file.c_str());
    }
    else {
        err = luaL_dostring(L, Base::LuaHandle::LuaCode[LuaFile].code.c_str());
    }

    if (err != 0)
    {
        int type = lua_type(L, -1);
        if (type == 4) {
            string error = lua_tostring(L, -1);
            LuaErrorRecord(error);
        }
        return -1;
    }
    Nowlua = LuaFile;
    //���ô���ص�����
    lua_pushcfunction(L, LuaErrorCallBack);
    //��ȡջ����λ�ü�����ص�������λ��
    int callBack = lua_gettop(L);
    lua_getglobal(L, "run");
    err = lua_pcall(L, 0, 0, callBack);
    if (err != 0)
    {
        string error = lua_tostring(L, -1);
        LuaErrorRecord(error);
    }
    lua_close(L);
    Sublua = "";
    return 1;
}