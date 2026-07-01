// FUNC_NAME: DebugUI::showOptionText

// Function at 0x00958190: Displays a text string (likely for debug UI or HUD) based on the current option index stored at +0x2c4.
// The index selects from 7 predefined help/option strings stored as global data pointers.
// Each case calls setDisplayText with the corresponding string and a fixed parameter 0.

extern void setDisplayText(void* textPtr, int mode);  // 0x00402050

void __thiscall DebugUI::showOptionText(int this) {
    int optionIndex = *(int*)(this + 0x2c4);  // +0x2c4: current option selection index (0-6)

    switch (optionIndex) {
    case 0:
        setDisplayText((void*)0x011301c0, 0);  // Option 0 text
        break;
    case 1:
        setDisplayText((void*)0x011304d8, 0);  // Option 1 text
        break;
    case 2:
        setDisplayText((void*)0x01130448, 0);  // Option 2 text
        break;
    case 3:
        setDisplayText((void*)0x011302c8, 0);  // Option 3 text
        break;
    case 4:
        setDisplayText((void*)0x01130310, 0);  // Option 4 text
        break;
    case 5:
        setDisplayText((void*)0x01130208, 0);  // Option 5 text
        break;
    case 6:
        setDisplayText((void*)0x011302c0, 0);  // Option 6 text
        break;
    // Note: no default; index is assumed to be in 0-6 range
    }
}