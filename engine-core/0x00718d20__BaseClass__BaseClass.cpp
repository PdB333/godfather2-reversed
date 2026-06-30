// FUNC_NAME: BaseClass::BaseClass
// @address 0x00718d20
// Calls base class constructor / initialization routine at 0x00718610 with this pointer.
void __thiscall BaseClass::BaseClass(void)
{
    // Pass the this pointer (implicit, placed on stack as first argument) to the base constructor.
    FUN_00718610(this);
    return;
}