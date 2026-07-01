// FUNC_NAME: SimManager::destroy
void __fastcall SimManager::destroy(SimManager *this)
{
    int slotIndex;
    int *slotPtr;

    // Set vtable pointers for multiple inheritance cleanup
    this->vtable0 = &PTR_FUN_00d81140; // Base class vtable
    this->vtable1_offset0x824 = &PTR_LAB_00d810f0; // Interface or secondary base
    this->vtable2_offset0x825 = &PTR_LAB_00d810ec;

    // Release two global locks or resources
    FUN_004086d0(&DAT_01222240); // Probably destructor for lock object
    FUN_004086d0(&DAT_01222250);

    // Release a child object if present
    if (this->childPtr != 0) {
        (*(code **)((*(int *)this->childPtr) + 4))(); // Call vfunc[1] (destructor)
        this->childPtr = 0;
    }

    // Further cleanup
    FUN_008f3970(); // Another subsystem destructor

    // Destroy an array of 26 slots (each with a pointer + destructor function pointer)
    slotIndex = 26;
    slotPtr = (int *)&this->slotArrayStart; // +0x898
    do {
        if (slotPtr[-4] != 0) {
            (*(code *)slotPtr[-1])(slotPtr[-4]); // Destroy object using pointer and function
        }
        slotIndex--;
        slotPtr -= 1; // Move to previous slot (4 ints back = 16 bytes)
    } while (slotIndex >= 0);

    // Set vtable pointers to sentinel values indicating object is being destroyed
    this->vtable2_offset0x825 = &PTR_LAB_00d810e8;
    DAT_01129828 = 0; // Global flag
    this->vtable1_offset0x824 = &PTR_LAB_00d81098;

    // Final cleanup call
    FUN_008f2860();
    return;
}