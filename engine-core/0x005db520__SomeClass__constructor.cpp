// FUNC_NAME: SomeClass::constructor

void* __thiscall SomeClass::constructor(void* this, byte flags)
{
    // Call base class constructor (likely EARSObject or similar)
    // FUN_005db540 - base constructor
    EARSObject::constructor(this);

    // Bit 0 of flags indicates whether to deallocate the object immediately
    // (perhaps for factory pattern or error handling)
    if ((flags & 1) != 0)
    {
        // FUN_009c8eb0 - custom deallocation (probably operator delete or pool free)
        freeObjectMemory(this);
    }

    return this;
}