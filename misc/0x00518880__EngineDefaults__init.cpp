// FUNC_NAME: EngineDefaults::init
int* EngineDefaults::init(void)
{
    // Initialize global engine defaults structure at 0x01219250
    // Structure contains various configuration values (likely floats/ints)
    // Fields:
    // +0x00: default value (DAT_00e2b1a4)
    // +0x04: default value (DAT_00e2b1a4)
    // +0x08: default value (DAT_00e2b1a4)
    // +0x0C: zero
    // +0x10: zero
    // +0x14: zero
    // +0x18: zero
    // +0x1C: default value (DAT_00e2b1a4)
    // +0x20: default value (DAT_00e39f98)
    // +0x24: default value (DAT_00e39f98)
    // +0x28: default value (DAT_00e445ac)
    // +0x2C: zero
    // +0x30: zero
    // +0x34: zero
    // +0x38: default value (DAT_00e2b1a4)
    // +0x3C: default value (DAT_00e2b1a4)
    // +0x40: zero
    // +0x44: zero
    // +0x50: zero

    gEngineDefaults[0x20] = gDefaultValue1;  // _DAT_01219270
    gEngineDefaults[0x24] = gDefaultValue1;  // DAT_01219274
    gEngineDefaults[0x40] = 0;               // DAT_01219290
    gEngineDefaults[0x44] = 0;               // DAT_01219294
    gEngineDefaults[0x10] = 0;               // _DAT_01219260
    gEngineDefaults[0x14] = 0;               // _DAT_01219264
    gEngineDefaults[0x18] = 0;               // _DAT_01219268
    gEngineDefaults[0x1C] = gDefaultValue2;  // _DAT_0121926c
    gEngineDefaults[0x00] = gDefaultValue2;  // DAT_01219250
    gEngineDefaults[0x04] = gDefaultValue2;  // DAT_01219254
    gEngineDefaults[0x08] = gDefaultValue2;  // _DAT_01219258
    gEngineDefaults[0x28] = gDefaultValue3;  // DAT_01219278
    gEngineDefaults[0x2C] = 0;               // DAT_0121927c
    gEngineDefaults[0x30] = 0;               // DAT_01219280
    gEngineDefaults[0x34] = 0;               // DAT_01219284
    gEngineDefaults[0x38] = gDefaultValue2;  // DAT_01219288
    gEngineDefaults[0x3C] = gDefaultValue2;  // DAT_0121928c
    gEngineDefaults[0x0C] = 0;               // DAT_0121925c
    gEngineDefaults[0x50] = 0;               // DAT_012192a0

    return gEngineDefaults;  // &DAT_01219250
}