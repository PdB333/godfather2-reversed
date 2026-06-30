// FUNC_NAME: Entity::Entity
// Constructor for Entity base class.
// param_1: this pointer
// param_2: allocation flags (bit 0 = free memory after construction, used by placement new)
Entity* __thiscall Entity::Entity(Entity* this, byte allocFlags) {
    // Call the main constructor body to initialize fields
    this->init(); // FUN_0061a540 – likely sets vtable pointer and zeroes members

    // If allocFlag's low bit is set, free the memory (part of a placement new / allocation wrapper)
    if ((allocFlags & 1) != 0) {
        operatorDelete(this); // FUN_009c8eb0 – global operator delete
    }

    return this;
}