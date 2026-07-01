// FUNC_NAME: SomeManager::SomeManager
void __thiscall SomeManager::SomeManager(SomeManager *this)
{
    // Call base class constructor (likely sets up base vtable or initializes members)
    FUN_00598ec0();

    // Set vtable pointer for this class
    // +0x00: vtable pointer (PTR_LAB_00d74620)
    this->vtable = (void *)&PTR_LAB_00d74620;
}

// Static instance initialization path (when called with null this pointer)
void __fastcall SomeManager::StaticInit(void *unused)
{
    // Call base class constructor for static instance
    FUN_00598ec0();

    // Set global static instance vtable pointer
    // ppuRam00000000 is the global static instance pointer
    ppuRam00000000 = (SomeManager *)&PTR_LAB_00d74620;
}