// FUNC_NAME: EARSObject::constructor

// 0x0046e6b0 - Constructor for a base EARS engine game object
// Initializes vtable, flags, and various member fields.
// Called by many derived class constructors.

undefined4 * __thiscall EARSObject::constructor(undefined4 *this, void *baseObj, short someFlag)
{
    // Call base class constructor (likely EARSNode or similar)
    FUN_0046c590(baseObj);
    
    // Initial vtable/interface setup (overwritten later)
    this[0x14] = &PTR_LAB_00e32854; // +0x50? vtable or interface
    this[0x15] = &PTR_LAB_00e31528; // +0x54
    this[0x17] = 0;                 // +0x5C
    this[0x18] = 0;                 // +0x60
    this[0x16] = &PTR_FUN_00e33520; // +0x58
    this[0x19] = DAT_0120540c;      // +0x64 - save previous reference
    DAT_0120540c = 0;               // clear global
    
    // If previous reference exists and has a specific flag set, release it
    if (this[0x19] != 0)
    {
        if ((*(uint *)(this[0x19] + 0x30) >> 1 & 1) != 0) // +0x30 flag bit 1
        {
            FUN_00481430(); // Release / decrement refcount
        }
    }
    
    // Second set of vtable/interface pointers (overwrites previous)
    undefined4 uVar1 = DAT_0110ac04; // save for later
    this[0x16] = &PTR_LAB_00e32a20; // +0x58
    *this = &PTR_FUN_00e32858;      // +0x00 primary vtable
    this[0xf] = &PTR_LAB_00e329a4;  // +0x3C
    this[0x12] = &PTR_LAB_00e329b4; // +0x48
    this[0x14] = &PTR_LAB_00e329b8; // +0x50
    this[0x15] = &PTR_LAB_00e329c0; // +0x54
    
    // Zero out some fields
    this[0x1a] = 0; // +0x68
    this[0x1b] = 0; // +0x6C
    this[0x1c] = 0; // +0x70
    this[0x1d] = 0; // +0x74
    this[0x22] = uVar1; // +0x88
    this[0x1e] = 0; // +0x78
    
    *(undefined2 *)(this + 0x1f) = someFlag; // +0x7C cast to short
    this[0x21] = 0; // +0x84
    
    FUN_0060ffd0(); // Subroutine - probably initializes memory or another subsystem
    
    uVar1 = DAT_00e2b1a4;
    
    // Initialize many fields to 0 or default values
    this[0x4c] = 0; // +0x130
    this[0x50] = 0; // +0x140
    this[0x51] = 0; // +0x144
    this[0x54] = uVar1; // +0x150
    this[0x55] = 0; // +0x154
    this[0x56] = 0; // +0x158
    *(undefined2 *)(this + 0x57) = 0; // +0x15C
    *(undefined2 *)((int)this + 0x15e) = 0; // +0x15E
    *(undefined1 *)(this + 0x58) = 0; // +0x160
    *(undefined1 *)((int)this + 0x161) = 1; // +0x161 flag
    *(undefined1 *)((int)this + 0x162) = 0; // +0x162
    *(undefined1 *)((int)this + 0x163) = 0; // +0x163
    this[0x59] = 0; // +0x164
    this[0x5a] = 0; // +0x168
    this[0x5b] = 0; // +0x16C
    *(undefined1 *)(this + 0x5c) = 0; // +0x170
    
    // If a global pointer is set, call something with it
    if (DAT_0120e93c != 0)
    {
        FUN_00407e60(extraout_EDX, &DAT_0120e93c);
        uVar1 = DAT_00e2b1a4;
    }
    
    // Initialize 4 groups of 4 fields each (possibly 4 sets of simd values)
    this[0x34] = uVar1; // +0xD0
    this[0x35] = 0;     // +0xD4
    this[0x36] = 0;     // +0xD8
    this[0x37] = 0;     // +0xDC
    this[0x38] = 0;     // +0xE0
    
    this[0x39] = uVar1; // +0xE4
    this[0x3a] = 0;     // +0xE8
    this[0x3b] = 0;     // +0xEC
    this[0x3c] = 0;     // +0xF0
    this[0x3d] = 0;     // +0xF4
    
    this[0x3e] = uVar1; // +0xF8
    this[0x3f] = 0;     // +0xFC
    this[0x40] = 0;     // +0x100
    this[0x41] = 0;     // +0x104
    this[0x42] = 0;     // +0x108
    
    this[0x43] = uVar1; // +0x10C
    this[0x44] = 0;     // +0x110
    this[0x45] = 0;     // +0x114
    this[0x46] = 0;     // +0x118
    this[0x47] = 0;     // +0x11C
    
    FUN_006101b0(); // Another initialization subroutine
    
    // More field initializations
    this[0x4b] = 0; // +0x12C
    this[0x4a] = 0; // +0x128
    this[0x49] = 0; // +0x124
    this[0x48] = 0; // +0x120
    this[0x52] = 0; // +0x148
    this[0x53] = 0; // +0x14C
    this[0x4f] = uVar1; // +0x13C
    this[0x4e] = uVar1; // +0x138
    this[0x4d] = uVar1; // +0x134
    
    // Set a flag at offset +0x15E (bit 8)
    *(ushort *)((int)this + 0x15e) |= 0x100;
    
    this[0x20] = uVar1; // +0x80
    
    return this;
}