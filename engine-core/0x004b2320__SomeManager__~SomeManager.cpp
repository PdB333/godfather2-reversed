// FUNC_NAME: SomeManager::~SomeManager
// Address: 0x004b2320
// Destructor for SomeManager class. Handles cleanup of child object, sets global state, and optionally deallocates memory.
// Offsets:
//   param_1[0x00] : vtable pointer
//   param_1[0x04] : pointer to owned child object (non-null indicates valid)
// Global: DAT_012234b4 (likely a singleton flag or reference count)

void __thiscall SomeManager::_destructor_impl(SomeManager *this, byte freeMemoryFlag)
{
    // Set vtable to base class's destructor vtable (first stage cleanup)
    this->vtable = (int *)&PTR_FUN_00e357e0;

    // If we own a child object, call its destructor (offset +0xc is virtual destructor)
    if (this->childObject != nullptr)
    {
        (*(this->childObject->vtable + 3))(); // vtable[3] is typically destructor (offset +0xc)
        this->childObject = nullptr;
    }

    // Switch vtable to final vtable (likely base class vtable indicating destroyed state)
    this->vtable = (int *)&PTR_LAB_00e357e4;

    // Clear global reference/flag
    DAT_012234b4 = 0;

    // If freeMemoryFlag bit 0 is set, deallocate the object
    if ((freeMemoryFlag & 1) != 0)
    {
        FUN_009c8eb0(this); // custom deallocation (possibly operator delete)
    }
}