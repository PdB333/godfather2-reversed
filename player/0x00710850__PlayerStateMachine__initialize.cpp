// FUNC_NAME: PlayerStateMachine::initialize
void __fastcall PlayerStateMachine::initialize(PlayerStateMachine* thisState)
{
    // Zero-initialize all 46 int fields (offsets 0x00 to 0xB4)
    thisState->field_0x00 = 0;  // +0x00
    thisState->field_0x04 = 0;  // +0x04
    thisState->field_0x08 = 0;  // +0x08
    thisState->field_0x0C = 0;  // +0x0C
    thisState->field_0x10 = 0;  // +0x10
    thisState->field_0x14 = 0;  // +0x14
    thisState->field_0x18 = 0;  // +0x18
    thisState->field_0x1C = 0;  // +0x1C
    thisState->field_0x20 = 0;  // +0x20
    thisState->field_0x24 = 0;  // +0x24
    thisState->field_0x28 = 0;  // +0x28
    thisState->field_0x2C = 0;  // +0x2C
    thisState->field_0x30 = 0;  // +0x30
    thisState->field_0x34 = 0;  // +0x34
    thisState->field_0x38 = 0;  // +0x38
    thisState->field_0x3C = 0;  // +0x3C
    thisState->field_0x40 = 0;  // +0x40 (index 0x10)
    thisState->field_0x50 = 0;  // +0x50 (index 0x14)
    thisState->field_0x4C = 0;  // +0x4C (index 0x13)
    thisState->field_0x48 = 0;  // +0x48 (index 0x12)
    thisState->field_0x44 = 0;  // +0x44 (index 0x11)
    thisState->field_0x60 = 0;  // +0x60 (index 0x18)
    thisState->field_0x5C = 0;  // +0x5C (index 0x17)
    thisState->field_0x58 = 0;  // +0x58 (index 0x16)
    thisState->field_0x54 = 0;  // +0x54 (index 0x15)
    thisState->field_0x70 = 0;  // +0x70 (index 0x1C)
    thisState->field_0x6C = 0;  // +0x6C (index 0x1B)
    thisState->field_0x68 = 0;  // +0x68 (index 0x1A)
    thisState->field_0x64 = 0;  // +0x64 (index 0x19)
    thisState->field_0x80 = 0;  // +0x80 (index 0x20)
    thisState->field_0x7C = 0;  // +0x7C (index 0x1F)
    thisState->field_0x78 = 0;  // +0x78 (index 0x1E)
    thisState->field_0x74 = 0;  // +0x74 (index 0x1D)
    thisState->field_0x90 = 0;  // +0x90 (index 0x24)
    thisState->field_0x8C = 0;  // +0x8C (index 0x23)
    thisState->field_0x88 = 0;  // +0x88 (index 0x22)
    thisState->field_0x84 = 0;  // +0x84 (index 0x21)
    thisState->field_0x94 = 0;  // +0x94 (index 0x25)
    thisState->field_0x98 = 0;  // +0x98 (index 0x26)
    thisState->field_0x9C = 0;  // +0x9C (index 0x27)
    thisState->field_0xA0 = 0;  // +0xA0 (index 0x28)
    thisState->field_0xA4 = 0;  // +0xA4 (index 0x29)
    thisState->field_0xA8 = 0;  // +0xA8 (index 0x2A)

    // Set state indicator field to 3 (e.g., PLAYER_STATE_IDLE)
    thisState->field_0xAC = 3;  // +0xAC (index 0x2B)

    thisState->field_0xB0 = 0;  // +0xB0 (index 0x2C)
    thisState->field_0xB4 = 0;  // +0xB4 (index 0x2D)
}