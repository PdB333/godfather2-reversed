// FUNC_NAME: SomeClass::scalarDeletingDestructor

void __thiscall SomeClass::scalarDeletingDestructor(byte flags)
{
    // Actual destructor at 0x5d1750
    this->~SomeClass();
    // If the low bit is set, call operator delete (at 0x9c8eb0)
    if (flags & 1) {
        ::operator delete(this);
    }
}