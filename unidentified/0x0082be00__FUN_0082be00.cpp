// FUNC_NAME: SomeObject::constructor
undefined4 __thiscall SomeObject::constructor(byte flags)
{
    baseClassInit();                           // 0x0082a730: base class constructor/initializer
    if (flags & 1)
    {
        deallocate(this);                      // 0x009c8eb0: deallocation or cleanup
    }
    return this;                               // return this pointer
}