// FUNC_NAME: Player::holsterWeapon
void __fastcall Player::holsterWeapon(void)
{
    int* weaponSlotPtr = *(int**)(this + 0x74c); // +0x74c: weapon slot pointer (points to weapon object member at offset 0x48)
    if (weaponSlotPtr != nullptr && weaponSlotPtr != (int*)0x48)
    {
        // Weapon base object is at offset -0x48 from the slot pointer
        int* weaponBase = (weaponSlotPtr != nullptr) ? (weaponSlotPtr - 0x48) : nullptr; // +0x00: weapon vtable
        if (weaponBase != nullptr)
        {
            // Call weapon->setReference("r_weapon", 0) via vtable+0x154
            (*(void(__thiscall*)(int*, const char*, int))(*weaponBase + 0x154))(weaponBase, "r_weapon", 0);
            // Call weapon->detach() via vtable+0x88
            (*(void(__thiscall*)(int*))(*weaponBase + 0x88))(weaponBase);
            // Check weapon status byte at +0x1ad
            if (*(char*)(weaponBase + 0x1ad) != 0)
            {
                if (*(char*)(weaponBase + 0x1ad) != 1)
                {
                    // Call weapon->playAnimation() via vtable+0x70
                    (*(void(__thiscall*)(int*))(*weaponBase + 0x70))(weaponBase);
                    // Update animation system (likely related to weapon holster)
                    FUN_007091d0();
                }
            }
        }
        // Check flag at +0x8e0 bit 10 (0x400)
        if (!(*(uint32_t*)(this + 0x8e0) & 0x400))
        {
            // Call component->setAnimationFlag(0x20) via vtable at +0x28 from component pointer at +0x58
            (*(void(__thiscall*)(int))(*((int*)this + 0x58) + 0x28))(0x20);
        }
        // Set the flag to indicate weapon is holstered
        *(uint32_t*)(this + 0x8e0) |= 0x400;
    }
}