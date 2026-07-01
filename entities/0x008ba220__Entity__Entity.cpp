// FUNC_NAME: Entity::Entity
undefined4* __thiscall Entity::Entity(undefined4* this, void* pool) {
    // Called with a memory pool (size 0x4000) for initialization
    // pool->init? (FUN_0046e6b0)
    FUN_0046e6b0(pool, 0x4000);

    undefined4 uVar1 = _DAT_00d5780c;
    undefined4 uVar2 = DAT_00d5d7b8;

    // Initialize sentinel values for debugging (badba, beef, etc.)
    // These are later cleared after proper setup
    this[0x6d] = 0xbadbadba;  // +0x1b4
    this[0x6e] = 0xbeefbeef;  // +0x1b8
    this[0x6f] = 0xeac15a55;  // +0x1bc
    this[0x70] = 0x91100911;  // +0x1c0
    this[0x71] = 0xbadbadba;  // +0x1c4
    this[0x72] = 0xbeefbeef;  // +0x1c8
    this[0x73] = 0xeac15a55;  // +0x1cc
    this[0x74] = 0x91100911;  // +0x1d0

    // Set vtable pointers for multiple base classes
    this[0x60] = &PTR_LAB_00d58278;   // +0x180 first vtable
    this[0xf]  = &PTR_LAB_00d7b5c8;   // +0x3c
    this[0x12] = &PTR_LAB_00d7b5c4;   // +0x48
    this[0x14] = &PTR_LAB_00d7b5c0;   // +0x50
    this[0x15] = &PTR_LAB_00d7b560;   // +0x54
    this[0x16] = &PTR_LAB_00d7b4f8;   // +0x58
    this[0x60] = &PTR_LAB_00d7b4e0;   // +0x180 overridden with derived vtable

    // Zero out multiple fields
    this[0x61] = 0;                  // +0x184
    this[99]   = 0;                  // +0x18c flags
    this[100]  = uVar1;              // +0x190 copy from global
    this[0x65] = 0;                  // +0x194
    this[0x66] = 0;                  // +0x198
    this[0x67] = 0;                  // +0x19c
    this[0x6b] = 0;                  // +0x1ac
    this[0x6c] = 0;                  // +0x1b0
    this[0x75] = 0;                  // +0x1d4
    this[0x76] = 0;                  // +0x1d8
    this[0x77] = 0;                  // +0x1dc
    this[0x78] = 0;                  // +0x1e0
    this[0x79] = 0;                  // +0x1e4
    this[0x7a] = 0;                  // +0x1e8

    // Copy global values to specific fields
    this[0x7b] = uVar2;             // +0x1ec
    this[0x7c] = DAT_00e446f4;      // +0x1f0
    this[0x7d] = _DAT_00d69734;     // +0x1f4
    this[0x7e] = DAT_00e44634;      // +0x1f8
    this[0x82] = 0;                  // +0x208
    this[0x83] = 0;                  // +0x20c
    this[0x84] = 0;                  // +0x210
    this[0x85] = 0;                  // +0x214
    this[0x86] = DAT_00e445ac;      // +0x218

    // Initialize byte fields
    *(undefined1*)(this + 0x87) = 0;   // +0x21c first byte
    *(undefined1*)((int)this + 0x21d) = 0; // +0x21d
    *(undefined1*)((int)this + 0x21e) = 1; // +0x21e
    *(undefined1*)((int)this + 0x21f) = 0; // +0x21f
    *(undefined1*)(this + 0x88) = 0;      // +0x220 first byte

    this[0x8a] = 0;                  // +0x228
    this[0x8b] = 200;                // +0x22c default speed?
    this[0x8c] = uVar1;              // +0x230
    this[0x89] = 0;                  // +0x224
    this[0x8d] = 0;                  // +0x234
    this[0x8e] = uVar1;              // +0x238
    this[0x8f] = uVar1;              // +0x23c
    this[0x9c] = 0;                  // +0x270
    this[0x9d] = 0;                  // +0x274
    this[0x9e] = 0;                  // +0x278
    this[0x9f] = 0;                  // +0x27c
    this[0xa0] = 0;                  // +0x280

    // General initialization call
    FUN_00481530();

    // Set flags
    this[5]   = this[5] | 0x4000000;     // +0x14
    this[99]  = this[99] | 1;            // +0x18c
    this[0xa3] = 0;                  // +0x28c
    this[0xa2] = 0;                  // +0x288
    this[0xa1] = 0;                  // +0x284

    // Clear all sentinel fields (they were placeholders)
    this[0x70] = 0;  // +0x1c0
    this[0x6f] = 0;  // +0x1bc
    this[0x6e] = 0;  // +0x1b8
    this[0x6d] = 0;  // +0x1b4
    this[0x74] = 0;  // +0x1d0
    this[0x73] = 0;  // +0x1cc
    this[0x72] = 0;  // +0x1c8
    this[0x71] = 0;  // +0x1c4
    this[0x7f] = 0;  // +0x1fc
    this[0x80] = 0;  // +0x200
    this[0x81] = 0;  // +0x204

    // Load additional data if present
    if (DAT_0120e93c != 0) {
        FUN_00408900(this + 0xf, &DAT_0120e93c, 0x8000);  // copy or load data
    }

    // Check for feature flag and show message if not available
    char cVar3 = FUN_00842870();
    if (cVar3 == '\0') {
        this[99] = this[99] | 0x4000000;  // set flag
        FUN_004704d0(0, 0, 1);            // show warning?
    }

    return this;
}