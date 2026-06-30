// FUNC_NAME: translateInputToAction
// Address: 0x0063f930
// Role: Maps raw input codes (DirectInput scancodes or extended button IDs) to game action indices.
// Called from input handling code to convert low-level key presses to higher-level actions.
// Returns 0xE (14) for unmapped inputs.
unsigned int __fastcall translateInputToAction(unsigned int inputCode)
{
    switch (inputCode)
    {
        case 0x2A:  // DIK_LSHIFT
            return 2;
        case 0x2B:  // DIK_BACKSLASH
            return 0;
        case 0x2D:  // DIK_X
            return 1;
        case 0x2F:  // DIK_V
            return 3;
        case 0x3C:  // DIK_F2
            return 8;
        case 0x3E:  // DIK_F4
            return 10;
        case 0x5E:  // Unknown (possibly custom gamepad/keyboard mapping)
            return 4;
        case 0x101: // Extended key or gamepad button
            return 12;
        case 0x10F:
            return 13;
        case 0x117:
            return 5;
        case 0x119:
            return 7;
        case 0x11A:
            return 11;
        case 0x11B:
            return 9;
        case 0x11C:
            return 6;
        default:
            return 0xE;
    }
}