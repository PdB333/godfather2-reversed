// FUNC_NAME: SimManager::SimManager

undefined4* __thiscall SimManager::SimManager(undefined4* thisPtr, undefined4 someParam)
{
    undefined4 uVar1;
    undefined4 uVar2;
    undefined4 uVar3;

    // Base class constructor call
    BaseClass::BaseClass(someParam);

    // Initialize fields from global constants
    thisPtr[0x2c] = DAT_00d8c0e4;          // +0xB0
    thisPtr[0x38] = DAT_00e446f4;          // +0xE0
    thisPtr[0x39] = DAT_00d5eff8;          // +0xE4
    uVar1 = _DAT_00d5780c;
    thisPtr[0x3a] = DAT_00e445e0;          // +0xE8
    uVar2 = DAT_00d8c0e0;
    thisPtr[0x28] = uVar1;                 // +0xA0
    uVar1 = DAT_00d60d04;
    thisPtr[0x3b] = uVar2;                 // +0xEC
    uVar2 = DAT_00d8c0dc;
    thisPtr[0x29] = uVar1;                 // +0xA4
    uVar1 = DAT_00d60d0c;
    thisPtr[0x3c] = uVar2;                 // +0xF0
    uVar2 = DAT_00d8c0d8;
    thisPtr[0x2a] = uVar1;                 // +0xA8
    uVar1 = DAT_00d700d4;
    thisPtr[0x3d] = uVar2;                 // +0xF4
    uVar2 = DAT_00d60c60;
    thisPtr[0x2b] = uVar1;                 // +0xAC
    thisPtr[0x2d] = uVar1;                 // +0xB4
    thisPtr[0x2e] = uVar1;                 // +0xB8
    uVar1 = _DAT_00d5cf70;
    thisPtr[0x3e] = uVar2;                 // +0xF8
    uVar2 = DAT_00e445f8;
    thisPtr[0x2f] = uVar1;                 // +0xBC
    thisPtr[0x30] = uVar1;                 // +0xC0
    uVar3 = DAT_00d5ef84;
    thisPtr[0x40] = uVar2;                 // +0x100
    uVar2 = DAT_00d5eee4;
    uVar1 = DAT_00d5d7b8;
    thisPtr[0x31] = uVar3;                 // +0xC4
    thisPtr[0x42] = uVar2;                 // +0x108
    uVar2 = DAT_00d5e288;

    // Set vtable and function pointers
    *thisPtr = &PTR_FUN_00d8c0b4;          // +0x00 vtable
    thisPtr[0xf] = &PTR_LAB_00d8c0a4;     // +0x3C
    thisPtr[0x12] = &PTR_LAB_00d8c0a0;    // +0x48
    thisPtr[0x14] = &PTR_LAB_00d8c09c;    // +0x50

    // Zero out various fields
    thisPtr[0x32] = 0;                     // +0xC8
    thisPtr[0x33] = 0;                     // +0xCC
    thisPtr[0x3f] = 0;                     // +0xFC
    thisPtr[0x43] = uVar2;                 // +0x10C
    *(byte*)(thisPtr + 0x41) = 0;          // +0x104 (byte)
    thisPtr[0x1b] = 0;                     // +0x6C
    thisPtr[0x1a] = 0;                     // +0x68
    thisPtr[0x19] = 0;                     // +0x64
    thisPtr[0x18] = 0;                     // +0x60
    thisPtr[0x1f] = 0;                     // +0x7C
    thisPtr[0x1e] = 0;                     // +0x78
    thisPtr[0x1d] = 0;                     // +0x74
    thisPtr[0x1c] = 0;                     // +0x70
    thisPtr[0x23] = 0;                     // +0x8C
    thisPtr[0x22] = 0;                     // +0x88
    thisPtr[0x21] = 0;                     // +0x84
    thisPtr[0x20] = 0;                     // +0x80
    thisPtr[0x27] = 0;                     // +0x9C
    thisPtr[0x26] = 0;                     // +0x98
    thisPtr[0x25] = 0;                     // +0x94
    thisPtr[0x24] = 0;                     // +0x90
    thisPtr[0x37] = 0;                     // +0xDC
    thisPtr[0x36] = 0;                     // +0xD8
    thisPtr[0x35] = 0;                     // +0xD4
    thisPtr[0x34] = 0;                     // +0xD0
    thisPtr[0x44] = 0;                     // +0x110

    // Set additional fields
    thisPtr[0x56] = uVar1;                 // +0x158
    thisPtr[0x57] = uVar2;                 // +0x15C
    thisPtr[0x58] = uVar2;                 // +0x160
    thisPtr[0x53] = 0;                     // +0x14C
    thisPtr[0x52] = 0;                     // +0x148
    thisPtr[0x51] = 0;                     // +0x144
    thisPtr[0x50] = 0;                     // +0x140
    thisPtr[0x4b] = 0;                     // +0x12C
    thisPtr[0x4a] = 0;                     // +0x128
    thisPtr[0x49] = 0;                     // +0x124
    thisPtr[0x48] = 0;                     // +0x120

    // Final initialization call
    SimManager::init(thisPtr);

    return thisPtr;
}