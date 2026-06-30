// FUNC_NAME: Entity::~Entity
// Address: 0x00549950
// Destructor for a game entity that holds a reference-counted child object.
// The child object is at offset 0x18 (this[6]) and has reference counters.
// If the delete flag (param_2) is set, deallocates memory via thread-local heap.

class Entity {
public:
    virtual ~Entity(byte deallocFlag);
    // +0x00: vtable pointer
    // +0x04: unknown short (size field?)
    // +0x18: pointer to child object (ref-counted)
};

// Child object structure
struct ChildObject {
    void* vtable;      // +0x00
    short refCount;    // +0x04
    short useCount;    // +0x06
};

extern void* PTR_FUN_00e39ba8; // Temporary vtable (destructor phase)
extern void* PTR_LAB_00d96914; // Base vtable after child released
extern DWORD DAT_01139810;     // TLS index for heap

extern void __fastcall FUN_00aa26e0(void* ptr, unsigned int size, byte blockType);

Entity::~Entity(byte deallocFlag) {
    ChildObject* child = (ChildObject*)this->field_0x18; // +0x18
    
    // Set temporary vtable (first step of destruction)
    *(void**)this = &PTR_FUN_00e39ba8;
    
    if (child != nullptr) {
        // Check if child has any references (refCount != 0)
        if (child->refCount != 0) {
            // Decrement useCount; if it reaches zero, destroy child
            child->useCount--;
            if (child->useCount == 0) {
                // Call child's destructor via its vtable (function at offset 0)
                ((void(*)(int))child->vtable)(1);
            }
        }
        // Clear the child pointer
        this->field_0x18 = nullptr;
    }
    
    // Set base vtable (after child cleanup)
    *(void**)this = &PTR_LAB_00d96914;
    
    if (deallocFlag & 1) {
        // Get thread-local heap handle
        void* heap = TlsGetValue(DAT_01139810);
        // Deallocate this object with its stored size (short at offset +4)
        unsigned int size = *(unsigned short*)((byte*)this + 4);
        FUN_00aa26e0(this, size, 0xb);
    }
}