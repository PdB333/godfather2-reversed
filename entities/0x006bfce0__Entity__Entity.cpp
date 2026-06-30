// FUNC_NAME: Entity::Entity
// Function address: 0x006bfce0
// Role: Constructor for Entity class, sets up vtable pointers and initializes sub-object

class Entity {
public:
    // +0x00: First vtable pointer
    void** vtable1;
    // +0x08: Second vtable pointer (likely for multiple inheritance or interface)
    void** vtable2;
    // ... other members ...
    // +0x270 (0x9c * 4): Pointer to a sub-object (e.g., a string or another object)
    void* subObject; // offset 0x9c

    // Constructor
    __thiscall Entity() {
        // Set vtable pointers to class-specific tables
        this->vtable1 = &PTR_FUN_00d5ee24; // First vtable
        this->vtable2 = &PTR_LAB_00d5ee1c; // Second vtable

        // If the sub-object pointer is non-null, destroy it (likely to avoid double initialization)
        if (this->subObject != nullptr) {
            destroySubObject(&this->subObject); // FUN_004daf90
        }

        // Call common initialization routine
        initializeCommon(); // FUN_006d6500
    }

private:
    // Helper functions (renamed from callees)
    void destroySubObject(void** objPtr); // FUN_004daf90
    void initializeCommon(); // FUN_006d6500
};