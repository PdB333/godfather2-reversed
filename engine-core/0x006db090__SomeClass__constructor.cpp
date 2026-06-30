// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, uint8_t flags)
{
    // Call base class constructor (likely EARSBase or similar)
    this->baseConstructor_006da8c0(); // FUN_006da8c0

    // If flag bit 0 is set, allocate and initialize a sub-object of size 0x1c0 bytes
    if ((flags & 1) != 0)
    {
        // Allocate memory (likely operator new or pool allocator)
        int* subObject = (int*)FUN_009c8f80(); // operatorNew(0x1c0)?

        // Get vtable from the newly allocated object
        int* vtable = (int*)*subObject; // vtable pointer at offset 0

        // Call the second virtual function (index 1) on the sub-object,
        // passing 'this' as an argument, possibly an initializer
        ((void (__thiscall*)(void*, int))vtable[1])(this, 0x1c0);
    }
    return this;
}