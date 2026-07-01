// FUNC_NAME: UnknownClass::constructor (likely derived class constructor calling base at 0x414970)
undefined4 * __thiscall UnknownClass::constructor(UnknownClass *this, undefined4 param0, undefined4 param1)
{
    // Call base class constructor (0x414970)
    FUN_00414970(param0, param1);
    // Set vtable pointer (0x00d73ff8)
    this->vtable = (void *)0x00d73ff8;
    // Return this pointer
    return (undefined4 *)this;
}