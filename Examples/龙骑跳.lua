function run ()
    local PlayrAction = Gmae_Player_GetPlayerActionId()
    local x,y,z = Gmae_Player_GetPlayerNavigationCoordinate()

    local TP = Lua_Variable_ReadIntVariable('tp');

    if PlayrAction == 12708 and TP == 0 then
        TP = 1
        Gmae_Player_SetPlayerCoordinate(x,y,z)
    end

    if PlayrAction == 1 then
        TP = 0
    end

    Lua_Variable_SaveIntVariable('tp',TP)
end