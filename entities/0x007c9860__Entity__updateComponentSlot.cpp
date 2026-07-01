//FUNC_NAME: Entity::updateComponentSlot
void __thiscall Entity::updateComponentSlot(int thisPtr, undefined4 param2, int param3)
{
    int *componentNodePtr;
    int componentIndex;
    int *componentTablePtr;
    byte flagByte;
    int tableValues[4];
    int local_c0;
    undefined4 local_bc;
    undefined8 local_b4;
    undefined4 local_ac;
    byte local_a8;

    // Check if bit 0xd of flags is set and param3 is non-zero, then force param3 to 8
    if (((*(uint *)(thisPtr + 0x128) >> 0xd & 1) != 0) && (param3 != 0)) {
        param3 = 8;
    }

    // Get a value from a table indexed by something at +0x58
    local_c4 = *(undefined4 *)(&DAT_00002494 + *(int *)(thisPtr + 0x58));
    componentNodePtr = (int *)(thisPtr + 200); // +0xC8? Actually +0xC8 is 200, but offset is 0xC8? Wait: 0x200 = 512, but param_1+200 is 0xC8? No, 200 decimal = 0xC8. But the decompiled says param_1 + 200, which is 0xC8. However the code uses 0x200? Let's check: piVar1 = (int *)(param_1 + 200); That's offset 200 decimal = 0xC8. But later it uses *piVar1 and compares to 0x48. So the offset is 0xC8. I'll keep as 0xC8.
    local_c8 = DAT_0122339c; // Global singleton or constant
    flagByte = 0;
    if ((*(int *)(thisPtr + 0xC8) != 0) && (*(int *)(thisPtr + 0xC8) != 0x48)) {
        flagByte = 1;
        if (*componentNodePtr == 0) {
            componentIndex = 0;
        }
        else {
            componentIndex = *componentNodePtr - 0x48;
        }
        FUN_00424df0(local_c4, componentIndex, param2, param3, 0, 0);
    }

    FUN_006e01d0(); // Update transform or similar

    // Determine which component table to use based on flags
    if ((*(uint *)(thisPtr + 0x128) >> 0xe & 1) == 0) {
        if ((*(uint *)(thisPtr + 0x128) >> 0xd & 1) == 0) {
            componentTablePtr = (int *)(*(int *)(thisPtr + 0x58) + 0x2bd4);
        }
        else {
            componentTablePtr = (int *)(*(int *)(thisPtr + 0x58) + 0x2be4);
        }
    }
    else {
        componentTablePtr = (int *)(*(int *)(thisPtr + 0x58) + 0x2bf4);
    }

    // Read 4 ints from the table (likely a component ID or descriptor)
    tableValues[0] = *componentTablePtr;
    tableValues[1] = componentTablePtr[1];
    tableValues[2] = componentTablePtr[2];
    tableValues[3] = componentTablePtr[3];

    if ((((tableValues[0] == 0) && (tableValues[1] == 0)) && (tableValues[2] == 0)) && (tableValues[3] == 0)) {
        // No existing component, allocate a new one
        componentIndex = FUN_0043b910(0x128, 0); // Allocate 0x128 bytes
        if (componentIndex == 0) {
            componentIndex = 0;
        }
        else {
            componentIndex = FUN_006e0540(); // Initialize component
        }
        if (componentIndex == 0) {
            componentIndex = 0;
        }
        else {
            componentIndex = componentIndex + 0x48; // Offset to sub-object
        }
        if (*componentNodePtr != componentIndex) {
            if (*componentNodePtr != 0) {
                FUN_004daf90(componentNodePtr); // Remove old from list
            }
            *componentNodePtr = componentIndex;
            if (componentIndex != 0) {
                *(undefined4 *)(thisPtr + 0xCC) = *(undefined4 *)(componentIndex + 4); // Link list
                *(int **)(componentIndex + 4) = componentNodePtr;
            }
        }
    }
    else {
        // Look up existing component by table values
        componentIndex = FUN_00446130(tableValues, 0);
        if (componentIndex == 0) {
            componentIndex = 0;
        }
        else {
            componentIndex = componentIndex + 0x48;
        }
        if (*componentNodePtr != componentIndex) {
            if (*componentNodePtr != 0) {
                FUN_004daf90(componentNodePtr);
            }
            *componentNodePtr = componentIndex;
            if (componentIndex != 0) {
                *(undefined4 *)(thisPtr + 0xCC) = *(undefined4 *)(componentIndex + 4);
                *(int **)(componentIndex + 4) = componentNodePtr;
            }
        }
        // Register the component with a manager
        if (*componentNodePtr == 0) {
            FUN_006e03b0(0x68);
        }
        else {
            FUN_006e03b0(*componentNodePtr + 0x20);
        }
    }

    // Handle another linked list node (local_c0) related to +0x58
    if (*(int *)(thisPtr + 0x58) == 0) {
        componentIndex = 0;
    }
    else {
        componentIndex = *(int *)(thisPtr + 0x58) + 0x48;
    }
    if (local_c0 != componentIndex) {
        if (local_c0 != 0) {
            FUN_004daf90(&local_c0);
        }
        local_c0 = componentIndex;
        if (componentIndex != 0) {
            local_bc = *(undefined4 *)(componentIndex + 4);
            *(int **)(componentIndex + 4) = &local_c0;
        }
    }

    // Copy data from +0x80 and +0x88 (position/rotation?)
    local_ac = *(undefined4 *)(thisPtr + 0x88);
    local_b4 = *(undefined8 *)(thisPtr + 0x80);
    local_a8 = flagByte;

    FUN_006e03b0(&local_c0); // Add to list

    // Set a flag in the component object
    if (*componentNodePtr == 0) {
        componentIndex = 0;
    }
    else {
        componentIndex = *componentNodePtr - 0x48;
    }
    *(byte *)(componentIndex + 0x54) = 1;

    // Send component creation/update
    if (*componentNodePtr == 0) {
        componentIndex = 0;
    }
    else {
        componentIndex = *componentNodePtr - 0x48;
    }
    FUN_00424dc0(local_c4, componentIndex, param2, param3, 0);

    // Clean up local list node
    if (local_c0 != 0) {
        FUN_004daf90(&local_c0);
    }
    return;
}