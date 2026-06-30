// FUNC_NAME: Player::processHitResponse
void __thiscall Player::processHitResponse(float damageAmount) // param_2 is damage
{
    // +0x39c: isDead? (byte)
    if (*(char*)(this + 0x39c) == '\0') // not dead
    {
        int* pWeaponPtr = (int*)(this + 0x374); // +0x374: pointer to current weapon/attack component
        if ((*pWeaponPtr != 0) && (*pWeaponPtr != 0x48)) // 0x48 = invalid? sentinel
        {
            // If the pointer is not 0 and not 0x48, it might be a handle that needs cleanup?
            if (((*pWeaponPtr == 0) || (*pWeaponPtr == 0x48)) && (*pWeaponPtr != 0))
            {
                FUN_004daf90(pWeaponPtr); // delete/release component
                *pWeaponPtr = 0;
            }
            // ... nested logic (see below)
        }
        else
        {
            char state = *(char*)(this + 0x1ad); // +0x1ad: character state
            if ((((state == 0x1a) || (state == 0x1b)) && (*(int*)(this + 0x2d4) != 0)) && 
                (*(int*)(this + 0x2d4) != 0x48) &&
                (((*(int*)(this + 0x364) != 0) || (*(int*)(this + 0x368) != 0) ||
                  (*(int*)(this + 0x36c) != 0) || (*(int*)(this + 0x370) != 0))))
            {
                // +0x364-0x370: hit zones (four ints)
                int hitZoneIndex = FUN_00446100(this + 0x364, 0); // find active hit zone
                if (hitZoneIndex != 0)
                {
                    uint hash = 0x346d561a; // Some hash (e.g., "head" or "body")
                    int component = FUN_0070afb0(hitZoneIndex, hash); // get component by hash
                    FUN_0070af00(component); // apply effect (e.g., damage scaling)
                }
                // If weapon component exists and state is 0x1a, continue inner loop
                if (((*pWeaponPtr != 0) && (*pWeaponPtr != 0x48)) && (state == 0x1a))
                {
                    int weaponBase = (*pWeaponPtr == 0) ? 0 : (*pWeaponPtr - 0x48);
                    if (*(int*)(weaponBase + 0x1a8) == 0) // some flag? maybe "canBeUsed"?
                        goto LAB_0070c998; // go to inner processing
                }
                // If state == 0x1b
                if (state == 0x1b)
                {
                    int weaponBase = (*pWeaponPtr == 0) ? 0 : (*pWeaponPtr - 0x48);
                    if (*(int*)(weaponBase + 0x1a8) == 1) // flag == 1
                        goto LAB_0070c998;
                }
                // Otherwise, release weapon component
                if (*pWeaponPtr != 0)
                {
                    FUN_004daf90(pWeaponPtr);
                    *pWeaponPtr = 0;
                }
            }
            // If not dead, use the damage from this+0x310
            if (*(char*)(this + 0x39c) == '\0')
            {
                damageAmount = *(float*)(this + 0x310); // +0x310: current damage/health float
            }
        }
    }

    // Update global damage stat (0xbc is some global data pointer)
    FUN_00440590(&DAT_0112ac6c, this + 0x3c, damageAmount, 0, 4); // +0x3c: time? or ID?

    // If not dead and some condition (maybe check for blood effect)
    if ((*(char*)(this + 0x39c) == '\0') && (FUN_00481620() != '\0'))
    {
        // Spawn particle effect based on damage
        float scaledDamage = *(float*)(this + 0x310) * DAT_00d60d04; // multiplier
        int particleID = FUN_0090e2d0(0, (int)scaledDamage, 2, 0, 0, 0); // spawn particle
        *(int*)(this + 0x398) = particleID; // store particle handle
    }

    // Inner processing label (from multiple points)
LAB_0070c998:
    if ((*pWeaponPtr != 0) && (*pWeaponPtr != 0x48))
    {
        if (*pWeaponPtr == 0)
        {
            // no operation? (piVar6=0)
        }
        else
        {
            int* weaponData = (int*)(*pWeaponPtr - 0x48);
            // Call virtual function at vtable+0x14c (likely 'canApplyDamage' or something)
            char canApply = (*(code**)(*weaponData + 0x14c))(); // call to weapon virtual
            if (canApply)
            {
                // Clear some flag on weapon
                int weaponBase = (*pWeaponPtr == 0) ? 0 : (*pWeaponPtr - 0x48);
                FUN_00402050(weaponBase + 0x1c8, 0); // clear flag at +0x1c8

                int source = this + 0x3c;
                float weaponDamage = *(float*)(weaponBase + 0x1ac); // damage value from weapon

                // Update global stat with weapon damage
                FUN_00440590(&DAT_0112ac6c, source, weaponDamage, 0, 4);

                // If damage exceeds threshold, apply extra damage
                if (DAT_00d61438 < weaponDamage)
                {
                    float extra = weaponDamage - DAT_00d61438;
                    FUN_00440590(&DAT_0112ac5c, source, extra, 0, 0); // add to another stat
                }

                // Mark weapon as used (clear bit 0 at +0x1a4)
                *(uint*)(weaponBase + 0x1a4) &= 0xfffffffe;
                FUN_008da380(); // some global update

                // Check if character is in a specific state (0x1a) and a flag at +0x39e bit 3
                if ((*(char*)(this + 0x1ad) == 0x1a) && ((*(byte*)(this + 0x39e) >> 3 & 1) != 0))
                {
                    char canTransition = FUN_0070c650(); // check if can transition to second hit reaction
                    if (canTransition == '\0')
                    {
                        // Cannot transition: clear flags, reset animation, release weapon
                        int weaponBase2 = (*pWeaponPtr == 0) ? 0 : (*pWeaponPtr - 0x48);
                        FUN_00402050(weaponBase2 + 0x1d8, 0); // clear flag
                        weaponBase2 = (*pWeaponPtr == 0) ? 0 : (*pWeaponPtr - 0x48);
                        FUN_004088c0(weaponBase2 + 0x3c); // reset timer on weapon
                        if (*pWeaponPtr != 0)
                        {
                            FUN_004daf90(pWeaponPtr);
                            *pWeaponPtr = 0;
                        }
                        FUN_004088c0(this + 0x3c); // reset timer on self
                    }
                    else
                    {
                        // Transition to second hit reaction
                        FUN_0045ca00(this); // apply second hit animation (e.g., stagger)

                        int weaponBase3 = (*pWeaponPtr == 0) ? 0 : (*pWeaponPtr - 0x48);
                        // Prepare a vector? or position from weapon
                        __int64 vec = *(undefined4*)(weaponBase3 + 0x1d0); // 4 bytes
                        // (the rest is unclear, but seems to pass to another function)
                        FUN_00408a00(&vec, 0); // handle vector/point
                        FUN_0045cac0(); // finalize transition
                    }
                }
            }
        }
    }

    // After all, update another global stat with some offset
    if ((*(int*)(this + 0x3a0) != 0) && (*(int*)(this + 0x3a0) != 0x48))
    {
        int handle = *(int*)(this + 0x3a0);
        if ((handle == 0) || (handle == 0x48))
            handle = 0;
        else
            handle = handle - 0xc; // offset
        float value = *(float*)(this + 0x310) + DAT_00d5d7b8;
        FUN_00440590(&DAT_0112abd8, handle, value, 0, 4);
    }

    // Call final update function with ID 9 (maybe update HUD or state)
    FUN_0043c490(this, 9);
    return;
}