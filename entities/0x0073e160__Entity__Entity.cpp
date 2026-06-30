// FUNC_NAME: Entity::Entity
// Address: 0x0073e160
// Role: Base class constructor for the Entity hierarchy.
// Initializes base class via FUN_0080e6a0, sets vtable, and zeroes several fields.
// vtable at +0x00, field at +0x50 (0x14*4), +0x58 (0x16*4), +0x5C (0x17*4), etc.

#define VTABLE_ENTITY 0x00d63090  // Placeholder; actual vtable in binary

// Forward declaration: base class initialization functions
void Entity_InitializeBase(void* arg1, void* arg2);  // FUN_0080e6a0

class Entity {
public:
    // Vtable pointer at offset 0
    void** vtable;

    // Unknown fields at various offsets
    // offset +0x50 (index 0x14): some pointer or index
    // offset +0x58 (index 0x16): some field initialized to 0
    // offset +0x5C (index 0x17): copy from field at +0x50
    // offset +0x60 (index 0x18): counter or flag, 0
    // offset +0x64 (index 0x19): another flag, 0
    // offset +0x68 (index 0x1A): another flag, 0
    // offset +0x6C (index 0x1B): another flag, 0

    // Note: these are placeholders; actual member names and types unknown.
    // We use int for simplicity, but could be pointers (4 bytes on x86).
    int field_0x50;  // +0x50
    int field_0x58;  // +0x58
    int field_0x5C;  // +0x5C
    int field_0x60;  // +0x60
    int field_0x64;  // +0x64
    int field_0x68;  // +0x68
    int field_0x6C;  // +0x6C

    // Constructor
    Entity(void* arg1, void* arg2) {
        // Call base class constructor (FUN_0080e6a0)
        Entity_InitializeBase(arg1, arg2);

        // Set vtable
        this->vtable = (void**)VTABLE_ENTITY;

        // Initialize members
        this->field_0x58 = 0;      // param_1[0x16]
        this->field_0x60 = 0;      // param_1[0x18]
        this->field_0x5C = this->field_0x50;  // param_1[0x17] = param_1[0x14]
        this->field_0x64 = 0;      // param_1[0x19]
        this->field_0x68 = 0;      // param_1[0x1A]
        this->field_0x6C = 0;      // param_1[0x1B]
    }
};