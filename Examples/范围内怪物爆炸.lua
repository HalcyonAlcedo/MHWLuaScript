function run ()
    if System_Keyboard_CheckKey(9) then
        local monsterList = Game_Monster_GetAllMonsterCoordinatesInRange(0,10000)
        for _, monster in pairs(monsterList) do
            Game_Player_CreateBowgunProjectiles(89,monster.X,monster.Y,monster.Z,monster.X,monster.Y,monster.Z)
        end
    end
end