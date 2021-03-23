function run ()
    if Game_Player_Weapon_GetWeaponType() == 3 and Game_Player_Weapon_GetWeaponId() == 94 then
        --1 左键回斩
        if Game_Player_GetPlayerActionId() == 49460 and System_Keyboard_CheckKey(1) then
            Game_Player_AddEffect(2004,0)
            Game_Player_RunFsmAction(3,67)
        end
        --2 A键左移
        if not Game_Player_CheckRunFsmActionOver() and Game_Player_GetPlayerActionId() == 49259 and System_Keyboard_CheckKey(65) then
            Game_Player_AddEffect(2003,0)
            Game_Player_RunFsmAction(3,82)
        end
        --2 D键右移
        if not Game_Player_CheckRunFsmActionOver() and Game_Player_GetPlayerActionId() == 49259 and System_Keyboard_CheckKey(68) then
            Game_Player_AddEffect(2003,0)
            Game_Player_RunFsmAction(3,83)
        end
        --2 左键下劈
        if not Game_Player_CheckRunFsmActionOver() and Game_Player_GetPlayerActionId() == 49259 and System_Keyboard_CheckKey(1) then
            Game_Player_AddEffect(2007,0)
            Game_Player_RunFsmAction(3,85)
        end
        --3 右键中断并大回旋
        if not Game_Player_CheckRunFsmActionOver() and Game_Player_GetPlayerActionId() == 49253 and System_Keyboard_CheckKey(2) then
            Game_Player_AddEffect(0,2)
            Game_Player_RunFsmAction(3,69)
        end
    end
end