// FUNC_NAME: InputDeviceManager::updateControllerSlot
// Address: 0x00878170
// Role: Updates a controller slot's active state and copies default input profile data if needed.
void __thiscall InputDeviceManager::updateControllerSlot(int thisPtr, int controllerStatePtr) {
    char status;
    int tmpInt;

    int localArray[5]; // +0x1c
    char local_8;
    int local_4; // from DAT_01205228 (global)
    int local_20; // = 0x88886a27 (magic)
    void** local_24; // points to PTR_FUN_00d5dbbc (global function table)
    int local_30; // from DAT_0112ad8c (global default profile)
    void*** local_2c; // points to &local_24
    char local_28; // = 0

    if ((controllerStatePtr != 0) && ((*(uint*)(thisPtr + 0xc88) >> 0xb & 1) != 0)) {
        // +0xc88 is a flags field, bit 11 (0x400) must be set for this controller to be active
        status = FUN_00543050(controllerStatePtr); // likely checks if controller is valid/loaded
        if (status == '\0') {
            FUN_008f8220(controllerStatePtr); // cleanup/release if not valid
        }

        // Prepare stack variables for a copy operation
        localArray[4] = 0;
        localArray[3] = 0;
        localArray[2] = 0;
        local_24 = &PTR_FUN_00d5dbbc; // global function table pointer
        localArray[0] = 0;
        localArray[1] = 0;
        local_8 = 0;
        local_4 = DAT_01205228; // global (likely some flag)
        local_20 = 0x88886a27;   // magic constant

        // Check if a global manager exists (DAT_012233a0+4 points to some base object)
        if ((**(int**)(DAT_012233a0 + 4) != 0)) {
            tmpInt = **(int**)(DAT_012233a0 + 4) + -0x1f30; // offset -0x1f30 (negative)
            if (tmpInt != 0) {
                FUN_0044b210(tmpInt); // likely initializes or copies something from that offset
            }

            local_30 = DAT_0112ad8c; // global default controller profile data
            local_2c = &local_24;    // address of the function table pointer
            local_28 = 0;
            FUN_00408bf0(&local_30, controllerStatePtr + 0x3c, 0);
            // Copies default profile data to controllerStatePtr+0x3c (offset in controller struct)
            // Third argument 0 might indicate size (0 = default?) or flags

            if (localArray[0] != 0) {
                FUN_004daf90(localArray); // free temporary memory if allocated
            }
        }
    }
    return;
}