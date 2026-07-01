// FUNC_NAME: Vehicle::getSpeedValue
float __fastcall Vehicle::getSpeedValue(int thisPtr)
{
    int iVar1;
    float result;

    // Default value from global
    result = DAT_00d812a8;

    // Check if vehicle state is 2 (e.g., active/driving)
    if (*(int*)(thisPtr + 0x174) == 2) {
        iVar1 = 0;
        // Check if physics pointer is non-null
        if (*(int*)(thisPtr + 0x160) != 0) {
            iVar1 = FUN_007ff880(); // Possibly a validation or update function
        }
        // If either the validation succeeded or physics pointer is non-null
        if ((iVar1 != 0) || (*(int*)(thisPtr + 0x160) != 0)) {
            // Get some global object (e.g., player manager) and check a sub-object
            iVar1 = FUN_00471610(); // e.g., getPlayerManager()
            iVar1 = FUN_00786720(iVar1 + 0x30); // e.g., getPlayer()->isValid()
            if (iVar1 != 0) {
                // Return the stored speed value at offset 0x190
                result = *(float*)(thisPtr + 0x190);
            }
        }
    }
    return result;
}