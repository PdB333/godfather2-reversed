// FUNC_NAME: SimBaseObject::constructor
void * __thiscall SimBaseObject::constructor(SimBaseObject *this, unsigned char flags)
{
    // Set vtable pointer for this class (0x00d587e0)
    this->vtable = (void *)&PTR_FUN_00d587e0;  // +0x00 vtable pointer

    // Call base class constructor (FUN_004083d0)
    this->baseConstructor();  // Base class initialization

    // If the object was allocated on the heap (flags & 1), perform post-construction
    // cleanup or registration (FUN_009c8eb0)
    if (flags & 1) {
        this->postHeapConstruction();  // Heap-specific initialization
    }

    return this;
}