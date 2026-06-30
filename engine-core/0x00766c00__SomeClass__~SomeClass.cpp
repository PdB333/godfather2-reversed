// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x00766c00
// Role: Destructor for an EA EARS game object. Cleans up child node references, deallocates objects, and calls base/subsystem cleanup.

// Assumed class layout based on offsets:
// +0x00: void** vtable
// +0x18: uint8_t flags (bit0 = 1, bit1 = 2, bit3 = 8)
// +0x50: void* somePointer
// +0x54: void* childObjectPtr (node pointer, sentinel 0x48 means invalid)

void __thiscall SomeClass::~SomeClass(void)
{
    int containerBase;

    // Redirect vtable to destructor stub to prevent callbacks during teardown
    this->vtable = &PTR_LAB_00d65850;

    // If flags indicate active child management (bit0 set, bit1 clear) and child pointer is valid (not null and not sentinel 0x48)
    if (((this->flags & 1) != 0) && ((this->flags & 2) == 0) &&
        (this->childObjectPtr != 0) && (this->childObjectPtr != 0x48))
    {
        // The child object is embedded 0x48 bytes into a parent container.
        // Calculate container base and clear bit 8 (0x100) in its control field at +0x249c.
        if (this->childObjectPtr == 0)
            containerBase = 0;
        else
            containerBase = this->childObjectPtr - 0x48;

        *(uint*)(containerBase + 0x249c) &= 0xfffffeff;  // clear bit 8

        FUN_0079d520();   // notify child removal / list update
    }

    FUN_007668f0();       // base class destructor call
    FUN_0072cf00(0);      // shutdown some engine subsystem (e.g., audio, input)

    // If flags indicate extra cleanup needed (bit3) and somePointer is valid,
    // and the global singleton is still active, call a final deinit.
    if (((this->flags & 8) != 0) && (this->somePointer != 0) &&
        (FUN_0043b870(DAT_01131018) != 0))
    {
        FUN_009ae900(0);   // deallocate or disconnect component
    }

    // Free the child object pointer (the pointer itself is behind the memory)
    if (this->childObjectPtr != 0)
    {
        FUN_004daf90(&this->childObjectPtr);   // releases memory and nulls the pointer
    }

    FUN_004ac1e0();       // final cleanup: release handles, unregister etc.
}