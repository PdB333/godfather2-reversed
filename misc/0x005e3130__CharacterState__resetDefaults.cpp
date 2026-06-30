// FUNC_NAME: CharacterState::resetDefaults

struct CharacterState {
    // Offsets in bytes from this
    /* +0x00 */ int field_0x00;           // 0
    /* +0x04 */ char field_0x04;          // 0
    /* +0x05 */ char field_0x05;          // 0
    /* +0x08 */ int motionType;           // 1
    /* +0x0C */ int field_0x0C;           // 0
    /* +0x10 */ int field_0x10;           // 0
    /* +0x14 */ char field_0x14;          // 0
    /* +0x15 */ char padding_0x15[0x13];  // Padding to next dword
    /* +0x28 */ char field_0x28;          // 0
    /* +0x29 */ char field_0x29;          // 0
    /* +0x2A */ char padding_0x2A[2];     // Align to 0x2C
    /* +0x2C */ int unknown_0x2C;         // DAT_00e2b1a4 (global constant)
    /* +0x30 */ int teamId;               // DAT_00e2b04c
    /* +0x34 */ int someHandle;           // DAT_00e2b050
    /* +0x38 */ int field_0x38;           // 0
    /* +0x3C */ int field_0x3C;           // 0
    /* +0x40 */ int field_0x40;           // 0
    /* +0x44 */ int field_0x44;           // 0
    /* +0x48 */ int field_0x48;           // DAT_00e2b1a4
    /* +0x4C */ int field_0x4C;           // DAT_00e2b1a4
    /* +0x50 */ int field_0x50;           // DAT_00e2b1a4
    /* +0x54 */ int maxHealth;            // 100
    /* +0x58 */ int field_0x58;           // 0
    /* +0x5C */ int field_0x5C;           // 0
    /* +0x60 */ int field_0x60;           // 0
    /* +0x64 */ int field_0x64;           // -1
    /* +0x68 */ int field_0x68;           // 0
};

// Global constant references (defined elsewhere in the game binary)
extern int DAT_00e2b04c;
extern int DAT_00e2b1a4;
extern int DAT_00e2b050;

void __thiscall CharacterState::resetDefaults(void) {
    this->field_0x00 = 0;
    this->field_0x04 = 0;
    this->field_0x05 = 0;
    this->field_0x5C = 0;
    this->field_0x60 = 0;
    this->field_0x64 = -1;

    this->field_0x0C = 0;
    this->field_0x10 = 0;
    this->motionType = 1;
    this->field_0x14 = 0;

    this->teamId = DAT_00e2b04c;
    this->field_0x3C = 0;
    this->field_0x28 = 0;
    this->unknown_0x2C = DAT_00e2b1a4;
    this->field_0x29 = 0;
    this->someHandle = DAT_00e2b050;
    this->field_0x38 = 0;
    this->field_0x40 = 0;
    this->field_0x44 = 0;
    this->field_0x48 = DAT_00e2b1a4;
    this->field_0x4C = DAT_00e2b1a4;
    this->field_0x50 = DAT_00e2b1a4;
    this->maxHealth = 100;
    this->field_0x58 = 0;
    this->field_0x68 = 0;
}