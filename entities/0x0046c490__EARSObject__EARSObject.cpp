// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x0046c490
// Role: Constructor for EARSObject, a base class in the EA EARS engine.
// Sets up vtable pointers, debug signatures, flags, and registers the object with a global manager.

void __thiscall EARSObject::EARSObject(void *this, int unused, int objId) {
    // Zero-initialize core fields
    *(int *)((char *)this + 4) = 0;      // +0x04: someFlag (refCount?)
    *(int *)((char *)this + 8) = 0;      // +0x08: userData
    *(int *)((char *)this + 20) = 0;     // +0x14: flags (will be ORed later)
    *(int *)((char *)this + 12) = 0;     // +0x0C: unknown
    *(int *)((char *)this + 16) = 0;     // +0x10: unknown
    *(int *)((char *)this + 24) = 0;     // +0x18: unknown
    *(int *)((char *)this + 28) = 0;     // +0x1C: unknown

    // Set debug signatures (used during development to detect memory corruption)
    *(int *)((char *)this + 32) = 0xBADBADBA;   // +0x20: debugSig1
    *(int *)((char *)this + 36) = 0xBEEFBEEF;   // +0x24: debugSig2
    *(int *)((char *)this + 40) = 0xEAC15A55;   // +0x28: debugSig3
    *(int *)((char *)this + 44) = 0x91100911;   // +0x2C: debugSig4

    // More zero-initialization
    *(int *)((char *)this + 48) = 0;     // +0x30: unknown
    *(int *)((char *)this + 52) = 0;     // +0x34: unknown
    *(int *)((char *)this + 56) = 0;     // +0x38: unknown

    // Clear debug signatures (they are no longer needed)
    *(int *)((char *)this + 44) = 0;     // +0x2C: clear debugSig4
    *(int *)((char *)this + 40) = 0;     // +0x28: clear debugSig3
    *(int *)((char *)this + 36) = 0;     // +0x24: clear debugSig2
    *(int *)((char *)this + 32) = 0;     // +0x20: clear debugSig1

    // Set vtable pointers and additional function table pointers
    VTABLE *vtable = (VTABLE *)&PTR_FUN_00e3280c;   // +0x00: main vtable
    *(void ***)this = vtable;
    *(void **)((char *)this + 60) = &PTR_FUN_00e2f19c; // +0x3C: secondary vtable (e.g., for interface)
    *(int *)((char *)this + 64) = 1;                // +0x40: someCount (initialized to 1)
    *(int *)((char *)this + 68) = 0;                // +0x44: unknown
    *(void **)((char *)this + 72) = &PTR_FUN_00e32808; // +0x48: another function table
    *(int *)((char *)this + 76) = 0;                // +0x4C: unknown

    // Set flags: OR in 0x28000000 (likely a set of bits)
    *(int *)((char *)this + 20) |= 0x28000000;      // +0x14: flags

    // Overwrite the secondary and tertiary vtable pointers with labels (maybe after registering?)  
    *(void **)((char *)this + 60) = &PTR_LAB_00e32828;  // +0x3C: different vtable label
    *(void **)((char *)this + 72) = &PTR_LAB_00e32838;  // +0x48: different label

    // OR in additional flags: 0x12 (so flags become 0x28000012)
    *(int *)((char *)this + 64) |= 0x12;            // +0x40: count (or flags?)

    // Register this object with a global manager
    // DAT_01223410 is likely a global pointer to an object manager or registration table.
    // param_3 (objId) is the unique ID for this object.
    FUN_004467c0(DAT_01223410, this, objId);
}