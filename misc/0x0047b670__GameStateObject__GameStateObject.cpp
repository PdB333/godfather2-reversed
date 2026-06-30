// FUNC_NAME: GameStateObject::GameStateObject
undefined4* __thiscall GameStateObject::GameStateObject(undefined4* thisPtr, undefined4 param_2) {
    // Call base class or initialization function
    FUN_0046c590(param_2);  // likely parent constructor or init

    // Set vtable pointers (multiple inheritance or sub-objects)
    thisPtr[0] = &PTR_FUN_00e33114;          // +0x00: primary vtable
    thisPtr[0xf] = &PTR_LAB_00e33130;        // +0x3C: secondary vtable
    thisPtr[0x12] = &PTR_LAB_00e33140;       // +0x48: tertiary vtable

    // Capture global values
    undefined4 uVar2 = DAT_00e44620;          // global used for field at +0x9C
    undefined4 uVar1 = DAT_00e2b1a4;          // global used for field at +0xA0

    // Initialize three structured blocks (each 8 bytes: int + 2 shorts)
    // Block 1 at +0x50
    thisPtr[0x14] = 0;                       // +0x50: int
    *(undefined2*)(thisPtr + 0x15) = 0;      // +0x54: short
    *(undefined2*)((int)thisPtr + 0x56) = 0; // +0x56: short

    // Block 2 at +0x58
    thisPtr[0x16] = 0;                       // +0x58: int
    *(undefined2*)(thisPtr + 0x17) = 0;      // +0x5C: short
    *(undefined2*)((int)thisPtr + 0x5e) = 0; // +0x5E: short

    // Block 3 at +0x60
    thisPtr[0x18] = 0;                       // +0x60: int
    *(undefined2*)(thisPtr + 0x19) = 0;      // +0x64: short
    *(undefined2*)((int)thisPtr + 0x66) = 0; // +0x66: short

    // Set debug/magic sentinel values (temporary)
    thisPtr[0x1a] = 0xbadbadba;              // +0x68: sentinel
    thisPtr[0x1b] = 0xbeefbeef;              // +0x6C: sentinel
    thisPtr[0x1c] = 0xeac15a55;              // +0x70: sentinel
    thisPtr[0x1d] = 0x91100911;              // +0x74: sentinel

    // Zero out other fields
    thisPtr[0x1e] = 0;                       // +0x78
    thisPtr[0x1f] = 0;                       // +0x7C
    thisPtr[0x22] = 0;                       // +0x88
    thisPtr[0x23] = 0;                       // +0x8C
    thisPtr[0x24] = 0;                       // +0x90
    thisPtr[0x20] = 0;                       // +0x80
    thisPtr[0x26] = 0;                       // +0x98

    // Initialize fields from global globals
    thisPtr[0x27] = uVar2;                   // +0x9C
    thisPtr[0x28] = uVar1;                   // +0xA0

    thisPtr[0x29] = 0;                       // +0xA4
    thisPtr[0x2a] = 0;                       // +0xA8

    // Set size fields (suggesting buffer sizes)
    thisPtr[0x25] = 0x9c;                    // +0x94: size = 156
    thisPtr[0x2b] = 0x9c;                    // +0xAC: size = 156

    thisPtr[0x2c] = 0;                       // +0xB0
    thisPtr[0x2d] = uVar2;                   // +0xB4
    thisPtr[0x2e] = uVar1;                   // +0xB8

    thisPtr[0x2f] = 0;                       // +0xBC
    thisPtr[0x30] = 0;                       // +0xC0

    // Clear the sentinel values (debug initialization complete)
    thisPtr[0x1d] = 0;                       // +0x74
    thisPtr[0x1c] = 0;                       // +0x70
    thisPtr[0x1b] = 0;                       // +0x6C
    thisPtr[0x1a] = 0;                       // +0x68

    return thisPtr;
}