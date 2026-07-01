// FUNC_NAME: Player::canPerformAction
char __thiscall Player::canPerformAction(int thisPtr) {
    char cVar1;
    int componentPtr;
    int obj1, obj2;
    char result;

    componentPtr = *(int *)(thisPtr + 0x5c); // Component pointer, offset 0x5c
    result = 1; // Default: allowed

    // Check blocking conditions
    if (((((*(byte *)(componentPtr + 0x8e6) & 1) != 0) && // Bit 0 of flag at +0x8e6
          (cVar1 = isMovementLocked(), cVar1 != 0)) ||    // Some movement lock check
         ((*(int *)(componentPtr + 0x2124) != 0 &&         // Non-null pointer at +0x2124
          ((cVar1 = isInVehicle(), cVar1 != 0 &&           // In vehicle?
           ((*(uint *)(*(int *)(thisPtr + 0x5c) + 0x1f98) & 0x50c) != 0)))))) || // Flags at +0x1f98
        ((cVar1 = checkStateFlags(*(int *)(thisPtr + 0x5c), 2), cVar1 != 0 &&     // Check state 2
         ((*(uint *)(*(int *)(thisPtr + 0x5c) + 0x1f98) >> 7 & 1) == 0)))) {     // Bit 7 of flag at +0x1f98
        result = 0; // Blocked
    }

    if (**(int **)(DAT_012233a0 + 4) == 0) { // Global singleton at +4
        obj1 = 0;
    } else {
        obj1 = **(int **)(DAT_012233a0 + 4) + -0x1f30; // Subtract offset to get actual object
    }

    if (result == 0) {
        return 0;
    }

    cVar1 = isObjectActive(obj1); // Check if the object is valid/active
    if (cVar1 != 0) {
        if (obj1 == 0) {
            return result;
        }
        obj1 = getTimeObject(); // e.g., GetCurrentTimeStruct
        obj2 = getTimeObject(); // e.g., GetLastEventTimeStruct
        if ((float)((uint)(*(float *)(obj1 + 0x34) - *(float *)(obj2 + 0x34)) & DAT_00e44680) <
            DAT_00d5eee4) { // Time delta comparison with threshold
            return 1;
        }
    }
    return 0;
}