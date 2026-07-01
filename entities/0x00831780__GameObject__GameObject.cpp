// FUNC_NAME: GameObject::GameObject

void __thiscall GameObject::GameObject(GameObject* this)
{
    // Set base vtable pointer (offset +0x00)
    *this = &PTR_FUN_00d73868;

    // Call base class constructor
    FUN_0082b7a0();

    // Set own vtable pointer at offset +0x30 (this[0xC])
    this[0xC] = &PTR_LAB_00e32854;

    // Call derived class initialization
    FUN_00821f60();

    return;
}