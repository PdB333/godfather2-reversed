// FUNC_NAME: DialogTreeManager::setSelectedOption

// 0x005403e0 - DialogTreeManager::setSelectedOption
// Checks if the dialog manager is active, then updates the global selected option
// param_2 = option index to set
void __thiscall DialogTreeManager::setSelectedOption(int this, int option)
{
    int status;

    // +0x28 is the active flag (bool)
    if (*(char *)(this + 0x28) != '\0') {
        // 0x00ab5130 - getDialogState(&gDialogManager) returns -2 if no active dialog
        status = getDialogState(&gDialogManager); // DAT_00e2d728 -> global DialogManager singleton
        if (status != -2) {
            // 0x0103b270 - gCurrentSelectedOption (global int)
            gCurrentSelectedOption = option;
        }
    }
    return;
}