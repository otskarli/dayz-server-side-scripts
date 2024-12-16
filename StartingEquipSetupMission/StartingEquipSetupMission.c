
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

        // Equip Hunting Jacket (replacing default Body slot)
        itemClothing = player.FindAttachmentBySlotName("Body");
        if (itemClothing)
        {
            player.GetInventory().LocalDestroyEntity(itemClothing); // Remove the default clothing in Body slot
        }
        itemClothing = player.GetInventory().CreateAttachment("HuntingJacket_Winter"); // Add Hunting Jacket to Body slot

        // Backpack Selection
        string backpackArray[] = { "TaloonBag_Orange"  }; // Lets keep the array for now
        itemClothing = player.GetInventory().CreateInInventory(backpackArray[0]);

        // Random Canned Food
        string cannedFoodArray[] = { "SpaghettiCan", "BakedBeansCan", "TunaCan" };
        int foodIndex = Math.RandomInt(0, 3);
        player.GetInventory().CreateInInventory(cannedFoodArray[foodIndex]);

        if (itemClothing)
        {
            // Random Knife
            string knifeArray[] = { "KitchenKnife", "SteakKnife", "HuntingKnife", "CombatKnife" };
            int knifeIndex = Math.RandomInt(0, 4);
            itemClothing.GetInventory().CreateInInventory(knifeArray[knifeIndex]);
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