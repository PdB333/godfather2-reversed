// FUNC_NAME: Entity::Entity
// Function at 0x008cc4c0: Constructor for Entity class (speculative)
// Parameters: this, param2, param3, param4 (passed to base class constructor)
// Calls base constructor, sets up vtable pointers for multiple inheritance, initializes fields, and calls additional init

class Entity
{
public:
    // Constructor
    Entity(void* param2, void* param3, void* param4)
    {
        // Call base class constructor (likely SimObject or similar)
        FUN_004b6060(param2, param3, param4); // Base::Base(param2, param3, param4)

        // Set vtable pointers for multiple inheritance
        // Temporary purecall vtable at offset 0x2C (11*4)
        this->vtable3 = &PTR___purecall_00e3924c;
        // Primary vtable at offset 0
        this->vtable1 = &PTR_FUN_00d7c488;
        // Secondary vtable at offset 0x0C (3*4)
        this->vtable2 = &PTR_LAB_00d7c474;
        // Override tertiary vtable at offset 0x2C (11*4)
        this->vtable3 = &PTR_FUN_00d7c460;

        // Initialize fields
        this->field_0x30 = 0; // offset 0x30 (12*4)
        this->field_0x38 = 0; // offset 0x38 (14*4)

        // Call additional initialization
        FUN_008cc2e0(); // Entity::init() or similar
    }

private:
    // Vtable pointers (actual layout may differ)
    void* vtable1;       // +0x00
    // ... other members ...
    void* vtable2;       // +0x0C
    // ... other members ...
    void* vtable3;       // +0x2C
    int field_0x30;      // +0x30
    int field_0x38;      // +0x38
};