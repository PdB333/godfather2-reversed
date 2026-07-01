// FUNC_NAME: applyResourceModifier

// Function at 0x007e7780: Adjusts a global resource (DAT_00e44564) based on decay rate, max value, and a multiplier.
// Takes an optional override value (param_2). If param_2 is null, uses a base value from global DAT_00e448d8.
// param_1 is likely an ID or handle passed to the helper FUN_008934e0 when param_2 is null.
void __cdecl applyResourceModifier(int param_1, float* param_2)
{
    int iVar1;
    int iVar2;
    float local_c;
    float local_8;
    float local_4;

    // Retrieve a global object pointer from DAT_012233a0 (likely g_simManager or g_gameManager)
    iVar1 = **(int**)(DAT_012233a0 + 4);
    if ((((iVar1 != 0) && (iVar1 != 0x1f30)) &&                // Check for invalid handle (0x1f30)
         (iVar2 = *(int*)(iVar1 + -0x58), iVar2 != 0)) &&
        (iVar2 != 0x48))                                       // Check for invalid handle (0x48)
    {
        local_4 = *(float*)(iVar2 + 0xb8);                     // Max value from derived object
        local_c = DAT_00e448d8;                                 // Base decay amount
        local_8 = _DAT_00d5c458;                                // Decay rate

        FUN_008934e0(0x16e63fc1, &local_8);                     // Possibly a hash/random function on local_8
        if (param_2 == (float*)0x0)
        {
            FUN_008934e0(param_1, &local_c);                   // Modify base decay using param_1 (ID)
        }
        else
        {
            local_c = *param_2;                                 // Override decay value
        }

        local_c = *(float*)(iVar1 + 0x23c) * local_c;          // Apply multiplier from primary object
        if (local_8 * local_4 < local_c)                       // Cap to decay rate * max
        {
            local_c = local_8 * local_4;
        }
        if (local_4 < local_c)                                 // Cap to max
        {
            local_c = local_4;
        }

        // Subtract the computed value from global resource (e.g., reputation, heat)
        FUN_008c09a0(DAT_00e44564 - local_c, 5);               // Likely sets or decrements the resource
    }
    return;
}