// FUNC_NAME: WeaponManager::equipWeapon
void __thiscall WeaponManager::equipWeapon(int thisPtr, int weaponHash)
{
    int *weaponDataPtr;
    int *vtableOffset;
    int result;

    // Step 1: Lock or mark something (e.g., mutex or reference count)
    sub_007ff050(0);

    // Get weapon data pointer from hash (likely asset or template lookup)
    weaponDataPtr = (int *)sub_00709fc0(weaponHash);
    if (weaponDataPtr == (int *)0x0)
        return;

    // Check magic sentinel values (known vtable markers for "null" or "empty")
    // The four ints at weaponDataPtr are compared against these constants:
    // -0x45245246 = 0xBBABDBBA
    // -0x41104111 = 0xBEEFBEEF
    // -0x153ea5ab = 0xEAC15A55
    // -0x6eeff6ef = 0x91100911
    // If any match, treat as invalid or uninitialized weapon.
    if ((*weaponDataPtr == -0x45245246) && (weaponDataPtr[1] == -0x41104111) &&
        (weaponDataPtr[2] == -0x153ea5ab) && (weaponDataPtr[3] == -0x6eeff6ef))
    {
        return;
    }
    if ((*weaponDataPtr == 0) && (weaponDataPtr[1] == 0) &&
        (weaponDataPtr[2] == 0) && (weaponDataPtr[3] == 0))
    {
        return;
    }

    // Access a member at offset 0x1e9c (likely a linked list or container of weapon slots)
    vtableOffset = (int *)(thisPtr + 0x1e9c);
    // Create or reference the weapon instance using data pointer, resource ID at +0x1c
    result = sub_00856780(weaponDataPtr, *(int *)(thisPtr + 0x1c), 0, 0, 0);
    sub_006906e0(result); // Possibly increment reference count or set owner

    // If the slot is occupied and not a special sentinel (0x48 seems unusual - maybe empty slot marker)
    if ((*vtableOffset != 0) && (*vtableOffset != 0x48))
    {
        sub_00481570(); // Something like detach or cleanup
        // Compute base of weapon object from slot pointer (offset -0x48 bytes)
        if (*vtableOffset == 0)
            weaponDataPtr = (int *)0x0;
        else
            weaponDataPtr = (int *)(*vtableOffset - 0x48);

        // Call vtable method at +0x154: set resource "r_weapon" to 0 (detach?)
        (*(void (__thiscall **)(int, const char *, int))(weaponDataPtr[0] + 0x154))(thisPtr, "r_weapon", 0);

        // Again compute base pointer for next call
        if (*vtableOffset == 0)
            weaponDataPtr = (int *)0x0;
        else
            weaponDataPtr = (int *)(*vtableOffset - 0x48);

        // Call vtable method at +0x70: probably cleanup or release
        (*(void (__thiscall **)(int))(weaponDataPtr[0] + 0x70))();

        sub_007091d0(); // Possibly update state

        // If slot is still valid, call vtable method at +0x174 (finalize?)
        if (*vtableOffset != 0)
        {
            (*(void (__thiscall **)(int))(*(int *)(*vtableOffset - 0x48) + 0x174))(thisPtr);
            return;
        }
        // Fallback (if slot became null) – does nothing safe? Actually this would crash.
        // The decompiler may have inserted a null pointer call; in practice this branch is never reached.
        // Possibly it's a miscompilation; ignore.
    }
}