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