// FUNC_NAME: EARSObject::constructor
void* __thiscall EARSObject::constructor(EARSObject* this, byte flags)
{
    // Call base constructor / initialization
    this->baseConstructor(); // FUN_004403f0

    // If the flag bit 0 is set, destroy the object (likely exception handling for failed construction)
    if ((flags & 1) != 0) {
        operatorDelete(this); // FUN_009c8eb0 – typically operator delete or destructor cleanup
    }

    return this;
}