// FUNC_NAME: SomeComponent::SomeComponent (constructor, sets vtable at +0x20)
int __thiscall SomeComponent::SomeComponent(SomeComponent *this, byte flags)
{
    undefined4 *vtable_ptr;

    if (this == 0) {
        vtable_ptr = (undefined4 *)0x0;
    }
    else {
        vtable_ptr = (undefined4 *)((int)this + 0x20); // vtable pointer at +0x20
    }
    *vtable_ptr = &PTR_LAB_00d580ec; // set vtable
    DAT_01129920 = 0;                // global init flag
    FUN_007edfb0();                  // base constructor / common init
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);          // cleanup or placement delete
    }
    return (int)this;
}