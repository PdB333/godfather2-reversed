// FUNC_NAME: SimNpc::initializeDefaults
// Function address: 0x005dd030
// Role: Initializes a SimNpc (or similar game object) with default values, including debug sentinel markers and global parameters.
// The struct layout is inferred from offsets; fields are documented with offsets.
// TODO: Verify exact location of fields; some bytes at +0x20, +0x21, +0x22, +0x23 are set individually.

void SimNpc::initializeDefaults(undefined4 *thisPtr) // __thiscall, pointer in EAX
{
    // External globals (likely float or int constants)
    extern int DAT_00e2b1a4; // some global value (e.g., default speed or camera offset)
    extern int DAT_00e2b118; // another global value

    int uVar2 = DAT_00e2b1a4;
    int uVar1 = DAT_00e2b118;

    // +0x44: field at offset 0x44 (index 17) set to 96000 (likely max value or timer)
    thisPtr[0x11] = 96000;
    // +0x4C: field at offset 0x4C (index 19) set to 96000
    thisPtr[0x13] = 96000;

    // +0x00, +0x04: first two dwords set to uVar2 (globals)
    thisPtr[0] = uVar2;
    thisPtr[1] = uVar2;

    // +0x28, +0x2C: more copies of uVar2
    thisPtr[0x0A] = uVar2;
    thisPtr[0x0B] = uVar2;

    // +0x21, +0x22, +0x23: three bytes set to 0 (could be bools/flags)
    *(byte *)((int)thisPtr + 0x21) = 0;
    *(byte *)((int)thisPtr + 0x22) = 0;
    *(byte *)((int)thisPtr + 0x23) = 0;

    // +0x08: dword set to 0
    thisPtr[2] = 0;
    // +0x24: dword set to 0
    thisPtr[9] = 0;
    // +0x30: dword set to 0
    thisPtr[0x0C] = 0;
    // +0x34: dword set to 0
    thisPtr[0x0D] = 0;
    // +0x48: dword set to 0
    thisPtr[0x12] = 0;

    // +0x0C: dword set to 1 (likely a boolean flag)
    thisPtr[3] = 1;

    // +0x10 to +0x1C: debug sentinel magic values (for memory corruption detection)
    thisPtr[4] = 0xBADBADBA;
    thisPtr[5] = 0xBEEFBEEF;
    thisPtr[6] = 0xEAC15A55; // "EAC" may hint at EARS engine (Electronic Arts)
    thisPtr[7] = 0x91100911;

    // +0x38: dword set to uVar1
    thisPtr[0x0E] = uVar1;
    // +0x3C: dword set to uVar2
    thisPtr[0x0F] = uVar2;

    // +0x50 to +0x64: six dwords set to 0
    thisPtr[0x14] = 0;
    thisPtr[0x15] = 0;
    thisPtr[0x16] = 0;
    thisPtr[0x17] = 0;
    thisPtr[0x18] = 0;
    thisPtr[0x19] = 0;

    return;
}