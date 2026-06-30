// FUNC_NAME: Player::updateInteractionFlags
void __thiscall Player::updateInteractionFlags(int thisObj, bool enable, int excludeEntity, bool forceOverride)
{
    // thisObj: player object (likely Player class)
    // enable: if true, attempt to set block flags; if false, clear block flags
    // excludeEntity: entity pointer or ID to skip in checks (0 if none)
    // forceOverride: if true, bypass global condition check

    if (enable)
    {
        // Access the nearby entities list at this+0x18 (pointer to a list manager)
        int listMgr = *(int *)(thisObj + 0x18);  // +0x18: pointer to NearbyEntityList
        int count = 0;
        if (0 < *(int *)(listMgr + 0x154))       // +0x154: entity count
        {
            do
            {
                int entity = *(int *)(*(int *)(listMgr + 0x150) + count * 4); // +0x150: array of entity pointers
                int derivedPtr;
                // Check if the entity's vtable type flag at +0x18 is 1
                if (*(char *)(entity + 0x18) == 1)   // +0x18: type indicator
                {
                    // Adjust to derived class by reading vtable offset stored at entity+0x10
                    derivedPtr = *(char *)(entity + 0x10) + entity; // +0x10: virtual base offset (signed char)
                }
                else
                {
                    derivedPtr = 0;
                }

                bool globalCondition = FUN_0054ea60(); // Check if some global condition is active (e.g., mission state)

                // If the derived entity exists, has a state at +0xd8 not equal to 7 (e.g., not dead),
                // and is not the excluded entity, then block flags cannot be set.
                if ((derivedPtr != 0) && (*(char *)(derivedPtr + 0xd8) != 7) && (derivedPtr != excludeEntity))
                {
                    return; // Abort - cannot set flags
                }

                // If global condition is active and we are not forcing override, abort
                if ((globalCondition) && (forceOverride == false))
                {
                    return; // Abort - global condition prevents setting flags
                }

                count++;
            } while (count < *(int *)(listMgr + 0x154));
        }

        // All conditions passed, set flags
        *(uint *)(thisObj + 0xe4) |= 0x40;   // +0xe4: flags bitmask (bit 6 = block interaction A)
        *(uint *)(thisObj + 0xe4) |= 0x100;  // bit 8 = block interaction B
        return;
    }

    // If enable is false, clear flag bit 6, set bit 8
    *(uint *)(thisObj + 0xe4) &= ~0x40;
    *(uint *)(thisObj + 0xe4) |= 0x100;
}