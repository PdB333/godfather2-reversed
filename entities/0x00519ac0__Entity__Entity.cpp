// FUNC_NAME: Entity::Entity
// Address: 0x00519ac0
// Constructor for Entity class (base class for game objects).
// Initializes base class and optionally performs vtable-based initialization.

Entity* __thiscall Entity::Entity(byte allocFlags) {
    // +0x00: Call base class constructor (likely EARS::Framework::Object or similar)
    BaseEntity::BaseEntity(); // 0x00519af0 - base initializer

    // If the low bit of allocFlags is set, perform additional initialization via vtable
    if (allocFlags & 1) {
        // Get the default vtable pointer for this class (from singleton or static data)
        int* vtable = (int*)getObjectVTable(); // 0x009c8f80 - returns pointer to class vtable table
        // Call virtual function at offset 4 (second slot) with a parameter '0'
        // This is typically a virtual Initialize or PostConstruct method
        void (__thiscall *initFunc)(void*, int) = (void (__thiscall*)(void*, int))vtable[1];
        initFunc(this, 0);
    }

    return this;
}

// Note: BaseEntity::BaseEntity is a placeholder for the actual base class constructor at 0x00519af0.
// The vtable offset 4 corresponds to the second virtual function (index 1) after the destructor.