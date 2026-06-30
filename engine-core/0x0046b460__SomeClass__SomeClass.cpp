// FUNC_NAME: SomeClass::SomeClass
void __thiscall SomeClass::SomeClass(void* thisPtr)
{
    // Set vtable to base class vtable (likely EARS::Object or similar)
    *(void**)thisPtr = &vtable_BaseClass;          // +0x00: vtable pointer

    // Call base class constructor
    BaseClass::Constructor(thisPtr);               // FUN_0043e380

    // After base constructor, set vtable to derived class vtable
    *(void**)thisPtr = &vtable_SomeClass;          // +0x00: adjusted vtable for this class
}