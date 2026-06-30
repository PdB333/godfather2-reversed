// FUNC_NAME: Building::constructor
void __fastcall Building::constructor(int thisPtr)
{
    // Call base class constructor
    FUN_0059b5e0(); // Probably EARSObject::constructor or similar

    // Initialize building-specific fields
    *(undefined4 *)(thisPtr + 0x70) = 0;  // +0x70: unknown (4 bytes)
    *(undefined4 *)(thisPtr + 0x74) = 0;  // +0x74: unknown (4 bytes)
    *(undefined4 *)(thisPtr + 0x78) = 0;  // +0x78: unknown (4 bytes)
    *(undefined2 *)(thisPtr + 0x80) = 0;  // +0x80: unknown (2 bytes)
    *(undefined2 *)(thisPtr + 0x82) = 0;  // +0x82: unknown (2 bytes)
    *(undefined4 *)(thisPtr + 0x88) = 0;  // +0x88: unknown (4 bytes)
    *(undefined2 *)(thisPtr + 0x86) = 0;  // +0x86: unknown (2 bytes)
    *(undefined4 *)(thisPtr + 0x7c) = 0;  // +0x7c: unknown (4 bytes)
    *(undefined2 *)(thisPtr + 0x84) = 4;  // +0x84: initialized to 4 (2 bytes)

    // Call some global function (likely from GameManager or similar)
    // The function pointer at DAT_012055a8 + 0x34 is called with 3 zero args and output pointer
    (**(code **)(*DAT_012055a8 + 0x34))(0, 0, 0, thisPtr + 0x8c);
    (**(code **)(*DAT_012055a8 + 0x34))(0, 0, 0, thisPtr + 0x98);

    *(undefined4 *)(thisPtr + 0xa4) = 0;  // +0xa4: unknown (4 bytes)
    *(undefined4 *)(thisPtr + 0xa8) = 0;  // +0xa8: unknown (4 bytes)
    *(undefined4 *)(thisPtr + 0xac) = 0;  // +0xac: unknown (4 bytes)
    return;
}