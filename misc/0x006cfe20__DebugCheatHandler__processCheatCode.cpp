// FUNC_NAME: DebugCheatHandler::processCheatCode

void __thiscall DebugCheatHandler::processCheatCode(DebugCheatHandler* this, int* hashInput)
{
    int* piVar1;
    uint uVar2;
    int iVar3;
    uint local_6c;
    int iStack_68;
    int iStack_64;
    int iStack_60;
    int iStack_5c;
    int iStack_58;
    undefined1 auStack_54[4];
    undefined4 uStack_50;
    undefined4 uStack_4c;
    undefined4 uStack_48;
    undefined4 uStack_44;
    undefined4 uStack_40;
    undefined4 uStack_3c;
    undefined4 uStack_38;
    undefined4 uStack_34;
    undefined4 uStack_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    undefined4 uStack_24;
    undefined4 uStack_20;
    undefined4 uStack_1c;
    undefined4 uStack_18;
    undefined4 uStack_14;

    // Check global object pointer (e.g., player or UI system)
    piVar1 = (int*)**(int**)(DAT_012233a0 + 4);
    local_6c = local_6c & 0xffffff00;
    if ((piVar1 != (int*)0x0) && (piVar1 != (int*)0x1f30)) {
        uVar2 = (**(code**)(*piVar1 + 8))();
        iVar3 = FUN_00410540(uVar2);
        local_6c = CONCAT31(local_6c._1_3_, *(undefined1*)(iVar3 + 0x11)) & 0xffffff01;
    }

    // Compute polynomial hash of input and compare with stored hash
    int computedHash = ((*hashInput * 0x21 + hashInput[1]) * 0x21 + hashInput[2]) * 0x21 + hashInput[3];
    if (this[0x33] != computedHash) {
        // Hash mismatch – possibly new cheat entered
        if (this[0x32] != 0) {
            FUN_004df600(); // e.g., hidePreviousNotification or clear
        }

        // Skip processing if hash matches known placeholder or zero
        bool isPlaceholder = (*hashInput == -0x45245246 && hashInput[1] == -0x41104111 &&
                              hashInput[2] == -0x153ea5ab && hashInput[3] == -0x6eeff6ef);
        bool isZero = (*hashInput == 0 && hashInput[1] == 0 && hashInput[2] == 0 && hashInput[3] == 0);
        if (!isPlaceholder && !isZero) {
            // Prepare color data (RGBA format, probably for text rendering)
            uStack_50 = _DAT_00d5780c;  // Color A
            uStack_4c = 0;
            uStack_48 = 0;
            uStack_44 = 0;
            uStack_40 = 0;
            uStack_3c = _DAT_00d5780c;  // Color B
            uStack_38 = 0;
            uStack_34 = 0;
            uStack_30 = 0;
            uStack_2c = 0;
            uStack_28 = _DAT_00d5780c;  // Color C
            uStack_24 = 0;
            uStack_20 = 0;
            uStack_1c = 0;
            uStack_18 = 0;
            uStack_14 = _DAT_00d5780c;  // Color D

            // Call vtable function at offset 0x24 (likely drawText or showMessage)
            (**(code**)(*this + 0x24))(&uStack_20); // Pass color struct

            // Store original hash for formatting
            iStack_60 = hashInput[1];
            iStack_64 = *hashInput;
            iStack_5c = hashInput[2];
            iStack_58 = hashInput[3];
            local_6c = 0;

            // Format hash string into buffer (auStack_54, max length 0x1ff)
            uVar2 = FUN_004df270(&iStack_68, &iStack_64, auStack_54, 0x1ff, 0, &local_6c);
            FUN_00414db0(uVar2); // e.g., setText or display

            if (iStack_68 != 0) {
                *(undefined4*)(iStack_68 + 8) = 0; // Clear some flag/pointer
            }

            // Call vtable function at offset 0x3c (e.g., finalizeNotification or commit)
            (**(code**)(*this + 0x3c))(uStack_70);

            // Update stored hash
            this[0x33] = computedHash;
        }
    }
}