// FUNC_NAME: SomeClass::constructor
// Address: 0x0054da10
// Reconstructed constructor for a game object (likely from EA EARS engine)
// Initializes a derived class with dual vtables, zero-filling many fields,
// setting flags, and conditionally freeing a previously allocated object.

SomeClass* SomeClass::constructor(SomeClass* this) {
    // +0x00: vtable pointer to primary class
    *reinterpret_cast<int*>(this) = &PTR_FUN_00e39f10;

    // +0x18: magic constant (CRC/hash?)
    this->field_0x18 = 0xfe16702f;

    // +0x31, +0x32: two copies of same global value
    this->field_0x31 = DAT_00e2eff4;
    this->field_0x32 = DAT_00e2eff4;

    // +0x2f: second vtable pointer (likely for a secondary base/interface)
    this->field_0x2f = &PTR_LAB_00e39f14;
    this->field_0x30 = 0;

    // +0x36, +0x37: initialization (later used for cleanup)
    this->field_0x36 = 0;
    this->field_0x37 = 0;

    // +0x39: flags field, initially 0, later set to 2
    this->flags = 0;

    // +0x04: another global constant
    this->field_0x04 = DAT_00e4482c;

    // Zero out a large block (offsets 0x05 through 0x27)
    this->field_0x05 = 0;
    this->field_0x06 = 0;
    this->field_0x07 = 0;
    this->field_0x08 = 0;
    *reinterpret_cast<uint8_t*>(&this->field_0x0c) = 0; // byte at +0x31? careful: decompile says *(undefined1 *)(param_1 + 0xc) = 0; but offset might be 0x31 for byte? Actually *(undefined1 *)(param_1 + 0xc) is at offset 0x0c? But later *(undefined1 *)(param_1+0x31) = 0; so two byte assignments. Let's re-express:
    // Actually the decompiler used *(undefined1 *)(param_1 + 0xc) = 0; and *(undefined1 *)((int)param_1 + 0x31) = 0; So byte at +0x0c and byte at +0x31.
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(this) + 0x0c) = 0;
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(this) + 0x31) = 0;

    // Zero out 4-word blocks (probably arrays of 4 ints)
    for (int i = 0; i < 4; i++) {
        this->array1_0x10[i] = 0; // offsets 0x10,0x11,0x12,0x13? Actually from code: param_1[0x13], [0x12], [0x11], [0x10] are set to 0.
    }
    for (int i = 0; i < 4; i++) {
        this->array2_0x14[i] = 0; // offsets 0x14-0x17
    }
    for (int i = 0; i < 4; i++) {
        this->array3_0x18[i] = 0; // offsets 0x18-0x1b? but 0x18 already set earlier; careful: the decompiler sets [0x18] first, then later sets [0x1b],[0x1a],[0x19],[0x18] to 0? Actually it sets param_1[0x1b],[0x1a],[0x19],[0x18] after the earlier assignments? That would overwrite, so maybe the earlier assignment to 0x18 was different? Looking at the code: it sets param_1[0x18] = 0xfe16702f; then later sets param_1[0x1b]=0, param_1[0x1a]=0, param_1[0x19]=0, param_1[0x18]=0? That would overwrite. But the decompiler shows order: first set [0x18], then later set [0x1b],[0x1a],[0x19],[0x18] to 0. That might be a bug or intentional partial initialization? Actually the initial 0x18 is set to a constant, then later the block of 4 is zeroed, which includes 0x18. So the constant is overwritten? That seems odd. Possibly the decompiler's loop of 4 is for offsets 0x18-0x1b, but the prior assignment to 0x18 may be a different field? Let's check: In the code, after setting param_1[0x18], it does param_1[0x1b]=0; param_1[0x1a]=0; param_1[0x19]=0; param_1[0x18]=0; That's four consecutive assignments, but they are not a loop; the same order. So indeed it sets [0x18] to 0 again. So the initial constant 0xfe16702f is overwritten? That can't be correct. Maybe the offsets are different? The decompiler's use of indices: param_1[0x18] is the 24th int (0x60 offset). The later assignments to [0x1b],[0x1a],[0x19],[0x18] are separate. So there is a conflict. Possibly it's a typo in the decompilation? Or the earlier assignment is to a different field? The code shows: param_1[0x18] = 0xfe16702f; then later param_1[0x1b]=0; param_1[0x1a]=0; param_1[0x19]=0; param_1[0x18]=0; That would overwrite. Maybe the decompiler missed that the first is actually at a different offset? Let's assume the logic is intentional: first set a specific field to a magic number, then zero out a range of fields that does NOT include that field? But the range includes [0x18] again. Alternatively, note the pattern: after the initial setup, there are 5 groups of 4 zero-assignments: offsets 0x13-0x10 (backwards), 0x17-0x14, then 0x1b-0x18, etc. The 0x18 group is the third group. So yes, it zeros 0x18 again. This is likely a decompilation artifact: the initial 0x18 assignment might actually be to a different field that the decompiler numbered incorrectly. Possibly the actual offset is 0x18 in 4-byte units, but the later assignments are to a different set of addresses. Given the ambiguity, I'll follow the decompiled code faithfully.

    // Offsets 0x18-0x1b zeroed (after 0x18 was set to constant)
    this->field_0x1b = 0;
    this->field_0x1a = 0;
    this->field_0x19 = 0;
    this->field_0x18 = 0; // overwrites constant? keep as is.

    // Offsets 0x1f-0x1c
    this->field_0x1f = 0;
    this->field_0x1e = 0;
    this->field_0x1d = 0;
    this->field_0x1c = 0;

    // Offsets 0x22-0x20 (only 3?)
    this->field_0x22 = 0;
    this->field_0x21 = 0;
    this->field_0x20 = 0;

    // Offsets 0x27-0x24
    this->field_0x27 = 0;
    this->field_0x26 = 0;
    this->field_0x25 = 0;
    this->field_0x24 = 0;

    // +0x28: another global constant
    this->field_0x28 = DAT_00e44830;

    // +0x2a and +0x2b: two global values
    this->field_0x2a = DAT_00e2cd58;
    this->field_0x2b = DAT_00e2cd5c;
    this->field_0x29 = 0;
    this->field_0x2c = 0;
    this->field_0x2d = 0;
    this->field_0x2e = 1;

    // +0x33-0x35: zero
    this->field_0x33 = 0;
    this->field_0x34 = 0;
    this->field_0x35 = 0;

    // +0x36: if not zero, free a child object
    if (this->field_0x36 != 0) {
        FUN_004daf90(&this->field_0x36); // likely frees memory
        this->field_0x36 = 0;
    }

    // +0x39: flags manipulation
    this->flags = 0;
    this->field_0x3a = 2;
    this->field_0x38 = 8;
    this->flags = this->flags | 2; // set bit 1
    this->field_0x2d = 0; // redundant, already 0
    this->field_0x2e = 1; // redundant
    this->flags = this->flags & 0xfffffff7; // clear bit 3

    return this;
}