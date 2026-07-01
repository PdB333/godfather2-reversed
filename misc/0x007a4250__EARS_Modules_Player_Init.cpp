// Xbox PDB: EARS_Modules_Player_Init
// FUNC_NAME: EntityBase::resetState
// Reconstructed C++ for Godfather 2 (EARS engine) - EntityBase::resetState at 0x007a4250
// Clears state flags, resets timers, resets animation/script, clears various arrays and pointers.
// Parameter: param_2 = true if animation/script root should also be reset.
void __thiscall EntityBase::resetState(EntityBase* this, bool resetAnimationRoot)
{
    // Multiple calls to an unknown function (possibly timer-related or frame callback)
    FUN_004df600();  // Unknown - perhaps FrameAdvance or UpdateTimers
    FUN_004df600();
    FUN_007f6420(0x56); // Send message/event ID 0x56

    if (this->field_0xae0 != 0) {
        FUN_004df600();  // Another timer update if some pointer non-null
    }

    // Clear bit 14 (0x4000) of flags at +0x929
    this->flags_0x929 = this->flags_0x929 & ~0x4000;

    if (resetAnimationRoot) {
        // Clear bit 8 (0x100) of flags at +0x928
        this->flags_0x928 = this->flags_0x928 & ~0x100;

        // Access a script controller or animation object via pointer at +0x17d (0x5F4 bytes)
        int* scriptController = *(int**)this->ptr_0x17d; // dereference double pointer?
        // Actually param_1[0x17d] is an int that holds a pointer; we treat as int* indirectly
        // The decompiler shows: iVar1 = *(int *)param_1[0x17d]; meaning: iVar1 = *(int*)(this->field_0x17d)
        // So field_0x17d is a pointer to an object that has a vtable at +0x2c and +0x3c
        int* someObj = (int*)*(int*)((uintptr_t)this + 0x17d * 4); // Wait: param_1[0x17d] means *(this + 0x17d*4) is an int that is a pointer; then we dereference that to get another pointer
        // Actually the code: iVar1 = *(int *)param_1[0x17d];
        // This means: take the int stored at offset 0x17d*4, treat it as a pointer, read the int at that pointer? That seems odd.
        // More likely: param_1[0x17d] is a pointer to an object, and we dereference it to get the vtable? No, the next line uses iVar1 as a vtable pointer, so iVar1 = the address of the vtable? Actually: iVar1 = *(int *)param_1[0x17d]; means: treat the int stored at this+0x5F4 as a pointer (to an object), then read the first int of that object (the vtable pointer). So iVar1 is the vtable pointer of that object.
        // Then we call functions at vtable+0x2c and vtable+0x3c.
        // Let's simplify: it's a pointer to a ScriptController or similar.
        int* scriptObjVtable = *(int**)(*(int*)((uintptr_t)this + 0x5F4)); // dereference double pointer
        // Call vfunc 0x2c (likely getCurrentTime or something) and then vfunc 0x3c with that value (setTime?)
        float currentTime = ((float(__thiscall*)(int*))(*scriptObjVtable + 0x2c))(scriptObjVtable);
        ((void(__thiscall*)(int*, float))(*scriptObjVtable + 0x3c))(scriptObjVtable, currentTime);
    }

    // Clear bit 5 (0x10) of flags at +0x61
    this->flags_0x61 = this->flags_0x61 & ~0x10;

    // If bit 0 of field at +0x927 is not set, call FUN_007984f0 and set bit
    if (!(this->field_0x927 & 1)) {
        FUN_007984f0();  // Unknown - maybe initialize something
        this->field_0x927 |= 1;
    }

    // Access a global and call FUN_007f89d0 (maybe a UI element or something)
    FUN_007f89d0(&DAT_00d6a4f4); // DAT_00d6a4f4 is a global variable (likely a struct or string)

    if (this->field_0x12a != 0) {
        FUN_005512c0(0);  // Unknown - maybe stop a timer
    }

    // Multiple calls to update or state management functions
    FUN_00896e70();  // Unknown
    FUN_00460880();  // Unknown
    FUN_00551390(1, _DAT_00d6a504, 3); // Unknown - parameters: int, global, int

    // Send events/messages 0x10 and 0x11
    FUN_007f6420(0x10);
    FUN_007f6420(0x11);

    // Clear multiple bits in flags at +0x6e5
    this->flags_0x6e5 = this->flags_0x6e5 & ~0x2;  // bit 1
    this->flags_0x6e5 = this->flags_0x6e5 & ~0x10; // bit 4
    this->flags_0x6e5 = this->flags_0x6e5 & ~0x4;  // bit 2
    this->flags_0x6e5 = this->flags_0x6e5 & ~0x8;  // bit 3

    FUN_007f6420(0xb);
    FUN_007f6420(0x2d);

    // Clear bits in various flag fields
    this->field_0x927 = this->field_0x927 & ~0x20000000; // bit 29
    this->flags_0x929 = this->flags_0x929 & ~0x2;        // bit 1
    this->flags_0x929 = this->flags_0x929 & ~0x4;        // bit 2

    // Check if on console (maybe debug or specific platform)
    bool isConsole = FUN_00481640();
    if (isConsole) {
        FUN_007f4740();  // Unknown - maybe disable v-sync or something
        FUN_007f4690();  // Unknown
    }

    // Determine a value based on bit 1 of field_at_0x238 (shift right 1, mask 1)
    // If that bit is 0, uVar5 = 0; else uVar5 = 4
    int someValue = ( (uint)this->field_0x238 >> 1 & 1 ) == 0 ? 0 : 4;

    // Call vtable function at offset 0x234 (index 0x234/4 = 0x8D)
    ((void(__thiscall*)(EntityBase*, int, int))(*((int**)this)[0x8D]))(this, someValue, 1);

    // Call vtable function at offset 0x14c (index 0x53) with a computed argument
    // The argument is a conditional value: if bit1 is set, use -0x6e24e6c2? Actually:
    // (-(uint)(bit != 0) & 0x6e24e6c2) + 0x46f5c7b4
    // When bit != 0: -1 & 0x6e24e6c2 = 0x6e24e6c2, add 0x46f5c7b4 = 0xB51A9E76
    // When bit == 0: 0 + 0x46f5c7b4 = 0x46f5c7b4
    uint arg = (bit1Active ? 0x6e24e6c2 : 0) + 0x46f5c7b4;  // Wait, the formula: (-(uint)(bit) & 0x6e24e6c2) + 0x46f5c7b4
    // If bit is 1, -(1) = 0xFFFFFFFF, &0x6e24e6c2 = 0x6e24e6c2, +0x46f5c7b4 = 0xB51A9E76
    // If bit is 0, -(0)=0, &0 = 0, +0x46f5c7b4 = 0x46f5c7b4
    // So arg = 0x46f5c7b4 or 0xB51A9E76. These look like magic constants. Possibly used for sending a message or event ID.
    uint arg1 = (bit1Active ? 0x6e24e6c2 : 0) + 0x46f5c7b4;
    ((void(__thiscall*)(EntityBase*, uint, int, int))(*((int**)this)[0x53]))(this, arg1, 0, 0);

    // Call vtable function at offset 0x280 (index 0xA0) - no parameters besides this
    ((void(__thiscall*)(EntityBase*))(*((int**)this)[0xA0]))(this);

    // Clear a block of 10 integer fields from offset 0xc1b to 0xc24 (contiguous)
    // Also set field at 0xc25 to -1
    this->field_0xc1b = 0;
    this->field_0xc1c = 0;
    this->field_0xc1d = 0;
    this->field_0xc1e = 0;
    this->field_0xc1f = 0;
    this->field_0xc20 = 0;
    this->field_0xc21 = 0;
    this->field_0xc22 = 0;
    this->field_0xc23 = 0;
    this->field_0xc24 = 0;
    this->field_0xc25 = -1;

    // Check and possibly destroy a pointer at offset 0x92d
    int* ptr_0x92d = (int*)((uintptr_t)this + 0x92d * 4);
    if (*ptr_0x92d != 0) {
        FUN_004daf90(ptr_0x92d);  // Unknown - possibly destructor
        *ptr_0x92d = 0;
    }

    // Set a global variable (DAT_01129900 + 0x2c) to 0
    *(int*)(DAT_01129900 + 0x2c) = 0;

    // Clear bit 9 (0x200) of a field at +0x86 (offset 0x218? Actually param_1[0x86] is an int pointer? Wait: param_1[0x86] is an int that is a pointer to another structure)
    // *(uint *)(param_1[0x86] + 0x10) = ... means: take the int from offset 0x86*4, treat as pointer, add 0x10, clear bit 9
    int* somePtr = (int*)*(int*)((uintptr_t)this + 0x86 * 4);
    *(uint*)((uintptr_t)somePtr + 0x10) &= ~0x200;

    // Call vtable function at offset 0x94 (index 0x25) with a string parameter "r_clav" (likely a bone name)
    ((void(__thiscall*)(EntityBase*, const char*))(*((int**)this)[0x25]))(this, "r_clav");

    // Check if console and some animation indices are valid, and global pointer condition
    if (isConsole && (this->field_0x7be != -1) && (this->field_0x7bd != -1)) {
        int* globalPtr = *(int**)(DAT_0112b9b4 + 0x40); // global pointer to some manager
        if ((globalPtr != 0) && (globalPtr[0x36] == 2) && (this->field_0xc47 == 0)) {
            // Call vtable functions on that globalPtr (animation controller?)
            ((void(__thiscall*)(int, int))(*((int**)globalPtr)[0x33]))(this->field_0x7be); // offset 0xcc
            ((void(__thiscall*)(int, EntityBase*))(*((int**)globalPtr)[0x31]))(this); // offset 0xc4
        }
    }

    // Check if in multiplayer mode
    bool isMultiplayer = FUN_008a4380();
    if (isMultiplayer) {
        int someId = FUN_007057c0();  // Gets some ID (maybe player ID or team)
        // Call vtable function at offset 600 (decimal) = 0x258 (index 0x96)
        ((void(__thiscall*)(EntityBase*, int))(*((int**)this)[0x96]))(this, someId);
        // Call vtable function at offset 0x25c (index 0x97)
        ((void(__thiscall*)(EntityBase*))(*((int**)this)[0x97]))(this);
    }
}