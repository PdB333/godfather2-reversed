// FUNC_NAME: SimManager::~SimManager

// Destructor for SimManager class. Releases resources: internal pointer at offset 0x7c,
// singleton allocator (DAT_0112ded0), debug flag, and frees data at offsets 0x88 and 0x68.
// Restores vtable to base class at the end.

void __thiscall SimManager::~SimManager(void *this)
{
    // Offsets (relative to this pointer):
    // +0x00: vtable pointer (set to derived class vtable during destruction)
    // +0x70: secondary vtable pointer (multiple inheritance)
    // +0x7c: pointer to allocated data (freed via FUN_009af0a0)
    // +0x88: allocated block (freed via FUN_004daf90)
    // +0x90: byte flags (bit0 indicates debug state)
    // +0x68: another allocated block (freed via FUN_004daf90)

    uint *thisPtr = (uint *)this;

    // Set vtable pointers to destruction-phase vtables
    thisPtr[0x00] = &PTR_LAB_00d68390;
    thisPtr[0x1c] = &PTR_LAB_00d68380;  // secondary vtable at offset +0x70
    thisPtr[0x1f] = &PTR_FUN_00d6836c;  // stored as a function pointer, later used as address

    // Initial cleanup call (possibly resource tracker update)
    FUN_007f75b0();

    // Pointer to the field at offset +0x88
    uint *ptrField88 = thisPtr + 0x22;

    // Condition: if the value at offset +0x88 is non-zero and not 0x48 (sentinel)
    if ((thisPtr[0x22] != 0) && (thisPtr[0x22] != 0x48)) {
        // Cleanup global singleton (allocator?) and release block at +0x7c
        FUN_0043b870(DAT_0112ded0);
        FUN_009af0a0(thisPtr + 0x1f);  // free the data at offset +0x7c
    }

    // Check debug flag at offset +0x90 (byte, bit 0)
    if ((*(byte *)(thisPtr + 0x24) & 1) != 0) {
        // Cleanup another global singleton (stream manager?)
        FUN_004086d0(&DAT_0112e028);
    }

    // Free the block at offset +0x88 if it is non-zero
    if (*ptrField88 != 0) {
        FUN_004daf90(ptrField88);  // custom deallocation (sets pointer to zero internally)
    }

    // General cleanup (memory manager flush)
    FUN_004083d0();

    // Restore vtable to base class for base destructor
    thisPtr[0x00] = &PTR_LAB_00d63090;

    // Free the block at offset +0x68 if non-zero
    if (thisPtr[0x1a] != 0) {
        FUN_004daf90(thisPtr + 0x1a);
    }

    // Final cleanup call
    FUN_0080ea60();

    return;
}