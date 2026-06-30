// FUNC_NAME: InputDeviceManager::resetDefaults
void __thiscall InputDeviceManager::resetDefaults(void)
{
    // Global constant used for default values (likely 0xFFFFFFFF or similar sentinel)
    int defaultVal = DAT_00e2b1a4;

    // Initialize the internal state array (36 ints, 0x90 bytes)
    // Offsets are in 4-byte units
    this->field0 = 0;                          // +0x00
    this->field4 = defaultVal;                 // +0x10
    this->field5 = 0;                          // +0x14
    this->field6 = 0;                          // +0x18
    this->field7 = 0;                          // +0x1C
    this->field8 = 0;                          // +0x20
    this->field9 = defaultVal;                 // +0x24
    this->field10 = 0;                         // +0x28
    this->field11 = 0;                         // +0x2C
    this->field12 = 0;                         // +0x30
    this->field13 = 0;                         // +0x34
    this->field14 = defaultVal;                // +0x38
    this->field15 = 0;                         // +0x3C
    this->field16 = 0;                         // +0x40
    this->field17 = 0;                         // +0x44
    this->field18 = 0;                         // +0x48
    this->field19 = defaultVal;                // +0x4C
    this->field20 = defaultVal;                // +0x50
    this->field21 = 0;                         // +0x54
    this->field22 = 0;                         // +0x58
    this->field23 = 0;                         // +0x5C
    this->field24 = 0;                         // +0x60
    this->field25 = defaultVal;                // +0x64
    this->field26 = 0;                         // +0x68
    this->field27 = 0;                         // +0x6C
    this->field28 = 0;                         // +0x70
    this->field29 = 0;                         // +0x74
    this->field30 = defaultVal;                // +0x78
    this->field31 = 0;                         // +0x7C
    this->field32 = 0;                         // +0x80
    this->field33 = 0;                         // +0x84
    this->field34 = 0;                         // +0x88
    this->field35 = defaultVal;                // +0x8C
}