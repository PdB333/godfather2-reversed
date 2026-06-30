// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x007416d0
// Role: Destructor that switches vtable, releases a sub-object at offset 0x50, then calls global cleanup

class SomeClass;

// Offset: +0x00 vtable pointer
// Offset: +0x50 subObjectPtr (pointer to sub-object requiring cleanup)

void __fastcall SomeClass::~SomeClass(SomeClass* this)
{
    // Set vtable to a known base pointer (likely to prevent double virtual calls)
    this->vtable = (void**)&PTR_LAB_00d63ab0;

    // Check if the sub-object pointer at +0x50 is non-null and destroy it
    if (this->subObjectPtr != nullptr)
    {
        // FUN_004daf90: Likely a destructor for the sub-object
        destroySubObject(this->subObjectPtr);
    }

    // Global cleanup function (common to many destructors)
    globalCleanup();
}