// FUNC_NAME: SomeClass::~SomeClass
void SomeClass::destroy()
{
    // Temporary buffer for destructor chaining
    char chainBuffer[12];

    // Call base class or additional destruction routine
    FUN_00622b80(chainBuffer, this, this->mPtr0x1c, this, this->mPtr0x1c);

    // Call virtual deallocation function (vtable[1]) to free resource of size 0x28
    // vtable is at offset +0x04 from this
    (this->vtable->release)(this->mPtr0x1c, 0x28);

    // Clear owned pointers
    this->mPtr0x1c = 0;
    this->mPtr0x20 = 0;
}