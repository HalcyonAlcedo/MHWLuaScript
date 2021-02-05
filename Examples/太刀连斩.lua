local Modular = {}

function Modular.run ()
    if Gmae_Player_Weapon_GetWeaponType() == 3 then
        --1 左键回斩
        if Gmae_Player_GetPlayerActionId() == 49460 and System_Keyboard_CheckKey(1) == 1 then
            Gmae_Player_AddEffect(2004,0)
            Gmae_Player_RunFsmAction(3,67)
        end
        --2 A键左移
        if Gmae_Player_CheckRunFsmActionOver() == 0 and Gmae_Player_GetPlayerActionId() == 49259 and System_Keyboard_CheckKey(65) == 1 then
            Gmae_Player_AddEffect(2003,0)
            Gmae_Player_RunFsmAction(3,82)
        end
        --2 D键右移
        if Gmae_Player_CheckRunFsmActionOver() == 0 and Gmae_Player_GetPlayerActionId() == 49259 and System_Keyboard_CheckKey(68) == 1 then
            Gmae_Player_AddEffect(2003,0)
            Gmae_Player_RunFsmAction(3,83)
        end
        --2 左键下劈
        if Gmae_Player_CheckRunFsmActionOver() == 0 and Gmae_Player_GetPlayerActionId() == 49259 and System_Keyboard_CheckKey(1) == 1 then
            Gmae_Player_AddEffect(2007,0)
            Gmae_Player_RunFsmAction(3,85)
        end
        --3 右键中断并大回旋
        if Gmae_Player_CheckRunFsmActionOver() == 0 and Gmae_Player_GetPlayerActionId() == 49253 and System_Keyboard_CheckKey(2) == 1 then
            Gmae_Player_AddEffect(0,2)
            Gmae_Player_RunFsmAction(3,69)
        end
    end
end

return Modular