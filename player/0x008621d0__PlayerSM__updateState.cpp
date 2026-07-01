// FUNC_NAME: PlayerSM::updateState
void __fastcall PlayerSM::updateState(int thisPtr)
{
    int *vtable;

    // Check if bit 0 of flags at +0xf28 is clear (not in a certain state)
    if ((*(byte *)(thisPtr + 0xf28) & 1) == 0) {
        // If state at +0xf2c is not 1 (not in "active" state)
        if (*(int *)(thisPtr + 0xf2c) != 1) {
            // Set bit 19 (0x80000) in flags at +0xf28
            *(uint *)(thisPtr + 0xf28) = *(uint *)(thisPtr + 0xf28) | 0x80000;
        }
        // Call some function with parameter 0
        FUN_0087f870(0);
        // Set state to 1 (active)
        *(undefined4 *)(thisPtr + 0xf2c) = 1;
        // Clear bit 18 (0x40000) in flags at +0xf28
        *(uint *)(thisPtr + 0xf28) = *(uint *)(thisPtr + 0xf28) & 0xfffbffff;
        
        // Get vtable pointer from +0x130
        vtable = *(int **)(thisPtr + 0x130);
        if (vtable != (int *)0x0) {
            // Call vtable method at offset 0x48 (0x48/4 = 18th method) with two parameters
            (**(code **)(*vtable + 0x48))(0xe143e67d, 0);
            (**(code **)(*vtable + 0x48))(0xbe171efb, 0);
        }
        
        // Check if bit 14 (0x4000) is NOT set in flags at +0xc88
        if ((*(uint *)(thisPtr + 0xc88) | 0x4000) != *(uint *)(thisPtr + 0xc88)) {
            // Call vtable method at offset 0x28 (0x28/4 = 10th method) with parameter 0x10
            (**(code **)(*(int *)(thisPtr + 0x58) + 0x28))(0x10);
            // Set bit 14 (0x4000) in flags at +0xc88
            *(uint *)(thisPtr + 0xc88) = *(uint *)(thisPtr + 0xc88) | 0x4000;
        }
    }
    
    // Check if global _DAT_00d577a0 is <= float at +0x1034
    if (_DAT_00d577a0 <= *(float *)(thisPtr + 0x1034)) {
        // Call function with float parameter
        FUN_00546940(*(float *)(thisPtr + 0x1034));
    }
}