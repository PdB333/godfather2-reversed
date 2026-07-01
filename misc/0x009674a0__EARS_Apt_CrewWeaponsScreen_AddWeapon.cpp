// Xbox PDB: EARS_Apt_CrewWeaponsScreen_AddWeapon
// FUNC_NAME: WeaponManager::addWeapon
// Address: 0x009674a0
// Role: Adds a weapon to the player's inventory, logs event, increments counter, and calls callback.

void __thiscall WeaponManager::addWeapon(void* thisPtr, const char* weaponName, int param_3, int param_4, void (*callback)(const char*))
{
    // If weaponName is null, use a default empty string (global empty string)
    const char* actualName = (weaponName != nullptr) ? weaponName : &DAT_0120546e; // likely empty string

    // Log the "AddWeapon" event with some constant (maybe weapon ID or type)
    // FUN_005a04a0 is likely an event logger or dispatcher; first param is event name string
    // Second param 0 possibly reserved, third param &DAT_00d8cdec is a constant (maybe an identifier like weapon type)
    // Fourth param 1 might be a flag (e.g., success), fifth is the name
    FUN_005a04a0("AddWeapon", 0, &DAT_00d8cdec, 1, actualName);

    // Increment weapon counter at offset 0x14 (e.g., total weapon count)
    *(int*)((int)thisPtr + 0x14) = *(int*)((int)thisPtr + 0x14) + 1;

    // If a weapon name was provided, call the callback with it (e.g., for HUD or effects)
    if (weaponName != nullptr)
    {
        callback(weaponName);
    }
}