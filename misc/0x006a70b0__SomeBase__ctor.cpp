// FUNC_NAME: SomeBase::ctor
SomeBase * __thiscall SomeBase::ctor(SomeBase *this, byte creationFlags)
{
    // Call base class constructor (likely at FUN_006a6e80)
    BaseClass::ctor(this);

    // If the low bit of creationFlags is set, perform additional memory operation
    // (likely operator delete or deallocation with size 0x74 = 116 bytes)
    if ((creationFlags & 1) != 0) {
        operatorDelete(this, 0x74); // FUN_0043b960(this, 0x74)
    }

    return this;
}