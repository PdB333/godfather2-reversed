// FUNC_NAME: PlayerCharacter::updateWeaponSounds
// Address: 0x007ea0b0
// Role: Plays appropriate weapon sound effects based on player state and weapon type (silenced/unsilenced)

void __thiscall PlayerCharacter::updateWeaponSounds(void* this)
{
    // Get the weapon system pointer (offset 0x7c from this)
    int* weaponSystem = *(int**)((char*)this + 0x7c);
    // Call vtable+0x34 to get current weapon data
    int* currentWeapon = (*(int*(*)(int*))(*(int*)weaponSystem + 0x34))(weaponSystem);
    
    int* player = *(int**)((char*)this + 0x58); // Player character pointer at +0x58
    bool isSilenced = isWeaponSilenced(player, currentWeapon); // FUN_007e9b00
    
    char playerState = *(char*)((char*)player + 0x1b8c); // +0x1b8c: movement state (0=idle,1=walk,2=run,3=sprint,4=crouch)
    uint weaponID = *(uint*)((char*)currentWeapon + 0x3c); // +0x3c: weapon identifier
    
    // Get the playSound method pointer (vtable+0x2c)
    void (*playSound)(int, int, int, int, float, float) = *(void (**)())(*(int*)this + 0x2c);
    
    // State dispatch
    if (playerState == 0) // Idle
    {
        // Check if weapon is pistol category
        if ((weaponID == *(uint*)((char*)player + 0x68c) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x674) >> 2))
        {
            if (isSilenced)
                playSound(0x8de4ca5d, 1, 1, 0, 1.0f, 1.0f);
            else
                playSound(0x76ab6c71, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        // Weapon category: shotgun
        if (weaponID == *(uint*)((char*)player + 0x670) >> 2)
        {
            if (isSilenced)
                playSound(0x8de4ca5d); // silent variant
            else
                playSound(0x5d8c4a78, 1, 1, 0, 1.0f, 1.0f); // unsilenced fallback
            return;
        }
        // Weapon category: sniper
        if (weaponID == *(uint*)((char*)player + 0x6b8) >> 2)
        {
            if (isSilenced)
                playSound(0x19b1d3f6, 1, 1, 0, 1.0f, 1.0f);
            else
                playSound(0x5d8c4a78, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        // Rifle category (multiple IDs)
        if ((weaponID == *(uint*)((char*)player + 0x678) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x67c) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x680) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x684) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x688) >> 2))
        {
            if (isSilenced)
                playSound(0x1162e8c9, 1, 1, 0, 1.0f, 1.0f);
            else
                playSound(0x27cff3b5, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        // SMG category
        if ((weaponID == *(uint*)((char*)player + 0x6a0) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x6a4) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x6a8) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x6ac) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x6b0) >> 2))
        {
            if (isSilenced)
                playSound(0x8237d37a, 1, 1, 0, 1.0f, 1.0f);
            else
                playSound(0x11f9838e, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        // Melee category
        if ((weaponID == *(uint*)((char*)player + 0x66c) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x668) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x664) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x660) >> 2))
        {
            if (isSilenced)
                playSound(0xd752846, 1, 1, 0, 1.0f, 1.0f);
            else
                playSound(0x2d309f32, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        // Heavy weapon category
        if ((weaponID == *(uint*)((char*)player + 0x69c) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x698) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x694) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x690) >> 2))
        {
            if (isSilenced)
                playSound(0xca32733d, 1, 1, 0, 1.0f, 1.0f);
            else
                playSound(0x1040b751, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        // Default fallback (pistol sound)
        playSound(0x8de4ca5d, 1, 1, 0, 1.0f, 1.0f);
        return;
    }
    else if ((playerState == 1) || (playerState == 4)) // Walking or crouching
    {
        // Pistol category (silenced/unsilenced handled later)
        if ((weaponID != *(uint*)((char*)player + 0x68c) >> 2) &&
            (weaponID != *(uint*)((char*)player + 0x674) >> 2))
        {
            // Rifle category
            if ((weaponID == *(uint*)((char*)player + 0x678) >> 2) ||
                (weaponID == *(uint*)((char*)player + 0x67c) >> 2) ||
                (weaponID == *(uint*)((char*)player + 0x684) >> 2) ||
                (weaponID == *(uint*)((char*)player + 0x688) >> 2))
            {
                if (isSilenced)
                {
                    playSound(0x8914c80e, 1, 1, 0, 1.0f, 1.0f);
                    return;
                }
                // else go to silenced fallback?
                playSound(0xd642c575); // silenced fallback sound
                return;
            }
            // SMG category
            if ((weaponID == *(uint*)((char*)player + 0x6a0) >> 2) ||
                (weaponID == *(uint*)((char*)player + 0x6a4) >> 2) ||
                (weaponID == *(uint*)((char*)player + 0x6a8) >> 2) ||
                (weaponID == *(uint*)((char*)player + 0x6ac) >> 2) ||
                (weaponID == *(uint*)((char*)player + 0x6b0) >> 2))
            {
                if (isSilenced)
                {
                    playSound(0x8914c80e, 1, 1, 0, 1.0f, 1.0f);
                    return;
                }
                playSound(0xd642c575); // silenced fallback
                return;
            }
            // Otherwise check weapon type sub ID (at +0x30)
            if (*(int*)((char*)currentWeapon + 0x30) != 5)
            {
                playSound(0x9f397fd8, 1, 1, 0, 1.0f, 1.0f);
                return;
            }
            // Special case: trigger reload animation and fallback to default pistol sound
            startWeaponReloadAnimation(0, 1); // FUN_007ab9a0
            playSound(0x8de4ca5d, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        // Pistol category (unhandled above) - play footstep?
        playSound(0x9f397fd8, 1, 1, 0, 1.0f, 1.0f);
    }
    else if ((playerState == 2) || (playerState == 3)) // Running or sprinting
    {
        // Pistol category
        if ((weaponID == *(uint*)((char*)player + 0x68c) >> 2) ||
            (weaponID == *(uint*)((char*)player + 0x674) >> 2))
        {
            playSound(0xcc610fa, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        // Shotgun, melee, heavy categories
        if ((weaponID != *(uint*)((char*)player + 0x670) >> 2) &&
            (weaponID != *(uint*)((char*)player + 0x66c) >> 2) &&
            (weaponID != *(uint*)((char*)player + 0x69c) >> 2))
        {
            playSound(0x4eb13e2d, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        playSound(0x4eb13e2d, 1, 1, 0, 1.0f, 1.0f);
    }
    // No action for other states (e.g., 0x05 etc.)
}