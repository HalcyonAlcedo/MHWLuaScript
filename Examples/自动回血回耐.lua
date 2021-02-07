function run ()
    local BasicHealth,MaxHealth,Health = Gmae_Player_GetPlayerHealth()
    
    if MaxHealth ~= Health then
        Gmae_Player_SetPlayerCurrentHealth(MaxHealth);
    end
    local MaxEndurance,Endurance = Gmae_Player_GetPlayerEndurance()
    if MaxEndurance ~= Endurance then
        Gmae_Player_SetPlayerCurrentEndurance(MaxEndurance);
    end
end