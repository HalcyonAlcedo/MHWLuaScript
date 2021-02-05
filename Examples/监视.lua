function run ()
    local x,y,z = Gmae_Player_GetPlayerNavigationCoordinate()

    if System_Keyboard_CheckDoubleKey(84) then
        Gmae_Player_UnbindPlayerVisualCoordinate()
    else if System_Keyboard_CheckKey(84) then
        Gmae_Player_SetPlayerVisualCoordinate(x,y,z,0)
    end
end