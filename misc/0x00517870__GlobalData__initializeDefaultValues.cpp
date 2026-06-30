// FUNC_NAME: GlobalData::initializeDefaultValues
void GlobalData::initializeDefaultValues(void)
{
    // +0x00: unknown field (4 bytes)
    // +0x04: unknown field (4 bytes)
    // +0x08: unknown field (4 bytes)
    // +0x0C: unknown field (4 bytes)
    // +0x10: unknown field (4 bytes)
    // +0x14: unknown field (4 bytes)
    // +0x18: unknown field (4 bytes)
    // +0x1C: unknown field (4 bytes)
    // +0x20: unknown field (4 bytes)
    // +0x24: unknown field (4 bytes)
    // +0x28: unknown field (4 bytes)
    // +0x2C: unknown field (4 bytes)
    // +0x30: unknown field (4 bytes)
    // +0x34: unknown field (4 bytes)
    // +0x38: unknown field (4 bytes)
    // +0x3C: unknown field (4 bytes)
    // +0x40: unknown field (4 bytes)
    // +0x44: unknown field (4 bytes)
    // +0x48: unknown field (4 bytes)
    // +0x4C: unknown field (4 bytes)
    // +0x50: unknown field (4 bytes)
    // +0x54: unknown field (4 bytes)
    // +0x58: unknown field (4 bytes)
    // +0x5C: unknown field (4 bytes)

    // Initialize first two fields with value from DAT_00e39f98 (likely a default float/int)
    DAT_012192d0 = DAT_00e39f98;
    DAT_012192d4 = DAT_00e39f98;

    // Clear three fields at offset 0x00, 0x04, 0x08
    _DAT_012192c0 = 0;
    _DAT_012192c4 = 0;
    _DAT_012192c8 = 0;

    // Initialize field at offset 0x0C with value from DAT_00e2b1a4 (likely another default)
    _DAT_012192cc = DAT_00e2b1a4;

    // Initialize four consecutive fields at offset 0x10, 0x14, 0x18, 0x1C with same default
    DAT_012192b0 = DAT_00e2b1a4;
    DAT_012192b4 = DAT_00e2b1a4;
    DAT_012192b8 = DAT_00e2b1a4;
    _DAT_012192bc = DAT_00e2b1a4;

    // Initialize field at offset 0x20 with value from DAT_00e445ac
    _DAT_012192d8 = DAT_00e445ac;

    // Clear fields at offset 0x24, 0x28, 0x30, 0x34
    DAT_012192dc = 0;
    DAT_012192f0 = 0;
    _DAT_012192f4 = 0;
    DAT_012192e0 = 0;
    DAT_012192e4 = 0;

    // Initialize fields at offset 0x38 and 0x3C with default value
    _DAT_012192e8 = DAT_00e2b1a4;
    DAT_012192ec = DAT_00e2b1a4;

    return;
}