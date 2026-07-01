// FUNC_NAME: getConstantByIndex
float getConstantByIndex(uint32_t index)
{
    // Global constants (addresses from Ghidra)
    // DAT_00d5eeec = 0x00d5eeec
    // DAT_00d69ac8 = 0x00d69ac8
    // DAT_00d69ad0 = 0x00d69ad0
    // DAT_00d69acc = 0x00d69acc
    // DAT_00e447a4 = 0x00e447a4
    // DAT_00e446a0 = 0x00e446a0
    // DAT_00d5f00c = 0x00d5f00c

    float fVar1 = 0.0f;
    float local_4 = 0.0f;

    switch (index)
    {
    case 0:
        return DAT_00d5eeec;
    case 1:
        fVar1 = DAT_00d69ac8;
        // fall through
    case 3:
        local_4 = fVar1;
        // fall through to default
    default:
        return local_4;
    case 2:
        return DAT_00d69ad0;
    case 4:
        return DAT_00d69acc;
    case 5:
        return DAT_00e447a4;
    case 6:
        return DAT_00e446a0;
    case 7:
        return DAT_00d5f00c;
    }
}