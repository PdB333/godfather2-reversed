// FUNC_NAME: GameObject::GameObject
// Constructor for a base game object. Sets up multiple vtables (multiple inheritance).
// this[0] points to primary vtable, this[1] points to secondary vtable (likely interface).
// param_2: bit 0 indicates heap allocation (calls a destructor-like function if set).
// After base constructor, sets global _DAT_01223468 = 0 (some global flag).
void * __thiscall GameObject::GameObject(GameObject *this, byte constructorFlag) {
    // Initial vtable pointer (base class)
    this->vtable0 = &PTR_FUN_00e31e98;          // +0x00
    // Secondary vtable pointer (secondary base or interface)
    this->vtable1 = &PTR_LAB_00e31ea4;          // +0x04

    // Call base class constructor
    BaseClass::constructor((BaseClass *)this);

    // Adjust secondary vtable after base construction
    this->vtable1 = &PTR_LAB_00e31ea8;          // +0x04

    // Reset global flag (likely indicates object state)
    _DAT_01223468 = 0;

    // Set primary vtable to final derived version
    this->vtable0 = &PTR_LAB_00e30ea0;          // +0x00

    // If object was heap-allocated (bit 0 set), call cleanup/destructor function
    if ((constructorFlag & 1) != 0) {
        FUN_009c8eb0(this);                      // operator delete or destructor
    }

    return this;
}