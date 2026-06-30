// FUN_NAME: Entity::Entity
// Address: 0x00598ec0
// Role: Constructor for base Entity class; sets vtable pointer to the Entity vtable.
class Entity {
public:
    void* __vtable; // +0x00

    // Constructor: initializes vtable only.
    __thiscall Entity() {
        __vtable = reinterpret_cast<void*>(0x00e3b044); // PTR_LAB_00e3b044 = Entity vtable
    }
};