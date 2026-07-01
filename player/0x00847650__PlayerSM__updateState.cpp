//FUNC_NAME: PlayerSM::updateState
void __thiscall PlayerSM::updateState(int thisPtr, char param_2, undefined4 param_3)
{
    char result;
    undefined4 hashMapResult;
    int typeCheckResult;
    int foundData;

    foundData = thisPtr;
    FUN_00598860();
    hashMapResult = FUN_00445ff0((int *)(thisPtr + 0x8c), 0); // +0x8c: hash map pointer
    foundData = 0;
    result = FUN_004480d0(hashMapResult, 0x30431d5e, &foundData); // Lookup key (hash 0x30431d5e)
    typeCheckResult = 0;
    if (((result != '\0') && (typeCheckResult = foundData, foundData != 0)) && (param_2 == '\0')) {
        typeCheckResult = FUN_004025a0(*(undefined4 *)(*(int *)(foundData + 0xfc) + 8)); // +0xfc: data pointer, +8: type info
        if ((typeCheckResult == 0) || (*(int *)(typeCheckResult + 0x24) != 3)) { // +0x24: type ID
            result = FUN_00847100(); // Check some condition
            if (result != '\0') {
LAB_00847762:
                FUN_00846790(1, 0); // Set state flag
                *(uint *)(thisPtr + 0x118) = *(uint *)(thisPtr + 0x118) | 0x10000; // +0x118: flags
                *(undefined4 *)(thisPtr + 0x14c) = param_3; // +0x14c: store parameter
                return;
            }
        }
        *(undefined4 *)(thisPtr + 0x130) = 0; // +0x130: clear some field
        FUN_008473d0(thisPtr, param_3); // Process transition
        FUN_004b1720(thisPtr + 0x144); // +0x144: timer or counter
        FUN_00408680(thisPtr + 100); // +0x64: timer or update
        return;
    }
    FUN_008429a0(); // Reset or cleanup
    if (param_2 != '\0') {
        FUN_00847060(); // Handle secondary state
        FUN_008428f0(1); // Set flag
    }
    FUN_00846720(); // Update state
    if (((param_2 == '\0') && (typeCheckResult == 0)) &&
       (((*(int *)(thisPtr + 0x8c) != 0 || // +0x8c: pointer
         ((*(int *)(thisPtr + 0x90) != 0 || (*(int *)(thisPtr + 0x94) != 0)))) || // +0x90, +0x94: pointers
        (*(int *)(thisPtr + 0x98) != 0)))) { // +0x98: pointer
        result = FUN_00445250(); // Check some condition
        if (result != '\0') {
            result = FUN_00846a50(); // Check another condition
            if (result != '\0') goto LAB_00847762;
            param_2 = '\x01';
        }
    }
    *(undefined4 *)(thisPtr + 0x130) = 0; // +0x130: clear
    if (param_2 == '\0') {
        if ((*(uint *)(thisPtr + 0x118) & 0x7800) == 0x800) { // +0x118: flags, check bit 11
            *(uint *)(thisPtr + 0x118) = *(uint *)(thisPtr + 0x118) & 0xffff87ff; // Clear bits 11-14
        }
        if ((*(byte *)(thisPtr + 0x118) & 8) != 0) goto LAB_008477dd; // Check bit 3
    }
    FUN_00846250(); // Update state
    if (param_2 != '\0') {
        FUN_00847150(); // Handle secondary state
    }
LAB_008477dd:
    FUN_00846930(); // Finalize update
    if (((((*(int *)(thisPtr + 0x134) != 0) || (*(int *)(thisPtr + 0x138) != 0)) || // +0x134-0x140: four ints
         (*(int *)(thisPtr + 0x13c) != 0)) || (*(int *)(thisPtr + 0x140) != 0)) &&
       (((*(int *)(thisPtr + 0x134) != -0x45245246 || (*(int *)(thisPtr + 0x138) != -0x41104111)) ||
        ((*(int *)(thisPtr + 0x13c) != -0x153ea5ab || (*(int *)(thisPtr + 0x140) != -0x6eeff6ef))))))
    {
        *(uint *)(thisPtr + 0x118) = *(uint *)(thisPtr + 0x118) & 0xfffff8ff | 0x80; // Clear bits 8-10, set bit 7
    }
    FUN_00408680(thisPtr + 100); // +0x64: timer or update
    return;
}