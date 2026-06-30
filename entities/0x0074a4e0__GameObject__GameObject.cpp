// FUNC_NAME: GameObject::GameObject

undefined4* __thiscall GameObject::GameObject(GameObject* this, byte flag)
{
    // Set vtable to class-specific vtable (offset 0x00)
    this->vtable = (GameObjectVTable*)&PTR_LAB_00d63090;

    // Check pointer at offset 0x68 (0x1a * 4) – likely a sub-object or resource
    if (this->field_0x68 != 0) {
        // Release/destroy the sub-object pointed to by field_0x68
        FUN_004daf90((undefined4*)&this->field_0x68);
    }

    // Perform base/engine initialization
    FUN_0080ea60();

    // If flag bit 0 is set, this is a deleting constructor – free memory
    if ((flag & 1) != 0) {
        FUN_00624da0(this);
    }

    return this;
}