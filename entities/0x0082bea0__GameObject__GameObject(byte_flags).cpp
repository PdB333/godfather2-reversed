// FUNC_NAME: GameObject::GameObject(byte flags)
// Address: 0x0082bea0
// Constructor for a game object that inherits from Entity and NetObject.
// param_2: flags - if bit 0 is set, the object was allocated with new and needs to be deallocated (??)
undefined4* __thiscall GameObject::GameObject(undefined4* this, byte flags)
{
    int* memoryManager;

    // Set primary vtable (Entity) at offset 0
    *this = &PTR_FUN_00d737d8;
    // Call Entity base constructor
    Entity::Entity();
    // Set secondary vtable (NetObject) at offset 0x30 (this[0xC])
    this[0xC] = &PTR_LAB_00e32854;
    // Call NetObject base constructor
    NetObject::NetObject();
    // If flag bit 0 is set, deallocate memory (size 0xC0)
    if ((flags & 1) != 0) {
        memoryManager = (int*)getMemoryManager();
        // Call deallocate function at vtable offset 4
        (**(code**)(*memoryManager + 4))(this, 0xC0);
    }
    return this;
}