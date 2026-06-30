// FUNC_NAME: MissionObject::MissionObject
// Function address: 0x0046c190
// Role: Constructor for MissionObject class. Sets up vtable pointer, calls base class (GameObject) constructor, then sets final vtable.
// Note: Vtable pointers are at offset +0x00 (first member).
void __thiscall MissionObject::MissionObject(MissionObject *this)
{
    // Set initial vtable to derived class vtable (PTR_FUN_00e327e4)
    this->vtable = (VTable*)&vtable_MissionObject_initial; // +0x00

    // Call base class (GameObject) constructor
    // FUN_0043e380 likely is GameObject::GameObject
    GameObject::GameObject((GameObject*)this);

    // Overwrite vtable with final derived class vtable (PTR_LAB_00e30ea0)
    // This is typical for EARS engine constructors after base initialization
    this->vtable = (VTable*)&vtable_MissionObject_final; // +0x00

    return;
}