// FUNC_NAME: InputManager::initPadActionNameMappings
void __fastcall InputManager::initPadActionNameMappings(uint32_t *table)
{
    // Maps action string names to internal IDs (enum ePadAction)
    // Pair layout: [0] = string pointer, [1] = action ID, repeated
    // Some trailing entries are IDs-only for axes and duplicates.

    table[0] = (uint32_t)"Pad.RightDPad.Left";   // +0x00
    table[1] = 6;                                 // +0x04
    table[2] = (uint32_t)"Pad.RightDPad.Down";   // +0x08
    table[3] = 5;
    table[4] = (uint32_t)"Pad.RightDPad.Right";  // +0x10
    table[5] = 7;
    table[6] = (uint32_t)"Pad.RightDPad.Up";     // +0x18
    table[7] = 4;
    table[8] = (uint32_t)"Pad.Trigger.LeftTop";  // +0x20
    table[9] = 9;
    table[10] = (uint32_t)"Pad.Trigger.LeftBottom"; // +0x28
    table[11] = 8;
    table[12] = (uint32_t)"Pad.Trigger.RightTop";   // +0x30
    table[13] = 0xb; // 11
    table[14] = (uint32_t)"Pad.Trigger.RightBottom"; // +0x38
    table[15] = 10;
    table[16] = (uint32_t)"Pad.Start";              // +0x40
    table[17] = 0xc; // 12
    table[18] = (uint32_t)"Pad.Back";               // +0x48
    table[19] = 0xd; // 13
    table[20] = (uint32_t)"Pad.LeftStick.Click";    // +0x50
    table[21] = 0xe; // 14
    table[22] = (uint32_t)"Pad.RightStick.Click";   // +0x58
    table[23] = 0xf; // 15

    // Stick axes (analog inputs)
    table[28] = (uint32_t)"Pad.LeftStick.X";        // +0x70
    table[29] = 0x10; // 16
    table[30] = (uint32_t)"Pad.LeftStick.Y";        // +0x78
    table[31] = 0x11; // 17
    table[32] = (uint32_t)"Pad.RightStick.X";       // +0x80
    table[33] = 0x12; // 18
    table[34] = (uint32_t)"Pad.RightStick.Y";       // +0x88
    table[35] = 0x13; // 19

    // Duplicate/extra ID assignments (likely for backward mapping or placeholder)
    table[24] = 0xc;  // Pad.Start ID again
    table[27] = 0xd;  // Pad.Back ID again
    table[25] = 0xe;  // Pad.LeftStick.Click ID again
    table[26] = 0xf;  // Pad.RightStick.Click ID again
}