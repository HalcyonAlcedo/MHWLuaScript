function run ()
    local BasicHealth,MaxHealth,Health = Game_Player_GetPlayerHealth()
    
    if MaxHealth ~= Health then
        Game_Player_SetPlayerCurrentHealth(MaxHealth);
    end
    local MaxEndurance,Endurance = Game_Player_GetPlayerEndurance()
    if MaxEndurance ~= Endurance then
        Game_Player_SetPlayerCurrentEndurance(MaxEndurance);
    end
end