// FUNC_NAME: Entity::initFromDescriptor
// Address: 0x004f2de0
// Role: Initializes entity from a descriptor struct (string + ID) if not already flagged

// Declare the descriptor structure passed in param_1
struct EntityDescriptor {
    char* name;            // +0x00: pointer to null-terminated string
    // ... padding/other fields ...
    int nameID;            // +0x20: some integer identifier
};

// Base class constructor (likely sets up vtable and base fields)
extern void EntityBaseConstructor(); // FUN_00533cc0

class Entity {
public:
    void** vtable;                 // +0x00
    // ... other fields ...
    char nameBuffer[?];            // +0x28: string buffer (size unknown)
    int nameID;                    // +0x24: identifier copied from descriptor

    void initFromDescriptor(EntityDescriptor* descriptor) {
        EntityBaseConstructor();
        this->vtable = &PTR_FUN_00e375e8; // assign vtable

        // Check if initialization already done (byte flag at parent object offset +0x0D)
        // 'edi' likely points to a parent or context object
        if (*(char*)(unaff_EDI + 0x0D) == '\0') {
            // Copy string from descriptor->name to internal buffer at +0x28
            char* src = descriptor->name;
            char* dst = (char*)(this + 0x28);
            while (*src) {
                *dst = *src;
                src++;
                dst++;  // implicit via index arithmetic
            }
            // Copy integer from descriptor at +0x20 to this->nameID at +0x24
            this->nameID = *(int*)((char*)descriptor + 0x20);
        }
    }
};