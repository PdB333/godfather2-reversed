// FUN_NAME: SomeClass::scalarDeletingDestructor
// Address: 0x00764ef0
// Role: Scalar deleting destructor for a class with a member pointer subobject at offset 0x64.
// Sets vtable to base class vtable (0x00d65684) for correct virtual dispatch during destruction,
// deletes the subobject if present, then deallocates the object.

void __thiscall SomeClass::scalarDeletingDestructor(SomeClass* thisObj)
{
    // Set vtable to base class vtable to prevent calling overridden virtual functions during destruction
    thisObj->vtable = reinterpret_cast<int*>(0x00d65684); // Base vtable

    // Check if the member pointer at offset 0x64 (field_0x64) is non-null
    if (thisObj->field_0x64 != nullptr) // +0x64: pointer to subobject (likely dynamically allocated)
    {
        // Call destructor/cleanup on that subobject (FUN_004daf90)
        FUN_004daf90(thisObj->field_0x64);
    }

    // Free the memory for this object (FUN_004ac1e0 is likely operator delete or a custom deallocator)
    FUN_004ac1e0(thisObj);
}