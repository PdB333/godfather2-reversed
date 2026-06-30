// FUNC_NAME: GameConfig::initializeDefaults
void __thiscall GameConfig::initializeDefaults(uint32_t* thisPtr)
{
    // Offsets are in 4-byte units (uint32_t)
    // +0x28 (10*4) through +0x88 (34*4) are initialized

    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;

    uVar1 = DAT_00d5f528;          // global constant
    thisPtr[10] = 0;               // +0x28
    thisPtr[11] = 0;               // +0x2C
    thisPtr[12] = 0;               // +0x30
    thisPtr[13] = 0;               // +0x34
    thisPtr[14] = uVar1;           // +0x38
    thisPtr[15] = DAT_00d5efd0;    // +0x3C
    thisPtr[16] = DAT_00d58cbc;    // +0x40
    thisPtr[17] = DAT_00d5eee4;    // +0x44
    thisPtr[18] = DAT_00d5efa4;    // +0x48
    uVar1 = DAT_00d5d7b8;          // global constant
    thisPtr[19] = 0;               // +0x4C
    thisPtr[21] = uVar1;           // +0x54 (skip +0x50)
    thisPtr[22] = uVar1;           // +0x58
    thisPtr[23] = uVar1;           // +0x5C
    uVar1 = _DAT_00d5780c;         // likely vtable pointer
    thisPtr[24] = 0;               // +0x60
    uVar2 = DAT_00d5ddec;          // global constant
    thisPtr[0] = uVar1;            // +0x00 (vtable)
    thisPtr[1] = uVar2;            // +0x04
    uVar2 = DAT_00d5f524;          // global constant
    thisPtr[3] = uVar1;            // +0x0C
    thisPtr[4] = uVar1;            // +0x10
    uVar1 = _DAT_00d5c458;         // global constant
    thisPtr[2] = uVar2;            // +0x08
    uVar2 = _DAT_00d5ca1c;         // global constant
    thisPtr[5] = uVar1;            // +0x14
    thisPtr[8] = uVar1;            // +0x20
    thisPtr[9] = uVar1;            // +0x24
    uVar3 = DAT_00d5f520;          // global constant
    thisPtr[6] = uVar2;            // +0x18
    uVar1 = DAT_00d5eee0;          // global constant
    thisPtr[29] = uVar3;           // +0x74 (0x1D*4)
    uVar2 = DAT_00d5ef88;          // global constant
    thisPtr[34] = 0;               // +0x88 (0x22*4)
    thisPtr[7] = uVar1;            // +0x1C
    thisPtr[30] = uVar2;           // +0x78 (0x1E*4)
    return;
}