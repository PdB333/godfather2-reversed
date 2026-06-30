// FUNC_NAME: WeaponManager::getWeaponDamage
float WeaponManager::getWeaponDamage(int weaponType)
{
    // Convert weapon type to internal index via lookup/validation function
    int weaponIndex = weaponTypeToIndex(weaponType);
    
    // Pointer to array of weapon data structs (size 0x1D0 each)
    // Stored at this+0x10
    WeaponData* weaponArray = *(WeaponData**)(this + 0x10);
    
    // Read damage field at offset 0x40 within the weapon struct
    return weaponArray[weaponIndex].damage; // +0x40
}