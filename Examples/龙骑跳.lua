local Modular = {}

function Modular.run ()
    local PlayrAction = Gmae_Player_GetPlayerActionId
    local x,y,z = Gmae_Player_GetPlayerNavigationCoordinate()
    local TP = false

    if PlayrAction == 12708 and not TP then
        TP = true
        Gmae_Player_SetPlayerCoordinate(x,y,z)
    end

    if PlayrAction == 1 then
        TP = false
    end
end

return Modular