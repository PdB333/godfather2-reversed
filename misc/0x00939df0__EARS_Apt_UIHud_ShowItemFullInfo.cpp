// Xbox PDB: EARS_Apt_UIHud_ShowItemFullInfo
// FUNC_NAME: UIHud::notifyAmmoPickup
void UIHud::notifyAmmoPickup(int weaponType)
{
    char *ammoString;
    switch(weaponType)
    {
    case 0:
        ammoString = "$ammo_rifle_full";
        break;
    case 1:
        ammoString = "$ammo_pistol_full";
        break;
    case 2:
        ammoString = "$ammo_magnum_full";
        break;
    case 3:
        ammoString = "$ammo_automatic_full";
        break;
    case 4:
        ammoString = "$ammo_shotgun_full";
        break;
    // case 5 is not used (possibly invalid or future weapon type)
    case 6:
        ammoString = "$ammo_molotov_full";
        break;
    case 7:
        ammoString = "$ammo_dynamite_full";
        break;
    case 8:
        ammoString = "$ammo_bomb_full";
        break;
    default:
        return; // invalid weapon type, do nothing
    }
    // Call the actual UI notification display function
    // The third parameter (g_hudManager) is a global HUD instance pointer (0x00d8a64c)
    FUN_005a04a0("ShowAmmoPickUpInfo", 0, &g_hudManager, 1, ammoString);
}