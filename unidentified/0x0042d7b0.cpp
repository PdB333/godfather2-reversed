// FUN_0042d7b0: InventoryManager::calculateTotalDamage
int InventoryManager::calculateTotalDamage()
{
    int totalDamage = 0;
    int* weaponManager = (int*)getWeaponManager(); // FUN_0042e5e0
    initIterator(weaponManager); // FUN_0042a3f0

    int slotCount = *(unsigned short*)(this + 0x1a); // number of weapon slots
    unsigned short* slotIndices = *(unsigned short**)(this + 0x1c); // array of weapon indices
    int* weaponTableBase = *(int**)(this + 0x10); // base of weapon table (each entry 0x20 bytes)

    for (int i = 0; i < slotCount; i++)
    {
        int weaponIndex = slotIndices[i];
        int* weaponEntry = weaponTableBase + weaponIndex * 0x20; // each weapon entry is 32 bytes
        if (weaponEntry != nullptr)
        {
            // Check if weapon type is 1 (e.g., primary weapon)
            int* weaponData = *(int**)(weaponEntry + 0x10); // +0x10 points to weapon data
            if (weaponData != nullptr && *(char*)(weaponData + 4) == 0x01)
            {
                totalDamage += getWeaponDamage(weaponEntry, 0); // FUN_00459b30
            }
        }
    }
    return totalDamage;
}