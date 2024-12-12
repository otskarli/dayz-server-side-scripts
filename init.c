#include "$CurrentDir:mpmissions\dayzOffline.chernarusplus\DayzServerSideScripts\StartingEquipSetupMission\StartingEquipSetupMission.c"
#include "$CurrentDir:mpmissions\dayzOffline.chernarusplus\DayzServerSideScripts\RandomLootSpawner\RandomLootSpawner.c"

// Entry point for the server-side script
void main()
{
    // INIT ECONOMY--------------------------------------
    Hive ce = CreateHive();
    if (ce)
        ce.InitOffline();

    // DATE RESET AFTER ECONOMY INIT-------------------------
    int year, month, day, hour, minute;
    int reset_month = 9, reset_day = 20;
    GetGame().GetWorld().GetDate(year, month, day, hour, minute);

    if ((month == reset_month) && (day < reset_day))
    {
        GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
    }
    else
    {
        if ((month == reset_month + 1) && (day > reset_day))
        {
            GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
        }
        else
        {
            if ((month < reset_month) || (month > reset_month + 1))
            {
                GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
            }
        }
    }

    InitLootSpawner();
}