// FUNC_NAME: Entity::~Entity
undefined4 * __thiscall Entity::~Entity(Entity *this, byte deleteFlag)
{
    // Set vtable to this class's vtable (scalar deleting destructor)
    this->vtable = (void **)0x00d64d18;

    // Check if flag at offset +0x80 (byte) indicates incomplete init or base destruction needed
    if (!*(char *)((int *)this + 0x20)) {
        // Call base destructor or cleanup routine with size hint 0x48
        Entity::performCleanup(this, 0x48);
    }

    // Destroy dynamically allocated member at offset +0x64 (int * at index 0x19)
    if (*(int **)((int *)this + 0x19) != 0) {
        Entity::deleteMember(*(int **)((int *)this + 0x19));
    }

    // Static cleanup (likely global state)
    Entity::staticCleanup();

    // If deleteFlag bit 0 set, deallocate memory
    if ((deleteFlag & 1) != 0) {
        Entity::operatorDelete(this);
    }

    return this;
}