#pragma once
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
static int Game_Player_Weapon_SetCharacteristicValue(lua_State* pL) {
    string ptr = "0x" + (string)lua_tostring(pL, 1);
    string type = (string)lua_tostring(pL, 2);
    long long Ptr = 0;
    sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
    void* ptrAddress = (void*)Ptr;
    if (ptrAddress != nullptr) {
        void* WeaponEntityPlot = *offsetPtr<void*>(Base::BasicGameData::PlayerPlot, 0x76B0);
        if (WeaponEntityPlot != nullptr) {
            if (type == "int") {
                *offsetPtr<int>(WeaponEntityPlot, Ptr) = (int)lua_tointeger(pL, 3);
            }
            else if (type == "float") {
                *offsetPtr<float>(WeaponEntityPlot, Ptr) = (float)lua_tonumber(pL, 3);
            }
            else if (type == "bool") {
                *offsetPtr<bool>(WeaponEntityPlot, Ptr) = (bool)lua_toboolean(pL, 3);
            }
            else if (type == "byte") {
                *offsetPtr<char>(WeaponEntityPlot, Ptr) = (char)lua_tointeger(pL, 3);
            }
        }
    }
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
    lua_pushstring(pL, Base::PlayerData::Name.c_str());
    lua_pushinteger(pL, Base::PlayerData::Hr);
    lua_pushinteger(pL, Base::PlayerData::Mr);
    return 3;
}
static int Game_World_GetMapId(lua_State* pL) {
    lua_pushinteger(pL, Base::World::MapId);
    return 1;
}
static int Game_World_Message(lua_State* pL) {
    lua_pushstring(pL, Base::World::Massage.c_str());
    return 1;
}
static int Game_World_SteamId(lua_State* pL) {
    lua_pushinteger(pL, Base::World::SteamId);
    return 1;
}
static int Game_World_Assembly(lua_State* pL) {
    lua_pushstring(pL, Base::World::Assembly.c_str());
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
static int Game_Player_CreateProjectiles(lua_State* pL) {
    int id = (int)lua_tointeger(pL, 1);
    float startx = (float)lua_tonumber(pL, 2);
    float starty = (float)lua_tonumber(pL, 3);
    float startz = (float)lua_tonumber(pL, 4);
    float endx = (float)lua_tonumber(pL, 5);
    float endy = (float)lua_tonumber(pL, 6);
    float endz = (float)lua_tonumber(pL, 7);
    string entity = "0x" + (string)lua_tostring(pL, 8);
    long long Ptr = 0;
    sscanf_s(entity.c_str(), "%p", &Ptr, sizeof(long long));
    void* EntityAddress = (double*)Ptr;
    if (EntityAddress != nullptr) {
        lua_pushboolean(pL, Base::ProjectilesOperation::CreateProjectiles(
            id, Base::Vector3(startx, starty, startz), Base::Vector3(endx, endy, endz), 0, EntityAddress
        ));
    }
    return 1;
}
static int Game_Monster_GetAllMonsterCoordinates(lua_State* pL)
{
    lua_newtable(pL);//创建一个表格，放在栈顶
    for (auto [id, monsterData] : Component::GetAllMonsterCoordinates()) {
        lua_pushinteger(pL, id);//压入编号
        lua_newtable(pL);//压入编号信息表
        lua_pushstring(pL, "X");//X坐标
        lua_pushnumber(pL, monsterData.CoordinatesX);//value
        lua_settable(pL, -3);//弹出X坐标
        lua_pushstring(pL, "Y");//Y坐标
        lua_pushnumber(pL, monsterData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z坐标
        lua_pushnumber(pL, monsterData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//怪物Id
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//怪物SubId
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//怪物指针
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//弹出到顶层
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
        lua_pushstring(pL, "Ptr");//怪物指针
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
        lua_pushstring(pL, "Ptr");//怪物指针
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
    lua_newtable(pL);//创建一个表格，放在栈顶
    for (auto [id, monsterData] : Component::GetAllMonsterCoordinatesRelativeToPlayers(min, max)) {
        lua_pushinteger(pL, id);//压入编号
        lua_newtable(pL);//压入编号信息表
        lua_pushstring(pL, "X");//X坐标
        lua_pushnumber(pL, monsterData.CoordinatesX);//value
        lua_settable(pL, -3);//弹出X坐标
        lua_pushstring(pL, "Y");//Y坐标
        lua_pushnumber(pL, monsterData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z坐标
        lua_pushnumber(pL, monsterData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//怪物Id
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//怪物SubId
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//怪物指针
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//弹出到顶层
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
        lua_pushstring(pL, "Ptr");//怪物指针
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
        lua_pushstring(pL, "Ptr");//怪物指针
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
    lua_newtable(pL);//创建一个表格，放在栈顶
    for (auto [id, monsterData] : Component::GetAllMonsterCoordinatesRelativeToTarget(Base::Vector3(x,y,z),min, max)) {
        lua_pushinteger(pL, id);//压入编号
        lua_newtable(pL);//压入编号信息表
        lua_pushstring(pL, "X");//X坐标
        lua_pushnumber(pL, monsterData.CoordinatesX);//value
        lua_settable(pL, -3);//弹出X坐标
        lua_pushstring(pL, "Y");//Y坐标
        lua_pushnumber(pL, monsterData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z坐标
        lua_pushnumber(pL, monsterData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//怪物Id
        lua_pushinteger(pL, monsterData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//怪物SubId
        lua_pushinteger(pL, monsterData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//怪物指针
        ostringstream ptr;
        ptr << monsterData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//弹出到顶层
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
        lua_pushstring(pL, "Ptr");//怪物指针
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
        lua_pushstring(pL, "Ptr");//怪物指针
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
    lua_newtable(pL);//创建一个表格，放在栈顶
    for (auto [id, environmentalData] : Component::GetAllEnvironmentalCoordinates(min, max)) {
        lua_pushinteger(pL, id);//压入编号
        lua_newtable(pL);//压入编号信息表
        lua_pushstring(pL, "X");//X坐标
        lua_pushnumber(pL, environmentalData.CoordinatesX);//value
        lua_settable(pL, -3);//弹出X坐标
        lua_pushstring(pL, "Y");//Y坐标
        lua_pushnumber(pL, environmentalData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z坐标
        lua_pushnumber(pL, environmentalData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Id");//怪物Id
        lua_pushinteger(pL, environmentalData.Id);
        lua_settable(pL, -3);
        lua_pushstring(pL, "SubId");//怪物SubId
        lua_pushinteger(pL, environmentalData.SubId);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//怪物指针
        ostringstream ptr;
        ptr << environmentalData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_settable(pL, -3);//弹出到顶层
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
static int Game_Shlp_GetShlpList(lua_State* pL)
{
    lua_newtable(pL);//创建一个表格，放在栈顶
    for (auto [Plot, shlpData] : Base::ProjectilesOperation::ProjectilesList) {
        ostringstream ptr;
        ptr << shlpData.Plot;
        string ptrstr = ptr.str();
        lua_pushstring(pL, ptrstr.c_str());//压入编号
        lua_newtable(pL);//压入编号信息表
        lua_pushstring(pL, "X");//X坐标
        lua_pushnumber(pL, shlpData.CoordinatesX);//value
        lua_settable(pL, -3);//弹出X坐标
        lua_pushstring(pL, "Y");//Y坐标
        lua_pushnumber(pL, shlpData.CoordinatesY);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Z");//Z坐标
        lua_pushnumber(pL, shlpData.CoordinatesZ);
        lua_settable(pL, -3);
        lua_pushstring(pL, "Ptr");//投射物指针
        lua_pushstring(pL, ptrstr.c_str());
        lua_settable(pL, -3);
        lua_pushstring(pL, "From");//来源指针
        ostringstream fromptr;
        fromptr << shlpData.From;
        string fromptrptrstr = fromptr.str();
        lua_pushstring(pL, fromptrptrstr.c_str());
        lua_settable(pL, -3);

        lua_settable(pL, -3);//弹出到顶层
    }
    return 1;
}
static int Game_Quest_GetQuestNowTime(lua_State* pL)
{
    lua_pushnumber(pL, Base::Chronoscope::NowTime);
    return 1;
}
static int Game_Quest_GetQuestId(lua_State* pL)
{
    lua_pushnumber(pL, Base::Quest::QuestId);
    return 1;
}
static int Game_Quest_GetQuestState(lua_State* pL)
{
    lua_pushnumber(pL, Base::Quest::QuestState);
    return 1;
}
static int Game_Quest_SetNextQuest(lua_State* pL) {
    Base::Quest::NextQuest = (int)lua_tointeger(pL, -1);
    return 0;
}
static int Game_Quest_SetQuestState(lua_State* pL) {
    int state = (int)lua_tointeger(pL, -1);
    *offsetPtr<int>(Base::BasicGameData::Quest, 0x38) = state;
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
    //ptr处理
    long long Ptr = 0;
    sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
    void* ptrAddress = (void*)Ptr;
    //offset处理
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
    int dw = 0;
    int dh = 0;
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
    if (lua_gettop(pL) > 8) {
        dw = (int)lua_tointeger(pL, 9);
        dh = (int)lua_tointeger(pL, 10);
    }
    Base::Draw::Img[name] = Base::Draw::NewImage(alpha, Channel, Base::Vector2(x, y), name, img, dw, dh);
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
    int dw = 0;
    int dh = 0;
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
    if (lua_gettop(pL) > 10) {
        dw = (int)lua_tointeger(pL, 11);
        dh = (int)lua_tointeger(pL, 12);
    }
    Base::Draw::Img[name] = Base::Draw::NewImage(alpha, Channel, Base::Vector2(x, y), name, img, true, width, height, dw, dh);
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
static int System_UI_GetSystemWindowSize(lua_State* pL) {
    int nWidth = GetSystemMetrics(SM_CXSCREEN);  //屏幕宽度    
    int nHeight = GetSystemMetrics(SM_CYSCREEN); //屏幕高度
    lua_pushinteger(pL, nWidth);
    lua_pushinteger(pL, nHeight);
    return 2;
}
static int System_UI_GetGameWindowSize(lua_State* pL) {
    HWND gameh = FindWindow("MT FRAMEWORK", NULL);
    RECT r1;
    ::GetWindowRect(gameh, &r1);
    lua_pushinteger(pL, r1.right - r1.left);
    lua_pushinteger(pL, r1.bottom - r1.top);
    return 2;
}
static int System_Sound_PlaySound(lua_State* pL) {
    string file = (string)lua_tostring(pL, 1);
    Base::SoundPlay::SoundList.push_back(file);
    return 0;
}
static int System_GetProcessList(lua_State* pL)
{
    Base::World::ProcessList = Component::GetProcessList();
    lua_newtable(pL);
    for (auto iter = Base::World::ProcessList.cbegin(); iter != Base::World::ProcessList.cend(); iter++) {
        string process = *iter;
        lua_pushstring(pL, process.c_str());
        lua_pushstring(pL, process.c_str());
        lua_settable(pL, -3);
    }
    return 1;
}
static int System_GetFileMD5(lua_State* pL) {
    string file = (string)lua_tostring(pL, 1);
    lua_pushstring(pL, Component::getFileMD5(file).c_str());
    return 1;
}
static int System_GetMouseDelta(lua_State* pL) {
    lua_pushnumber(pL, Base::Draw::MouseDelta.x);
    lua_pushnumber(pL, Base::Draw::MouseDelta.y);
    return 2;
}
#pragma endregion
#pragma region LuaFun
//存入整数变量
static int Lua_Variable_SaveIntVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 1);
    int variableValue = (int)lua_tointeger(pL, 2);
    LuaData::IntVariable[variableName] = variableValue;
    return 0;
}
//存入全局整数变量
static int Lua_Variable_SaveGlobalIntVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, 1);
    int variableValue = (int)lua_tointeger(pL, 2);
    LuaData::IntVariable[variableName] = variableValue;
    return 0;
}
//存入浮点数变量
static int Lua_Variable_SaveFloatVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 1);
    float variableValue = (float)lua_tonumber(pL, 2);
    LuaData::FloatVariable[variableName] = variableValue;
    return 0;
}
//存入全局浮点数变量
static int Lua_Variable_SaveGlobalFloatVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, 1);
    float variableValue = (float)lua_tonumber(pL, 2);
    LuaData::FloatVariable[variableName] = variableValue;
    return 0;
}
//存入字符串变量
static int Lua_Variable_SaveStringVariable(lua_State* pL) {
    string variableName = Sublua + Nowlua + (string)lua_tostring(pL, 1);
    string variableValue = (string)lua_tostring(pL, 2);
    LuaData::StringVariable[variableName] = variableValue;
    return 0;
}
//存入全局字符串变量
static int Lua_Variable_SaveGlobalStringVariable(lua_State* pL) {
    string variableName = "G_" + (string)lua_tostring(pL, 1);
    string variableValue = (string)lua_tostring(pL, 2);
    LuaData::StringVariable[variableName] = variableValue;
    return 0;
}
//读取整数变量
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
//读取全局整数变量
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
//读取浮点数变量
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
//读取全局浮点数变量
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
//读取字符串变量
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
//读取全局字符串变量
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
//销毁变量
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
//销毁全局变量
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
//设置子脚本变量前缀
static int Lua_Variable_SetSubScriptVariablePrefix(lua_State* pL) {
    string variablePrefix = (string)lua_tostring(pL, -1);
    Sublua = variablePrefix;
    return 0;
}
//获取随机数
static int Lua_Math_Random(lua_State* pL) {
    float min = (float)lua_tonumber(pL, 1);
    float max = (float)lua_tonumber(pL, 2);
    lua_pushnumber(pL, Base::Calculation::myRander(min, max));
    return 1;
}
//获取网络数据
static int Lua_Http_GetHttpData(lua_State* pL) {
    string httpUrl = (string)lua_tostring(pL, -1);
    lua_pushstring(pL, NetworkServer::GetHttpData(httpUrl).c_str());
    return 1;
}
//下载文件
static int Lua_Http_DownloadFile(lua_State* pL) {
    string url = (string)lua_tostring(pL, 1);
    string file = (string)lua_tostring(pL, 2);
    lua_pushboolean(pL, NetworkServer::DownloadFile(url, file));
    return 1;
}
//连接到WS服务器
static int Lua_WS_LinkWSServer(lua_State* pL) {
    string WSSLink = (string)lua_tostring(pL, -1);
    NetworkServer::LinkWS(WSSLink);
    return 0;
}
//发送消息到WS服务器
static int Lua_WS_SendMessage(lua_State* pL) {
    string Message = (string)lua_tostring(pL, -1);
    NetworkServer::WSSendMessage(Message);
    return 0;
}
//从服务器消息堆栈中接收一条消息并弹出
static int Lua_WS_GetMessage(lua_State* pL) {
    if (!NetworkServer::MessageCache.empty()) {
        lua_pushstring(pL, NetworkServer::MessageCache.front().c_str());
        NetworkServer::MessageCache.pop();
    }
    else 
        lua_pushstring(pL, "");
    return 1;
}
//从服务器消息堆栈中接收一条消息并弹出
static int Lua_WS_GetLinkState(lua_State* pL) {
    lua_pushboolean(pL, NetworkServer::WSState());
    return 1;
}
//录入脚本关于信息
static int Lua_About(lua_State* pL) {
    string About = (string)lua_tostring(pL, -1);
    Base::Draw::About[Nowlua] = About;
    return 0;
}
#pragma endregion
//==============================================
// Handling error
//==============================================
//错误回调
int LuaErrorCallBack(lua_State *L)
{
    lua_Debug debug = {};
    //错误所处的的调用层级
    int rank = 0;
    //逐层获取lua抛出的错误，直到获取到
    while (lua_getstack(L, rank, &debug)) {
        rank++;
    }
    //判断栈顶是否为字符串类型
    int type = lua_type(L, -1);
    if (type != 4)
        return 0;
    std::string error = lua_tostring(L, -1);
    std::string errorShort = debug.short_src;
    int errorLine = debug.currentline;
    std::string errorMsg = "error:" + error + ",errorShort:" + errorShort
        + ",line:" + std::to_string(errorLine);
    //将错误信息压人栈
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
int pcall_callback_err_fun(lua_State* L)
{
    lua_Debug debug = {};
    int ret = lua_getstack(L, 2, &debug); // 0是pcall_callback_err_fun自己, 1是error函数, 2是真正出错的函数
    lua_getinfo(L, "Sln", &debug);


    std::string err = lua_tostring(L, -1);
    lua_pop(L, 1);
    std::stringstream msg;
    msg << debug.short_src << ":line " << debug.currentline;
    if (debug.name != 0) {
        msg << "(" << debug.namewhat << " " << debug.name << ")";
    }


    msg << " [" << err << "]";
    lua_pushstring(L, msg.str().c_str());
    return 1;
}

//==============================================
// Main Functions
//==============================================
int Lua_Main(string LuaFile)
{
    lua_State* L = luaL_newstate();
    luaopen_base(L);
    luaopen_table(L);
    luaopen_string(L);
    luaopen_math(L);
    luaopen_debug(L);
    luaL_openlibs(L);

#pragma region Game
    #pragma region Player
    //获取玩家坐标
    lua_register(L, "Game_Player_GetPlayerCoordinate", Game_Player_GetPlayerCoordinate);
    //设置玩家坐标
    lua_register(L, "Game_Player_SetPlayerCoordinate", Game_Player_SetPlayerCoordinate);
    //获取准星坐标
    lua_register(L, "Game_Player_GetPlayerCollimatorCoordinate", Game_Player_GetPlayerCollimatorCoordinate);
    //获取抛物线准星坐标
    lua_register(L, "Game_Player_GetPlayerParabolaCollimatorCoordinate", Game_Player_GetPlayerParabolaCollimatorCoordinate);
    //获取武器坐标
    lua_register(L, "Game_Player_GetPlayerWeaponCoordinate", Game_Player_GetPlayerWeaponCoordinate);
    //检查瞄准状态
    lua_register(L, "Game_Player_CheckAimingStatus", Game_Player_CheckAimingStatus);
    //获取增量坐标
    lua_register(L, "Game_Player_GetPlayerIncrementCoordinate", Game_Player_GetPlayerIncrementCoordinate);
    //获取导航坐标
    lua_register(L, "Game_Player_GetPlayerNavigationCoordinate", Game_Player_GetPlayerNavigationCoordinate);
    //获取相机坐标
    lua_register(L, "Game_Player_GetPlayerVisualCoordinate", Game_Player_GetPlayerVisualCoordinate);
    //设置相机坐标（xyz和持续时间4个参数）
    lua_register(L, "Game_Player_SetPlayerVisualCoordinate", Game_Player_SetPlayerVisualCoordinate);
    //解除相机坐标绑定
    lua_register(L, "Game_Player_UnbindPlayerVisualCoordinate", Game_Player_UnbindPlayerVisualCoordinate);
    //获取相机距离
    lua_register(L, "Game_Player_GetPlayerVisualDistance", Game_Player_GetPlayerVisualDistance);
    //获取相机高度
    lua_register(L, "Game_Player_GetPlayerVisualHeight", Game_Player_GetPlayerVisualHeight);
    //设置相机距离
    lua_register(L, "Game_Player_SetPlayerVisualDistance", Game_Player_SetPlayerVisualDistance);
    //设置相机高度
    lua_register(L, "Game_Player_SetPlayerVisualHeight", Game_Player_SetPlayerVisualHeight);
    //获取玩家地址
    lua_register(L, "Game_Entity_GetPlayerPtr", Game_Entity_GetPlayerPtr);
    //获取玩家动作id
    lua_register(L, "Game_Player_GetPlayerActionId", Game_Player_GetPlayerActionId);
    //获取朝向角度
    lua_register(L, "Game_Player_GetPlayerAngle", Game_Player_GetPlayerAngle);
    //设置朝向角度
    lua_register(L, "Game_Player_SetPlayerAngle", Game_Player_SetPlayerAngle);
    //设置朝向坐标
    lua_register(L, "Game_Player_SetPlayerAimToCoordinate", Game_Player_SetPlayerAimToCoordinate);
    //获取玩家重力加速度
    lua_register(L, "Game_Player_GetPlayerGravity", Game_Player_GetPlayerGravity);
    //获取玩家下落速度
    lua_register(L, "Game_Player_GetPlayerFallSpeedRate", Game_Player_GetPlayerFallSpeedRate);
    //设置玩家重力加速度
    lua_register(L, "Game_Player_SetPlayerGravity", Game_Player_SetPlayerGravity);
    //设置玩家下落速度
    lua_register(L, "Game_Player_SetPlayerFallSpeedRate", Game_Player_SetPlayerFallSpeedRate);
    //获取玩家空中状态
    lua_register(L, "Game_Player_CheckPlayerAirState", Game_Player_CheckPlayerAirState);
    //添加特效
    lua_register(L, "Game_Player_AddEffect", Game_Player_AddEffect);

    //获取玩家武器Id
    lua_register(L, "Game_Player_Weapon_GetWeaponId", Game_Player_Weapon_GetWeaponId);
    //获取玩家武器类型
    lua_register(L, "Game_Player_Weapon_GetWeaponType", Game_Player_Weapon_GetWeaponType);
    //更换玩家的武器
    lua_register(L, "Game_Player_Weapon_ChangeWeapons", Game_Player_Weapon_ChangeWeapons);
    //完全更换玩家的武器
    lua_register(L, "Game_Player_Weapon_CompleteChangeWeapons", Game_Player_Weapon_CompleteChangeWeapons);
    //获取玩家武器装饰物坐标
    lua_register(L, "Game_Player_Weapon_GetOrnamentsCoordinate", Game_Player_Weapon_GetOrnamentsCoordinate);
    //获取玩家武器装饰物模型大小
    lua_register(L, "Game_Player_Weapon_GetOrnamentsSize", Game_Player_Weapon_GetOrnamentsSize);
    //设置玩家武器装饰物坐标
    lua_register(L, "Game_Player_Weapon_SetOrnamentsCoordinate", Game_Player_Weapon_SetOrnamentsCoordinate);
    //设置玩家武器装饰物模型大小
    lua_register(L, "Game_Player_Weapon_SetOrnamentsSize", Game_Player_Weapon_SetOrnamentsSize);
    //解除玩家武器装饰物坐标设置
    lua_register(L, "Game_Player_Weapon_DecontrolOrnamentsCoordinate", Game_Player_Weapon_DecontrolOrnamentsCoordinate);
    //解除玩家武器装饰物模型大小设置
    lua_register(L, "Game_Player_Weapon_DecontrolOrnamentsSize", Game_Player_Weapon_DecontrolOrnamentsSize);
    //获取玩家主武器坐标
    lua_register(L, "Game_Player_Weapon_GetMainWeaponCoordinate", Game_Player_Weapon_GetMainWeaponCoordinate);
    //获取玩家主武器模型大小
    lua_register(L, "Game_Player_Weapon_GetMainWeaponSize", Game_Player_Weapon_GetMainWeaponSize);
    //设置玩家主武器坐标
    lua_register(L, "Game_Player_Weapon_SetMainWeaponCoordinate", Game_Player_Weapon_SetMainWeaponCoordinate);
    //设置玩家主武器模型大小
    lua_register(L, "Game_Player_Weapon_SetMainWeaponSize", Game_Player_Weapon_SetMainWeaponSize);
    //解除玩家主武器坐标设置
    lua_register(L, "Game_Player_Weapon_DecontrolMainWeaponCoordinate", Game_Player_Weapon_DecontrolMainWeaponCoordinate);
    //解除玩家主武器模型大小设置
    lua_register(L, "Game_Player_Weapon_DecontrolMainWeaponSize", Game_Player_Weapon_DecontrolMainWeaponSize);
    //获取玩家副武器坐标
    lua_register(L, "Game_Player_Weapon_GetSecondaryWeaponCoordinate", Game_Player_Weapon_GetSecondaryWeaponCoordinate);
    //获取玩家副武器模型大小
    lua_register(L, "Game_Player_Weapon_GetSecondaryWeaponSize", Game_Player_Weapon_GetSecondaryWeaponSize);
    //设置玩家副武器坐标
    lua_register(L, "Game_Player_Weapon_SetSecondaryWeaponCoordinate", Game_Player_Weapon_SetSecondaryWeaponCoordinate);
    //设置玩家副武器模型大小
    lua_register(L, "Game_Player_Weapon_SetSecondaryWeaponSize", Game_Player_Weapon_SetSecondaryWeaponSize);
    //解除玩家副武器坐标设置
    lua_register(L, "Game_Player_Weapon_DecontrolSecondaryWeaponCoordinate", Game_Player_Weapon_DecontrolSecondaryWeaponCoordinate);
    //解除玩家副武器模型大小设置
    lua_register(L, "Game_Player_Weapon_DecontrolSecondaryWeaponSize", Game_Player_Weapon_DecontrolSecondaryWeaponSize);
    //获取玩家武器特殊数值(整数型)
    lua_register(L, "Game_Player_Weapon_CharacteristicIntValue", Game_Player_Weapon_CharacteristicIntValue);
    //获取玩家武器特殊数值(浮点型)
    lua_register(L, "Game_Player_Weapon_CharacteristicFloatValue", Game_Player_Weapon_CharacteristicFloatValue);
    //获取玩家武器特殊数值(字节)
    lua_register(L, "Game_Player_Weapon_CharacteristicByteValue", Game_Player_Weapon_CharacteristicByteValue);
    //设置玩家武器特殊数值
    lua_register(L, "Game_Player_Weapon_SetCharacteristicValue", Game_Player_Weapon_SetCharacteristicValue);
    //获取玩家武器最后命中的坐标
    lua_register(L, "Game_Player_Weapon_GetHitCoordinate", Game_Player_Weapon_GetHitCoordinate);
    //获取玩家武器最后命中的怪物地址
    lua_register(L, "Game_Player_Weapon_GetAttackMonster", Game_Player_Weapon_GetAttackMonster);

    //获取玩家派生信息
    lua_register(L, "Game_Player_GetFsmData", Game_Player_GetFsmData);
    //执行指定的派生动作
    lua_register(L, "Game_Player_RunFsmAction", Game_Player_RunFsmAction);
    //检查执行的派生动作是否结束
    lua_register(L, "Game_Player_CheckRunFsmActionOver", Game_Player_CheckRunFsmActionOver);
    //执行指定的派生动作
    lua_register(L, "Game_Player_RunLmtAction", Game_Player_RunLmtAction);
    //获取当前动作帧
    lua_register(L, "Game_Player_GetActionFrame", Game_Player_GetActionFrame);
    //设置当前动作帧
    lua_register(L, "Game_Player_SetActionFrame", Game_Player_SetActionFrame);
    //设置当前动作帧速率
    lua_register(L, "Game_Player_SetActionFrameSpeed", Game_Player_SetActionFrameSpeed);
    //获取玩家血量信息
    lua_register(L, "Game_Player_GetPlayerHealth", Game_Player_GetPlayerHealth);
    //设置玩家当前血量
    lua_register(L, "Game_Player_SetPlayerCurrentHealth", Game_Player_SetPlayerCurrentHealth);
    //设置玩家基础血量
    lua_register(L, "Game_Player_SetPlayerBasicHealth", Game_Player_SetPlayerBasicHealth);
    //获取玩家耐力信息
    lua_register(L, "Game_Player_GetPlayerEndurance", Game_Player_GetPlayerEndurance);
    //设置玩家当前耐力
    lua_register(L, "Game_Player_SetPlayerCurrentEndurance", Game_Player_SetPlayerCurrentEndurance);
    //设置玩家最大耐力
    lua_register(L, "Game_Player_SetPlayerMaxEndurance", Game_Player_SetPlayerMaxEndurance);
    //获取玩家角色信息
    lua_register(L, "Game_Player_GetPlayerRoleInfo", Game_Player_GetPlayerRoleInfo);
    //生成玩家武器投射物
    lua_register(L, "Game_Player_CreateWeaponProjectiles", Game_Player_CreateWeaponProjectiles);
    //生成玩家手弩投射物
    lua_register(L, "Game_Player_CreateBowgunProjectiles", Game_Player_CreateBowgunProjectiles);
    //生成自定义投射物
    lua_register(L, "Game_Player_CreateProjectiles", Game_Player_CreateProjectiles);
    //获取玩家Buff剩余时间
    lua_register(L, "Game_Player_GetPlayerBuffDuration", Game_Player_GetPlayerBuffDuration);
    //设置玩家Buff剩余时间
    lua_register(L, "Game_Player_SetPlayerBuffDuration", Game_Player_SetPlayerBuffDuration);
    //获取玩家钩爪坐标
    lua_register(L, "Game_Player_GetPlayerHookCoordinate", Game_Player_GetPlayerHookCoordinate);
    //获取对玩家仇恨的怪物
    lua_register(L, "Game_Player_GetMonstersHateToPlayers", Game_Player_GetMonstersHateToPlayers);
    //设置钩爪钩向的坐标
    lua_register(L, "Game_Player_SetHookCoordinateChange", Game_Player_SetHookCoordinateChange);
    //取消钩爪钩向坐标的设置
    lua_register(L, "Game_Player_CancelHookCoordinateChange", Game_Player_CancelHookCoordinateChange);
    
    #pragma endregion
    //获取当前地图Id
    lua_register(L, "Game_World_GetMapId", Game_World_GetMapId);
    //获取聊天消息
    lua_register(L, "Game_World_Message", Game_World_Message);
    //获取Steam好友Id
    lua_register(L, "Game_World_SteamId", Game_World_SteamId);
    //获取集会区域代码
    lua_register(L, "Game_World_Assembly", Game_World_Assembly);
    //获取投射物数据
    lua_register(L, "Game_Shlp_GetShlpList", Game_Shlp_GetShlpList);
#pragma region Quest
    //获取当前任务时间
    lua_register(L, "Game_Quest_GetQuestNowTime", Game_Quest_GetQuestNowTime);
    //获取当前任务ID
    lua_register(L, "Game_Quest_GetQuestId", Game_Quest_GetQuestId);
    //获取当前任务状态
    lua_register(L, "Game_Quest_GetQuestState", Game_Quest_GetQuestState);
    //设置下一个任务
    lua_register(L, "Game_Quest_SetNextQuest", Game_Quest_SetNextQuest);
    //设置任务状态
    lua_register(L, "Game_Quest_SetQuestState", Game_Quest_SetQuestState);
#pragma endregion
    #pragma region Monster
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
    //杀死范围内所有怪物
    lua_register(L, "Game_Monster_KillAllMonsterInRange", Game_Monster_KillAllMonsterInRange);
    //给范围内所有怪物设置异常状态
    lua_register(L, "Game_Monster_AddDebuffToAllMonsterInRange", Game_Monster_AddDebuffToAllMonsterInRange);
    //获取导航的怪物的坐标
    lua_register(L, "Game_Monster_GetNavigationMonsterCoordinates", Game_Monster_GetNavigationMonsterCoordinates);
    //获取距离最近的怪物的坐标
    lua_register(L, "Game_Monster_GetNearestMonsterCoordinates", Game_Monster_GetNearestMonsterCoordinates);
    //获取最后一次击中的怪物的坐标
    lua_register(L, "Game_Monster_GetLastHitMonsterCoordinates", Game_Monster_GetLastHitMonsterCoordinates);
    //获取所有怪物的坐标
    lua_register(L, "Game_Monster_GetAllMonsterCoordinates", Game_Monster_GetAllMonsterCoordinates);
    //获取所有怪物的生命
    lua_register(L, "Game_Monster_GetAllMonsterHealth", Game_Monster_GetAllMonsterHealth);
    //获取所有怪物的异常状态
    lua_register(L, "Game_Monster_GetAllMonsterDebuff", Game_Monster_GetAllMonsterDebuff);
    //获取范围内所有怪物的坐标
    lua_register(L, "Game_Monster_GetAllMonsterCoordinatesInRange", Game_Monster_GetAllMonsterCoordinatesInRange);
    //获取范围内所有怪物的生命
    lua_register(L, "Game_Monster_GetAllMonsterHealthInRange", Game_Monster_GetAllMonsterHealthInRange);
    //获取范围内所有怪物的异常状态(计划中)
    lua_register(L, "Game_Monster_GetAllMonsterDebuffInRange", Game_Monster_GetAllMonsterDebuffInRange);
    //获取目标点范围内所有怪物的坐标
    lua_register(L, "Game_Monster_GetAllMonsterCoordinatesInTargetPointRange", Game_Monster_GetAllMonsterCoordinatesInTargetPointRange);
    //获取目标点范围内所有怪物的生命
    lua_register(L, "Game_Monster_GetAllMonsterHealthInTargetPointRange", Game_Monster_GetAllMonsterHealthInTargetPointRange);
    //获取目标点范围内所有怪物的异常状态(计划中)
    lua_register(L, "Game_Monster_GetAllMonsterDebuffInTargetPointRange", Game_Monster_GetAllMonsterDebuffInTargetPointRange);
    //获取指定id怪物的中文名
    lua_register(L, "Game_Monster_GetMonsterCNName", Game_Monster_GetMonsterCNName);
    #pragma endregion
    #pragma region Environmental
    //设置环境生物筛选器
    lua_register(L, "Game_Environmental_SetFilter", Game_Environmental_SetFilter);
    //清除环境生物筛选器
    lua_register(L, "Game_Environmental_DisableFilter", Game_Environmental_DisableFilter);
    //设置范围内所有环境生物的坐标
    lua_register(L, "Game_Environmental_SetAllEnvironmentalCoordinatesInRange", Game_Environmental_SetAllEnvironmentalCoordinatesInRange);
    //获取范围内所有环境生物的坐标
    lua_register(L, "Game_Environmental_GetAllEnvironmentalCoordinatesInRange", Game_Environmental_GetAllEnvironmentalCoordinatesInRange);
    #pragma endregion
    #pragma region Entity
    //获取实体属性
    lua_register(L, "Game_Entity_GetEntityProperties", Game_Entity_GetEntityProperties);
    //设置实体坐标
    lua_register(L, "Game_Entity_SetEntityCoordinate", Game_Entity_SetEntityCoordinate);
    //设置实体模型大小
    lua_register(L, "Game_Entity_SetEntitySize", Game_Entity_SetEntitySize);
    //设置实体当前动作帧
    lua_register(L, "Game_Entity_SetEntityActionFrame", Game_Entity_SetEntityActionFrame);
    //设置实体朝向角度
    lua_register(L, "Game_Entity_SetEntityAngle", Game_Entity_SetEntityAngle);
    //将实体朝向指定的坐标
    lua_register(L, "Game_Entity_SetEntityAimCoordinate", Game_Entity_SetEntityAimCoordinate);
    //将实体动作帧速率
    lua_register(L, "Game_Entity_SetEntityFrameSpeed", Game_Entity_SetEntityFrameSpeed);
    //解除全部实体动作帧速率设置
    lua_register(L, "Game_Entity_ClearEntityFrameSpeed", Game_Entity_ClearEntityFrameSpeed);
    //使实体执行动作
    lua_register(L, "Game_Entity_BehaviorControl", Game_Entity_BehaviorControl);
    #pragma endregion
    
#pragma endregion
#pragma region System
    //检查按键
    lua_register(L, "System_Keyboard_CheckKey", System_Keyboard_CheckKey);
    //检查按键双击
    lua_register(L, "System_Keyboard_CheckDoubleKey", System_Keyboard_CheckDoubleKey);
    //检查按键是否处于按下状态
    lua_register(L, "System_Keyboard_CheckKeyIsPressed", System_Keyboard_CheckKeyIsPressed);
    //注册快捷键
    lua_register(L, "System_HotKey_AddHotKey", System_HotKey_AddHotKey);
    //检查快捷键
    lua_register(L, "System_HotKey_CheckKey", System_HotKey_CheckKey);
    //检查Xbox按键
    lua_register(L, "System_XboxPad_CheckKey", System_XboxPad_CheckKey);
    //检查Xbox按键双击
    lua_register(L, "System_XboxPad_CheckDoubleKey", System_XboxPad_CheckDoubleKey);
    //检查Xbox按键是否处于按下状态
    lua_register(L, "System_XboxPad_CheckKeyIsPressed", System_XboxPad_CheckKeyIsPressed);
    //添加计时器
    lua_register(L, "System_Chronoscope_AddChronoscope", System_Chronoscope_AddChronoscope);
    //检查计时器
    lua_register(L, "System_Chronoscope_CheckChronoscope", System_Chronoscope_CheckChronoscope);
    //检查计时器是否存在
    lua_register(L, "System_Chronoscope_CheckPresenceChronoscope", System_Chronoscope_CheckPresenceChronoscope);
    //删除计时器
    lua_register(L, "System_Chronoscope_DelChronoscope", System_Chronoscope_DelChronoscope);
    //向游戏内发送消息
    lua_register(L, "System_Message_ShowMessage", System_Message_ShowMessage);
    //向控制台发送消息
    lua_register(L, "System_Console_Info", System_Console_Info);
    //向控制台发送错误消息
    lua_register(L, "System_Console_Error", System_Console_Error);
    //获取LuaScript插件构建版本
    lua_register(L, "System_LuaScript_Build", System_LuaScript_Build);
    //获取LuaScript插件构建版本
    lua_register(L, "System_LuaScript_Version", System_LuaScript_Version);
    //获取UUID
    lua_register(L, "System_GetUUID", System_GetUUID);
    //打开调试控制台
    lua_register(L, "System_DeBug_OpenDeBugConsole", System_DeBug_OpenDeBugConsole);
    //关闭调试控制台
    lua_register(L, "System_DeBug_CloseDeBugConsole", System_DeBug_CloseDeBugConsole);
    //获取偏移内存地址
    lua_register(L, "System_Memory_GetOffsetAddress", System_Memory_GetOffsetAddress);
    //获取内存地址数据
    lua_register(L, "System_Memory_GetAddressData", System_Memory_GetAddressData);
    //获取内存地址数据
    lua_register(L, "System_Memory_SetAddressData", System_Memory_SetAddressData);
    //向屏幕添加图片
    lua_register(L, "System_UI_DrawImage", System_UI_DrawImage);
    //向屏幕添加Base64图片
    lua_register(L, "System_UI_DrawBase64Image", System_UI_DrawBase64Image);
    //移除添加的图片
    lua_register(L, "System_UI_RemoveImage", System_UI_RemoveImage);
    //向屏幕添加文字
    lua_register(L, "System_UI_DrawText", System_UI_DrawText);
    //移除添加的文字
    lua_register(L, "System_UI_RemoveText", System_UI_RemoveText);
    //获取屏幕大小
    lua_register(L, "System_UI_GetSystemWindowSize", System_UI_GetSystemWindowSize);
    //获取游戏窗口大小
    lua_register(L, "System_UI_GetGameWindowSize", System_UI_GetGameWindowSize);
    //播放音频文件
    lua_register(L, "System_Sound_PlaySound", System_Sound_PlaySound);
    //获取系统进程列表
    lua_register(L, "System_GetProcessList", System_GetProcessList);
    //获取文件Md5
    lua_register(L, "System_GetFileMD5", System_GetFileMD5);
    //获取鼠标移动信息
    lua_register(L, "System_GetMouseDelta", System_GetMouseDelta);
#pragma endregion
#pragma region Lua
    //存入整数变量
    lua_register(L, "Lua_Variable_SaveIntVariable", Lua_Variable_SaveIntVariable);
    //存入浮点数变量
    lua_register(L, "Lua_Variable_SaveFloatVariable", Lua_Variable_SaveFloatVariable);
    //存入字符串变量
    lua_register(L, "Lua_Variable_SaveStringVariable", Lua_Variable_SaveStringVariable);
    //读取整数变量
    lua_register(L, "Lua_Variable_ReadIntVariable", Lua_Variable_ReadIntVariable);
    //读取浮点数变量
    lua_register(L, "Lua_Variable_ReadFloatVariable", Lua_Variable_ReadFloatVariable);
    //读取字符串变量
    lua_register(L, "Lua_Variable_ReadStringVariable", Lua_Variable_ReadStringVariable);
    //销毁变量
    lua_register(L, "Lua_Variable_DestroyVariable", Lua_Variable_DestroyVariable);
    //设置子脚本变量名
    lua_register(L, "Lua_Variable_SetSubScriptVariablePrefix", Lua_Variable_SetSubScriptVariablePrefix);
    //获取随机数
    lua_register(L, "Lua_Math_Random", Lua_Math_Random);
    lua_register(L, "Lua_Math_Rander", Lua_Math_Random);
    //存入全局整数变量
    lua_register(L, "Lua_Variable_SaveGlobalIntVariable", Lua_Variable_SaveGlobalIntVariable);
    //存入全局浮点数变量
    lua_register(L, "Lua_Variable_SaveGlobalFloatVariable", Lua_Variable_SaveGlobalFloatVariable);
    //存入全局字符串变量
    lua_register(L, "Lua_Variable_SaveGlobalStringVariable", Lua_Variable_SaveGlobalStringVariable);
    //读取全局整数变量
    lua_register(L, "Lua_Variable_ReadGlobalIntVariable", Lua_Variable_ReadGlobalIntVariable);
    //读取全局浮点数变量
    lua_register(L, "Lua_Variable_ReadGlobalFloatVariable", Lua_Variable_ReadGlobalFloatVariable);
    //读取全局字符串变量
    lua_register(L, "Lua_Variable_ReadGlobalStringVariable", Lua_Variable_ReadGlobalStringVariable);
    //销毁全局变量
    lua_register(L, "Lua_Variable_DestroyGlobalVariable", Lua_Variable_DestroyGlobalVariable);
    //获取网络数据
    lua_register(L, "Lua_Http_GetHttpData", Lua_Http_GetHttpData);
    //下载文件
    lua_register(L, "Lua_Http_DownloadFile", Lua_Http_DownloadFile);
    //连接到websocket服务器
    lua_register(L, "Lua_WS_LinkWSServer", Lua_WS_LinkWSServer);
    //发送信息至WS服务器
    lua_register(L, "Lua_WS_SendMessage", Lua_WS_SendMessage);
    //获取服务器消息堆栈中的一条数据并弹出该数据
    lua_register(L, "Lua_WS_GetMessage", Lua_WS_GetMessage);
    //获取服务器连接状态
    lua_register(L, "Lua_WS_GetLinkState", Lua_WS_GetLinkState);
    
    //录入脚本关于信息
    lua_register(L, "Lua_About", Lua_About);
#pragma endregion
    int err = 0;
    
    if (Base::LuaHandle::LuaCode[LuaFile].hotReload) {
        err = luaL_loadfile(L, Base::LuaHandle::LuaCode[LuaFile].file.c_str());
    }
    else {
        err = luaL_loadstring(L, Base::LuaHandle::LuaCode[LuaFile].code.c_str());
    }

    if (err != 0)
    {
        int type = lua_type(L, -1);
        if (type == 4) {
            string error = lua_tostring(L, -1);
            LuaErrorRecord(error);
        }
        lua_close(L);
        return -1;
    }
    Nowlua = LuaFile;
    if (Base::LuaHandle::LuaCode[LuaFile].hotReload) {
        err = lua_pcall(L, 0, 0, 0);
    }
    else {
        err = lua_pcall(L, 0, LUA_MULTRET, 0);
    }
    /*
    lua_pushcfunction(L, pcall_callback_err_fun);
    int pos_err = lua_gettop(L);
    lua_getglobal(L, "run");               //调用lua中的函数f
    err = lua_pcall(L, 0, 1, pos_err);
    if (err != 0)
    {
        int t = lua_type(L, -1);
        const char* error = lua_tostring(L, -1);
        LOG(ERR) << Base::ModConfig::ModName << " LUA ERR:" << error;
        lua_pop(L, 1);
    }
    lua_close(L);
    */
    //设置错误回调函数
    lua_pushcfunction(L, LuaErrorCallBack);
    //获取栈顶的位置即错误回调函数的位置
    int callBack = lua_gettop(L);
    lua_getglobal(L, "run");
    int runerr = 0;
    runerr = lua_pcall(L, 0, 0, 0);
    err = lua_pcall(L, 0, 0, callBack);
    
    if (runerr != 0)
    {
        //string error = lua_tostring(L, -1);
        //LuaErrorRecord(error);
        int type = lua_type(L, -1);
        if (type == 4) {
            const char* error = lua_tostring(L, -1);
            LOG(ERR) << Base::ModConfig::ModName << " LUA RUN ERR:" << error;
        }
    }
    lua_close(L);
    Sublua = "";
    return 1;
}