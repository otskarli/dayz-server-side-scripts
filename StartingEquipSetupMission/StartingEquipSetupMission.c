
class StartingEquipSetupMission: MissionServer
{
    void SetRandomHealth(EntityAI itemEnt)
    {
        if (itemEnt)
        {
            float rndHlt = Math.RandomFloat(0.45, 0.65);
            itemEnt.SetHealth01("", "", rndHlt);
        }
    }

    override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
    {
        Entity playerEnt;
        playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
        Class.CastTo(m_player, playerEnt);

        GetGame().SelectPlayer(identity, m_player);

        return m_player;
    }

    override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
    {
        EntityAI itemClothing;
        EntityAI itemEnt;
        EntityAI bat;
        ItemBase itemBs;

        // Backpack Selection
        string backpackArray[] = { "HuntingBag", "MountainBag_Red", "MountainBag_Green", "CoyoteBag_Brown" }; // Add other 64-slot backpacks here
        int backpackIndex = Math.RandomInt(0, 4);
        itemClothing = player.GetInventory().CreateInInventory(backpackArray[backpackIndex]);

        // Random Canned Food
        string cannedFoodArray[] = { "CannedSardines", "CannedSpaghetti", "CannedBakedBeans", "CannedTuna" };
        int foodIndex = Math.RandomInt(0, 4);
        player.GetInventory().CreateInInventory(cannedFoodArray[foodIndex]);

        if (itemClothing)
        {
            // Random Knife
            string knifeArray[] = { "KitchenKnife", "SteakKnife", "HuntingKnife", "CombatKnife" };
            int knifeIndex = Math.RandomInt(0, 4);
            itemClothing.GetInventory().CreateInInventory(knifeArray[knifeIndex]);

            //add wepun to beat fags
            bat = itemClothing.GetInventory().CreateInInventory("BaseballBat");
            player.SetQuickBarEntityShortcut(bat, 0);
        }

        // Default Body, Legs, Feet setup
        itemClothing = player.FindAttachmentBySlotName("Body");
        if (itemClothing)
        {
            itemEnt = itemClothing.GetInventory().CreateInInventory("BandageDressing");
            player.SetQuickBarEntityShortcut(itemEnt, 2);

            string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
            int rndIndex = Math.RandomInt(0, 4);
            itemEnt = itemClothing.GetInventory().CreateInInventory(chemlightArray[rndIndex]);
            player.SetQuickBarEntityShortcut(itemEnt, 1);
        }
    }

}

// Entry point for the custom mission
Mission CreateCustomMission(string path)
{
    return new StartingEquipSetupMission();
}