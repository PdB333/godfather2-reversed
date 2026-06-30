// FUNC_NAME: GameEntity::GameEntity
void __thiscall GameEntity::GameEntity(undefined4 *this) {
    // Set vtable to base class vtable (offset 0)
    *this = &PTR_FUN_00e327cc;  // base vtable pointer
    // Call base class constructor (0x0043e380)
    BaseObject::BaseObject(this);
    // Overwrite vtable with derived class vtable
    *this = &PTR_LAB_00e30ea0;  // derived vtable pointer
    return;
}