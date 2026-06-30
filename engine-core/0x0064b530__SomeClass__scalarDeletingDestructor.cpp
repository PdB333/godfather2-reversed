// FUNC_NAME: SomeClass::scalarDeletingDestructor
undefined4 __thiscall SomeClass::scalarDeletingDestructor(SomeClass* this, byte flags)
{
    // Call the actual destructor (which may chain base destructors)
    this->~SomeClass(); // FUN_0064b440 - likely the destructor
    // If the flag indicates memory deallocation, call operator delete
    if (flags & 1) {
        SomeClass::operator delete(this); // FUN_009c8eb0 - likely operator delete
    }
    return this; // Return pointer to freed memory (common MSVC scalar deleting destructor behavior)
}