function run ()
    local x,y,z = Game_Player_GetPlayerNavigationCoordinate()

    if System_Keyboard_CheckDoubleKey(84) then
        Game_Player_UnbindPlayerVisualCoordinate()
    else if System_Keyboard_CheckKey(84) then
        Game_Player_SetPlayerVisualCoordinate(x,y,z,0)
    end
end