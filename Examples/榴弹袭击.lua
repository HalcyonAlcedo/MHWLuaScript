--[[
    示例文件
    使用动作决胜姿势2可以对目视方向释放最少8发榴弹袭击
]]
function run ()
    local x,y,z = Game_Player_GetPlayerCollimatorCoordinate()
    local wpType = Game_Player_Weapon_GetWeaponType()
    local wpId = Game_Player_Weapon_GetWeaponId()
    if Game_Player_GetPlayerActionId() == 12390
    then
        System_Chronoscope_AddChronoscope(1,'PreLaunchAction')
    end
    if System_Chronoscope_CheckChronoscope('PreLaunchAction')
    then
        Game_Player_Weapon_ChangeWeapons(12,30)
        Game_Player_RunFsmAction(3,11)
        System_Chronoscope_AddChronoscope(0.05,'LaunchAction')
    end
    if System_Chronoscope_CheckChronoscope('LaunchAction')
    then
        local monsterList = Game_Monster_GetAllMonsterCoordinatesInTargetPointRange(x,y,z,0,8000)
        if #monsterList < 8 then
            for i=0,8 - #monsterList,1 do
                Game_Player_CreateWeaponProjectiles(
                    13,
                    x,y+1500,z,
                    x + Lua_Math_Rander(-500,500) ,y + Lua_Math_Rander(0,500) ,z + Lua_Math_Rander(-500,500)
                )
            end
        end
        for _, monster in pairs(monsterList) do
            Game_Player_CreateWeaponProjectiles(
                13,
                x,y+1500,z,
                monster.X + Lua_Math_Rander(-150,150) ,monster.Y + Lua_Math_Rander(-150,150) ,monster.Z + Lua_Math_Rander(-150,150)
            )
        end
        Game_Player_Weapon_ChangeWeapons(wpType,wpId)
        Game_Player_RunFsmAction(1,6)
    end
end