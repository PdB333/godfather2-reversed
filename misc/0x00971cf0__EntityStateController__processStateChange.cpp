// FUNC_NAME: EntityStateController::processStateChange
void __fastcall EntityStateController::processStateChange(int thisPtr)
{
    // thisPtr points to an object with fields at known offsets
    // +0xDC: current state (uint)
    // +0x11C: boolean flag for state skip
    // +0x2EC: pointer to a state object (vtable at +0x2EC)
    // +0x378: pointer to another state object (vtable at +0x378)
    // virtual function at vtable+0xA4 is called (index 41)
    // FUN_00402050 releases a memory block from global heap DAT_01130448
    // FUN_009659a0 and FUN_00970b70 are related state actions

    uint state = *(uint*)(thisPtr + 0xDC);
    switch (state) {
    case 1:
        // Check if a flag is false (not skipped)
        if (*(char*)(thisPtr + 0x11C) == 0) {
            // Release memory from global heap
            FUN_00402050(&DAT_01130448, 0);
            // Call virtual function at vtable offset 0xA4 on the object at +0x2EC
            (**(code**)(*(int*)(thisPtr + 0x2EC) + 0xA4))();
        }
        break;
    case 4:
        // Direct state action
        FUN_009659a0();
        break;
    case 5:
        // Release memory, then perform another action
        FUN_00402050(&DAT_01130448, 0);
        FUN_00970b70();
        break;
    case 6:
        // Release memory, then call virtual function on object at +0x378
        FUN_00402050(&DAT_01130448, 0);
        (**(code**)(*(int*)(thisPtr + 0x378) + 0xA4))();
        break;
    }
    // No default; function returns silently for other states
}