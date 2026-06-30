// FUNC_NAME: CharacterWeaponManager::getAmmoStatusPacked
// Address: 0x0071f710
// Returns a packed uint32: low byte = 1 if remaining ammo < 5, upper 24 bits = (remainingAmmo - 1) >> 8.
// this->+4 is a pointer to current weapon data, subtract 0x48 to get owning CharacterBase.
// CharacterBase+0x200c holds a pointer to inventory array; inventory entry+0x14 is ammo count.
uint32 __thiscall CharacterWeaponManager::getAmmoStatusPacked(CharacterWeaponManager* thisFunc)
{
    char* weaponDataPtr = *(char**)((char*)thisFunc + 4); // +4: pointer to current WeaponData entry
    CharacterBase* character;
    if (weaponDataPtr == 0) {
        character = 0;
    } else {
        character = (CharacterBase*)(weaponDataPtr - 0x48); // weaponData is at offset 0x48 in CharacterBase
    }
    int* inventoryPtr = *(int**)((char*)character + 0x200c); // +0x200c: pointer to inventory array in CharacterBase
    if (inventoryPtr != 0) {
        uint ammoRemaining = *(uint*)((char*)inventoryPtr + 0x14) - 1; // +0x14: ammo count field
        uint32 result = ((ammoRemaining >> 8) & 0xFFFFFF) << 8; // upper 24 bits = ammoRemaining / 256
        result |= (ammoRemaining < 5) ? 1 : 0; // low byte = low ammo flag
        return result;
    }
    // Fallback to static default ammo value
    uint defaultRemaining = g_defaultAmmoCount - 1; // _DAT_00000050
    uint32 result = ((defaultRemaining >> 8) & 0xFFFFFF) << 8;
    result |= (defaultRemaining < 5) ? 1 : 0;
    return result;
}