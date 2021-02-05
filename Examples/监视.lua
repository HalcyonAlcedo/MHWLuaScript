local Modular = {}

function Modular.run ()
    local x,y,z = Gmae_Player_GetPlayerNavigationCoordinate()

    if System_Keyboard_CheckKey(84) == 1 then
        Gmae_Player_SetPlayerVisualCoordinate(x,y,z,0)
    else
        Gmae_Player_UnbindPlayerVisualCoordinate()
    end
end

return Modular