// FUNC_NAME: SomeClass::SomeClass(byte flag)
// Address: 0x008b6920
// Role: Constructor with placement flag; calls base constructor, then optionally deallocates memory if flag is set.

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte flag)
{
    // Call base class constructor
    BaseClass::BaseClass(); // +0x00 base class constructor (FUN_008b66c0)

    // If flag bit 0 is set, deallocate memory (size 0x90 = 144 bytes)
    if ((flag & 1) != 0) {
        MemoryDeallocate(this, 0x90); // operator delete or custom free (FUN_0043b960)
    }

    return this;
}