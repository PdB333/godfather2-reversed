// FUNC_NAME: EARSObject::EARSObject

// Constructor for EARSObject base class.
// Sets up vtable pointers, performs reference counting initialization,
// then conditionally calls a cleanup/destructor if the allocation flag is set.
// param_1: this pointer
// param_2: flags – bit 0 indicates caller wants the object to manage its own memory (allocated via new)
undefined4 * __thiscall EARSObject::EARSObject(undefined4 *this, byte flags) {
    // Set base class virtual table pointers (multiple inheritance initial vtables)
    this[0] = (undefined4 *)&PTR_FUN_00e311e0;    // +0x00: first vtable pointer
    this[1] = (undefined4 *)&PTR_LAB_00e311e4;    // +0x04: second vtable pointer

    // Increment reference count for global objects (likely allocator tracking)
    FUN_004086d0(&DAT_012069c4);   // reference count on some global data
    FUN_004086d0(&DAT_012069b4);   // another reference count
    FUN_004083d0();                // perform common initialization (e.g., register with manager)

    // Switch to the final derived vtable for this class
    this[0] = (undefined4 *)&PTR_LAB_00e311f4;    // +0x00: final vtable pointer

    // Reset a global flag (possibly indicating object is active/initialized)
    DAT_01223438 = 0;

    // If caller requested self‑managed memory (flags & 1), call a cleanup function.
    // This pattern is used in placement new: if the object was allocated with new,
    // we need to free it manually when the constructor terminates abnormally.
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);       // likely: memory deallocation or destructor cleanup
    }

    return this;
}