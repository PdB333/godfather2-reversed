// FUNC_NAME: PlayerCCTVariables::initialize
// Address: 0x007aaf80
// Initializes player character control variables with default values from globals.

struct PlayerCCTVariables {
    // offsets relative to this (0x0)
    int field_00;        // +0x00
    int field_04;        // +0x04
    int field_08;        // +0x08
    int field_0C;        // +0x0C
    int field_10;        // +0x10
    int field_14;        // +0x14
    int field_18;        // +0x18
    int jumpTimer;       // +0x1C (initialized to 3000)
    float someTolerance; // +0x20 (from _DAT_00d5780c)
    float float_24;      // +0x24
    float float_28;      // +0x28
    float float_2C;      // +0x2C
    float float_30;      // +0x30
    float float_34;      // +0x34
    float float_38;      // +0x38
    float float_3C;      // +0x3C
    char byte_40;        // +0x40
    float float_44;      // +0x44
    float float_48;      // +0x48
    char byte_4C;        // +0x4C
    float float_50;      // +0x50
    int field_54;        // +0x54
    float extraFloat;    // +0x58 (from DAT_00d5779c)
    int field_5C;        // +0x5C
    char byte_60;        // +0x60
    char byte_61;        // +0x61
    int fieldMask;       // +0x64 (initialized to -1)
    int field_68;        // +0x68
    int field_6C;        // +0x6C
    int field_70;        // +0x70
    int field_74;        // +0x74
    int field_78;        // +0x78
    float float_7C;      // +0x7C
    float float_80;      // +0x80
    float float_84;      // +0x84
    float float_88;      // +0x88
    float float_8C;      // +0x8C
    float float_90;      // +0x90
    float float_94;      // +0x94
};

// Global defaults (possibly float constants)
extern int _DAT_00d5780c; // Unknown default value (used for many floats)
extern int DAT_00d5779c;  // Another default value

void __fastcall PlayerCCTVariables::initialize(PlayerCCTVariables* this) {
    this->field_00 = 0;
    this->field_04 = 0;
    this->field_08 = 0;
    this->field_0C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->jumpTimer = 3000;
    this->someTolerance = _DAT_00d5780c;
    this->float_24 = _DAT_00d5780c;
    this->float_28 = _DAT_00d5780c;
    this->float_2C = _DAT_00d5780c;
    this->float_30 = _DAT_00d5780c;
    this->float_34 = _DAT_00d5780c;
    this->float_38 = _DAT_00d5780c;
    this->float_3C = _DAT_00d5780c;
    this->byte_40 = 0;
    this->float_44 = _DAT_00d5780c;
    this->float_48 = _DAT_00d5780c;
    this->byte_4C = 0;
    this->float_50 = _DAT_00d5780c;
    this->field_54 = 0;
    this->extraFloat = DAT_00d5779c;
    this->field_5C = 0;
    this->byte_60 = 0;
    this->byte_61 = 0;
    this->fieldMask = -1;
    this->field_68 = 0;
    this->field_6C = 0;      // Note: assigned in non-sequential order
    this->field_70 = 0;
    this->field_74 = 0;
    this->field_78 = 0;      // offset 0x78
    this->float_7C = _DAT_00d5780c;
    this->float_80 = _DAT_00d5780c;
    this->float_84 = _DAT_00d5780c;
    this->float_88 = _DAT_00d5780c;
    this->float_8C = _DAT_00d5780c;
    this->float_90 = _DAT_00d5780c;
    this->float_94 = _DAT_00d5780c;
}