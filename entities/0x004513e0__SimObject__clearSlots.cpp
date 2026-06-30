// FUNC_NAME: SimObject::clearSlots
void __fastcall SimObject::clearSlots(SimObject* this) {
    // Set vtable pointer (likely virtual destructor / initializer)
    this->vtable = (void**)&PTR_FUN_00e316f0;

    // Initialize global synchronization primitives (critical sections or mutices)
    initCriticalSection(&DAT_0120678c);
    initCriticalSection(&DAT_01206768);
    initCriticalSection(&DAT_01206780);
    initCriticalSection(&DAT_01206940);

    // Clear first dynamic array of 32 slots (controller / ghost entries)
    // Each slot is 10 words (40 bytes): offset 0 = object pointer, offset 3 = destructor function
    int i = 31;
    void** slotPtr = (void**)(this + 0x2f7);  // start at end of first array (+0xBDC bytes)
    do {
        if (slotPtr[-10] != 0) {
            // Invoke destructor on existing object
            ((void (*)(void*))slotPtr[-7])(slotPtr[-10]);
        }
        i--;
        slotPtr -= 10;  // move to previous slot
    } while (i >= 0);

    // Clear second dynamic array of 32 slots (offset +0x6D8 bytes)
    i = 31;
    slotPtr = (void**)(this + 0x1b6);
    do {
        if (slotPtr[-10] != 0) {
            ((void (*)(void*))slotPtr[-7])(slotPtr[-10]);
        }
        i--;
        slotPtr -= 10;
    } while (i >= 0);

    // Destroy sub‑object at offset 0x6c words (+0x1B0 bytes) if present
    if (this[0x6c] != 0) {
        ((void (*)(void*))this[0x6f])(this[0x6c]);
    }

    // Finalize / release global resources (e.g., critical sections)
    finalizeCriticalSections();
}