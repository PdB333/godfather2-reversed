// FUNC_NAME: Entity::Entity
// Address: 0x00686710
// Role: Constructor for an Entity class in the EARS engine. Sets vtable, two interface pointers, calls base class initializer, and optionally registers dynamic allocation size with the memory manager.

class Entity {
public:
    void* vtable;                // +0x00
    // ... other fields
    void* someInterface1;        // +0x3C (offset 0xf words)
    void* someInterface2;        // +0x48 (offset 0x12 words)
    // Size of this class: 0x68 bytes (104)

    // Constructor; allocFlag indicates whether object was heap-allocated (bit 0 set)
    Entity(uint8_t allocFlag);
};

// External functions
void __stdcall baseConstructor();  // likely BaseClass::BaseClass(this) – no explicit arguments in decompiled code
void __stdcall registerHeapAllocation(void* ptr, int size);  // e.g., memory tracker

Entity::Entity(uint8_t allocFlag) {
    // Initialize vtable and secondary interface pointers before base init
    this->vtable = (void*)&PTR_FUN_00d589e4;      // primary vtable
    this->someInterface1 = (void*)&PTR_LAB_00d589d4; // +0x3C
    this->someInterface2 = (void*)&PTR_LAB_00d589d0; // +0x48

    // Call base class constructor (likely sets up base vtable/further fields)
    baseConstructor();

    // If dynamically allocated, register the allocation with EA's memory manager
    // Size 0x68 is the total size of this entity
    if (allocFlag & 1) {
        registerHeapAllocation(this, 0x68);
    }
}