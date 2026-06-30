// FUN_NAME: Entity::Entity
// Function address: 0x0054a440
// Constructor for Entity with optional post-construction deallocation.
// Calls init() (0x0054a460) then, if param_2 & 1, calls a deallocation routine (0x009c8eb0).
// This pattern is typical for objects allocated from a fixed pool where the flag indicates
// whether the memory should be freed immediately (e.g., for temporary placement objects).

Entity* __thiscall Entity::Entity(byte flags) {
    // Initialize the object – likely sets vtable pointer and default state
    this->init(); // FUN_0054a460

    // If the low bit is set, deallocate the object's memory (e.g., return to pool)
    if ((flags & 1) != 0) {
        this->deallocateMemory(); // FUN_009c8eb0 – frees this instance
    }

    return this;
}