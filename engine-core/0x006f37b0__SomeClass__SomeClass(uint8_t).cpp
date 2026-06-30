// FUNC_NAME: SomeClass::SomeClass(uint8_t)
// Address: 0x006f37b0
// Role: Constructor for SomeClass. Calls base constructor, then optionally allocates internal buffer of size 0x118 (280 bytes) when allocFlag bit 0 is set.
// Callees: BaseClass::BaseClass() at 0x006f3210, SomeClass::allocateInternalBuffer(uint32_t size) at 0x0043b960

undefined4 __thiscall SomeClass::SomeClass(undefined4 this, byte allocFlag)
{
    BaseClass::BaseClass();                                  // Base class constructor (0x006f3210)
    if ((allocFlag & 1) != 0) {
        this->allocateInternalBuffer(0x118);                 // +0x? ; allocate 280-byte buffer (0x0043b960)
    }
    return this;
}