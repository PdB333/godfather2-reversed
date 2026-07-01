// FUNC_NAME: SimNpc::setActiveTarget
void __thiscall SimNpc::setActiveTarget(int thisPtr, int target) {
    char result;
    char buffer1[48];
    char buffer2[28];

    // Attempt to retrieve some property from target at offset 0x38 (likely a name or ID)
    result = FUN_00990db0(*(int*)(target + 0x38), buffer1);
    if (result != '\0') {
        // If retrieval succeeded, process the property further
        FUN_0097a8d0(buffer2);
    }

    // Reset state if it was in a transitioning state (1-4)
    switch (*(int*)(thisPtr + 8)) {
        case 1:
        case 2:
        case 3:
        case 4:
            *(int*)(thisPtr + 8) = 0;
            break;
    }

    // Assign target pointer and set state to 1 (active)
    *(int*)(thisPtr + 4) = target;
    *(int*)(thisPtr + 8) = 1;

    // If a flag in the parent object (at this - 0x10) is set, trigger an additional action
    if (*(char*)(thisPtr - 0x10) != '\0') {
        FUN_00978310(target);
    }
}