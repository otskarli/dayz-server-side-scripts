// Loot spawner function
void RandomLootSpawner()
{
    array<vector> spawnLocations = {
        "1234 5 5678",  // Warehouse near industrial area in Chernarus (Y = 5 for elevation)
        "1450 3 6900",  // Warehouse near Zelenogorsk (Y = 3)
        "1600 4 6200",  // Industrial complex near Stary Sobor (Y = 4)
        "2000 6 3000",  // Large warehouse area near Gorka (Y = 6)
        "2300 5 4500",  // Warehouse near Novo and military areas (Y = 5)
        "3200 4 5100",  // Warehouse at Svetlojarsk industrial complex (Y = 4)
        "850 2 2400",   // Warehouse near Balota Airfield (Y = 2)
        "4500 6 5600",  // Industrial warehouse near Vavilovo (Y = 6)
        "2900 3 4300",  // Small warehouse area near Tisy (Y = 3)
        "1800 5 2000"   // Warehouse near Kamensk (Y = 5)
    };

    int randomIndex = Math.RandomInt(0, spawnLocations.Count());
    vector chosenLocation = spawnLocations[randomIndex];

    array<string> randomItems = { 
        "Map", 
        "BurlapSack", 
        "Chemlight", 
        "FishingHook", 
        "TeddyBear", 
        "Flare", 
        "RoadFlare", 
        "Bone", 
        "Paper", 
        "Linen"
    };
    int randomItemIndex = Math.RandomInt(0, randomItems.Count());

    EntityAI loot = GetGame().CreateObject(randomItems[randomItemIndex], chosenLocation);
    if (loot)
    {
        Print("[LOOT SPAWNER] Loot spawned at: " + chosenLocation);
    }
    else
    {
        Print("[LOOT SPAWNER] Failed to spawn loot!");
    }

    string coordinates = chosenLocation[0].ToString() + ", " + chosenLocation[2].ToString();
    string message = string.Format(randomItems[randomItemIndex] + " has spawned at coordinates: %1!", coordinates);
    
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

void AdjustLootSpawnRate()
{
    // Get all players on the server
    array<Man> players = new array<Man>();
    GetGame().GetPlayers(players);

    int playerCount = players.Count();

    const float minInterval = 3600.0; // 1 hour in seconds
    const float maxInterval = 10800.0; // 3 hours in seconds

    // Calculate the interval based on player count
    float interval = maxInterval - ((maxInterval - minInterval) / 63) * (playerCount - 1);
    interval = Math.Clamp(interval, minInterval, maxInterval);

    // Schedule the loot spawner with the new interval
    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(RandomLootSpawner, interval * 1000, true);

    // Re-schedule AdjustLootSpawnRate itself to check again in 5 minutes
    const float adjustmentInterval = 60.0; // 5 minutes in seconds
    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(AdjustLootSpawnRate, adjustmentInterval * 1000, false);
}

void InitLootSpawner()
{
    // Call AdjustLootSpawnRate immediately, and schedule it if necessary
    AdjustLootSpawnRate();
}