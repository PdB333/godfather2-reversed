// FUNC_NAME: BaseClass::destructor
void __thiscall BaseClass::destructor(BaseClass *this)
{
    // +0x1C: pointer to sub-object (or allocated data) that has a destructor at +0x28
    if (*(void **)((int)this + 0x1C) != 0) {
        (*(void (__thiscall **)(void *))((int)this + 0x28))(*(void **)((int)this + 0x1C));
    }
    // +0x0C: another sub-object with destructor at +0x18
    if (*(void **)((int)this + 0x0C) != 0) {
        (*(void (__thiscall **)(void *))((int)this + 0x18))(*(void **)((int)this + 0x0C));
    }
    // Reset vtable to base class (global static vtable)
    *(int **)this = &PTR_LAB_00d576d4;
}