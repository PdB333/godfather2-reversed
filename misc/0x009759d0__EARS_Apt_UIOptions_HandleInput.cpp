// Xbox PDB: EARS_Apt_UIOptions_HandleInput
// FUNC_NAME: UIMenuScreen::handleInput
// Address: 0x009759d0
// Handles user input for a menu screen. Returns 1 if action == 1 (back/exit?), else 0 after processing.
// Uses getConfirmAction() and getCancelAction() from an input bindings system.
// Menu state: active flag at [this+0x5C], input enabled flag at this+0x83 (byte).

int __thiscall UIMenuScreen::handleInput(void* this, int action) {
    int result = 0;  // default return 0

    // Action 1: exit/back (e.g., pressing B button)
    if (action == 1) {
        return 1;
    }

    // If menu is already active (m_bActive at +0x5C)
    if (*(int*)((int)this + 0x5C) == 1) {
        // If input is enabled (byte at +0x83)
        if (*(char*)((int)this + 0x83) != '\0') {
            int confirmAction = getConfirmAction(); // FUN_00466860
            if (action == confirmAction) {
                // Call virtual function at vtable+0x2C (likely "onConfirm")
                (**(code**)(*(int*)this + 0x2C))(); 
                FUN_00402050(&DAT_01130310, 0); // clear global selection?
                return 0;
            }
            if (action == 8) {
                navigateMenu(0xFFFFFFFF); // FUN_00974b80 - move left? -1
                return 0;
            }
            if (action == 9) {
                navigateMenu(1); // FUN_00974b80 - move right? +1
                return 0;
            }
            int cancelAction = getCancelAction(); // FUN_00466840
            if (action == cancelAction) {
                resetMenuList(); // FUN_00975870 - reset list selection?
                return 0;
            }
        }
    } else {
        // Menu not active yet
        int confirmAction = getConfirmAction();
        if (action == confirmAction) {
            saveOptions(); // FUN_00974df0
            loadOptions(); // FUN_00975050
            callScriptFunction("RestoreOptionData", 0, &DAT_00d8f7f8, 0); // FUN_005a04a0
            *(int*)((int)this + 0x5C) = 1; // set active
            callScriptFunction("ShowMenu", 0, &DAT_00d8f7f8, 0); // show the menu
            // Copy global data into local struct and reset
            int local_c = DAT_01130310;
            int local_8 = 0;
            char local_4 = 0;
            FUN_00408a00(&local_c, 0); // copy or reset?
            return 0;
        }
        int cancelAction = getCancelAction();
        if (action == cancelAction) {
            *(int*)((int)this + 0x5C) = 1; // set active
            callScriptFunction("ShowMenu", 0, &DAT_00d8f7f8, 0);
            FUN_00402050(&DAT_011302c8, 0); // clear another global
            return 0;
        }
        switch (action) {
        case 0:
            result = 1; // some special action?
            break;
        case 6:
            sendInput("MoveLeft", &DAT_00d8f7f8, &DAT_011304d8, &DAT_011302c0); // FUN_00929a20
            return 0;
        case 7:
            sendInput("MoveRight", &DAT_00d8f7f8, &DAT_011304d8, &DAT_011302c0);
            return 0;
        case 8:
            callScriptFunction("MoveUp", 0, &DAT_00d8f7f8, 0);
            FUN_00402050(&DAT_011301c0, 0);
            return 0;
        case 9:
            callScriptFunction("MoveDown", 0, &DAT_00d8f7f8, 0);
            FUN_00402050(&DAT_011301c0, 0);
            return 0;
        }
    }
    return result;
}