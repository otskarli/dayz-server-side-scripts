// Loot spawner function
void SpawnRandomLoot()
{
    array<vector> spawnLocations = {
        "1000 0 2000",
        "1500 0 2500",
        "2000 0 3000"
    };

    int randomIndex = Math.RandomInt(0, spawnLocations.Count());
    vector chosenLocation = spawnLocations[randomIndex];

    EntityAI loot = GetGame().CreateObject("SmallProtectorCase", chosenLocation);
    if (loot)
    {
        Print("[LOOT SPAWNER] Loot spawned at: " + chosenLocation);
    }
    else
    {
        Print("[LOOT SPAWNER] Failed to spawn loot!");
    }

    string coordinates = string.Format("%.0f, %.0f", chosenLocation[0], chosenLocation[2]);
    string message = string.Format("A Small Protector Case has spawned at coordinates: %1!", coordinates);
    
    // Get all players on the server
    array<Man> players = new array<Man>();
    GetGame().GetPlayers(players);

    foreach (Man player : players)
    {
        if (player && player.IsAlive())
        {
            PlayerBase playerBase = PlayerBase.Cast(player);
            if (playerBase)
            {
                playerBase.MessageAction(message);
            }
        }
    }
}

void InitLootSpawner()
{
    const float interval = 60.0; // 1 minute in seconds
    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(SpawnRandomLoot, interval * 1000, true);
}