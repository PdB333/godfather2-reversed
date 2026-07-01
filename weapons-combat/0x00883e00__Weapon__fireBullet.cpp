// FUNC_NAME: Weapon::fireBullet
#include <cstdint>

void __thiscall Weapon::fireBullet(char param_2, char param_3)
{
    // 'this' as int* for offset calculations
    int* const pThis = reinterpret_cast<int*>(this);

    // Local variable for storing a position result from vtable call
    int local_e4 = 0;
    int local_e0 = 0;

    // Offset 0x14: pointer to weapon data object (may be encoded with 0x48 sentinel)
    int* pWeaponData = reinterpret_cast<int*>(pThis[0x14]);
    if (pWeaponData != nullptr && pWeaponData != reinterpret_cast<int*>(0x48))
    {
        // Subtract 0x48 bytes to get the actual base object (component?)
        int* pBase = reinterpret_cast<int*>(reinterpret_cast<char*>(pWeaponData) - 0x48);
        int* const vtableBase = reinterpret_cast<int*>(*pBase);

        // Virtual call at vtable+0x1ec (index 0x7B): get position from pThis+0x17 (muzzle?)
        auto getMuzzlePos = reinterpret_cast<void (*)(int*, int*)>(vtableBase[0x7B]);
        getMuzzlePos(pThis + 0x17, &local_e4);

        // Check flag bit 1 of field at +0x1D (offset 0x74) and that both params are zero
        if (((static_cast<uint32_t>(pThis[0x1D]) >> 1 & 1) != 0) && (param_2 == 0) && (param_3 == 0))
        {
            // Get a sound handle
            int soundID = FUN_0054eb10(); // assume returns sound ID
            // Play sound at location? (0x40102 may be a channel flag)
            FUN_00540bc0(0x40102, soundID, 0, 0);

            // Virtual call at +0xA4 (index 0x29): get a target position from pThis+0x18 (aim?)
            float fPos[3]; // local stack vector
            auto getAimPos = reinterpret_cast<void (*)(float*, int*)>(vtableBase[0x29]);
            getAimPos(fPos, pThis + 0x18);

            // Apply global offset to Y component
            fPos[1] += _DAT_00d5c458; // global constant

            // (Omitted: bitwise manipulation of fPos[1] to zero low byte – likely alignment padding)
            // i.e., fPos[1] = (float)((uint32_t)fPos[1] & 0xFFFFFF00);

            // Create projectile/effect via FUN_00540cc0 (returns an effect handle)
            // The stack array is constructed from fPos and some globals
            int effectID = FUN_00540cc0(/* stack array */);

            // Second call to get another position? Using a different source
            float fPos2[3];
            getAimPos(fPos2, &stack0xffffff10); // unknown stack address – possibly previous effect instance?
            fPos2[0] += DAT_00d5ef6c; // offset to X

            // Setup structure for FUN_009e69d0 (likely manages particle/decal)
            // Constants: uStack_64 = -1, uStack_58 = -1, uStack_b8 = local_e0, uStack_ac = _DAT_00d5780c, etc.
            // Also fPos2[1] is taken from earlier fPos[1] after clearing?
            // piStack_28 is initially null
            int* piStack_28 = nullptr; // result pointer from FUN_009e69d0
            FUN_009e69d0(&uStack_c8, &auStack_78); // pass local arrays

            if (piStack_28 != nullptr && *(int*)(*piStack_28 + 0xC) == 0xB)
            {
                // Hit something that needs cleanup
                FUN_00624d00();
                return;
            }
        }

        // Virtual call at +0x264 (index 0x99): maybe start muzzle flash?
        auto startFlash = reinterpret_cast<void (*)(int)>(vtableBase[0x99]);
        startFlash(pThis[0x16]); // pThis+0x16 is the weapon model object

        // Call virtual on the weapon model object itself (vtable offset 0x1B0 = index 0x6C)
        int* pModel = reinterpret_cast<int*>(pThis[0x16]);
        int* const vtableModel = reinterpret_cast<int*>(*pModel);
        auto modelCall = reinterpret_cast<void (*)(int*)>(vtableModel[0x6C]);
        modelCall(pBase); // pass the base object as argument
    }

    // General sound/effect after potential shot
    FUN_005512c0(2); // e.g., play gunshot sound (parameter 2 = weapon sound?)

    // Store the hit position (local_e4, local_e0) into the weapon model at offsets +0x860, +0x864
    int* pModel = reinterpret_cast<int*>(pThis[0x16]);
    *(reinterpret_cast<int*>(reinterpret_cast<char*>(pModel) + 0x860)) = local_e4;
    *(reinterpret_cast<int*>(reinterpret_cast<char*>(pModel) + 0x864)) = local_e0;

    // Debug/logging
    FUN_007f63e0(0x4F);
    FUN_007f7e40();

    // Get base object again
    int* pWeaponData2 = reinterpret_cast<int*>(pThis[0x14]);
    int* pBase2 = (pWeaponData2 != nullptr && pWeaponData2 != reinterpret_cast<int*>(0x48)) ?
                  reinterpret_cast<int*>(reinterpret_cast<char*>(pWeaponData2) - 0x48) : nullptr;

    // Call FUN_00883d70 on the base, returns a char that modifies a local float (byte manipulation)
    char c = FUN_00883d70(pBase2);
    // The float manipulation is omitted for brevity (CONCAT31 on fStack_dc)

    if (param_3 == 0)
    {
        if (param_2 == 0)
        {
            // Primary fire: call vtable+0x2C (index 0xB) on this object
            auto finalShootFunc = reinterpret_cast<void (*)(float, int, int, int, int, float)>(reinterpret_cast<int**>(pThis)[0xB]);
            // 0x46f5c7b4 = some damage/force constant, 1/1 = flags, pThis[0x1E] = target, 0x3f800000 = 1.0f (speed multiplier)
            finalShootFunc(0x46f5c7b4, 1, 1, 0, pThis[0x1E], 0x3f800000);
        }
        else if (pWeaponData2 != nullptr && pWeaponData2 != reinterpret_cast<int*>(0x48))
        {
            // Alternate fire: call vtable+0x278 (index 0x9E) on base, then FUN_00875af0
            auto getSpecialValue = reinterpret_cast<int (*)(int*, float, int)>(reinterpret_cast<int**>(pBase2)[0x9E]);
            int specialVal = getSpecialValue(pThis + 0x17, /* fStack_dc from earlier */, pThis[0x1E]);
            specialVal = FUN_00875af0(reinterpret_cast<int>(pModel), specialVal);
            // Then call the same final shoot function with specialVal as first parameter
            auto finalShootFunc2 = reinterpret_cast<void (*)(int, int, int, int, int, float)>(reinterpret_cast<int**>(pThis)[0xB]);
            finalShootFunc2(specialVal, 1, 1, 0, pThis[0x1E], 0x3f800000);
            return;
        }
    }
    return;
}