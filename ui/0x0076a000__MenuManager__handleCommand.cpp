// FUNC_NAME: MenuManager::handleCommand
// Function at 0x0076a000 - Handles menu navigation commands (0x23-0x29) with random selection feedback.
// Part of the menu system; dispatches to specific handlers for up/down/left/right/select actions.
// The default case delegates to a base class handler at 0x0073e610.

int __thiscall MenuManager::handleCommand(int this, int arg2, int arg3, int arg4, int command, int arg6) {
    uint maskedIndex;
    int result;

    switch (command) {
        case 0x23: // Up command
            FUN_00768fe0();  // handleMenuUp
            return 1;

        case 0x24: // Down command
            FUN_00769eb0();  // handleMenuDown
            return 1;

        case 0x25: // Left command
            FUN_00769ef0();  // handleMenuLeft
            return 1;

        case 0x26: // Right command
            FUN_00769060(&DAT_00d65be0, 0);  // log or play sound for right
            return 1;

        case 0x27: // Select/Confirm with random offset
            maskedIndex = DAT_010c2678 & DAT_012054b4;  // mask counter
            DAT_012054b4 = DAT_012054b4 + 1;             // increment global counter
            // Set random float offset (e.g., for scroll position or animation)
            *(float *)(this + 0x80) = *(float *)(&DAT_010c2680 + maskedIndex * 4) + _DAT_00d5780c;
            FUN_00769060(&DAT_00d65bec, 6);  // feedback sound/visual (type 6)
            return 1;

        case 0x28: // Secondary select/confirm with random offset
            maskedIndex = DAT_010c2678 & DAT_012054b4;
            DAT_012054b4 = DAT_012054b4 + 1;
            *(float *)(this + 0x80) = *(float *)(&DAT_010c2680 + maskedIndex * 4) + _DAT_00d5780c;
            FUN_00769060(&DAT_00d65bf8, 7);  // feedback sound/visual (type 7)
            return 1;

        case 0x29: // Cancel/Back command
            FUN_00769570();  // handleMenuCancel
            FUN_00720e40();  // maybe close menu or return to parent
            return 1;

        default:
            // Delegate to base class handler for unknown commands
            result = FUN_0073e610(arg2, arg3, arg4, command, arg6);
            return result;
    }
}