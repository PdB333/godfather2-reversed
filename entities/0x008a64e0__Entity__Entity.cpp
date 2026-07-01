// FUNC_NAME: Entity::Entity
// Function address: 0x008a64e0
// Role: Base class constructor for Entity objects in EA EARS engine.
// Sets vtable pointer at offset +0x18, calls base constructor, then optionally
// calls a cleanup function (likely operator delete) if the object was heap-allocated.

class Entity {
public:
    // Vtable pointer at +0x18 (offset relative to this)
    /* +0x00 */ int field_0x00; // unknown
    /* +0x04 */ int field_0x04; // unknown
    /* +0x08 */ int field_0x08; // unknown
    /* +0x0C */ int field_0x0C; // unknown
    /* +0x10 */ int field_0x10; // unknown
    /* +0x14 */ int field_0x14; // unknown
    /* +0x18 */ void** vtable; // points to PTR_LAB_00e355fc

    // Constructor
    // param_2: byte flag (1 = object was heap-allocated, calls cleanup on failure?)
    Entity(char heapAllocated) {
        // Set vtable pointer
        this->vtable = &PTR_LAB_00e355fc; // Vtable address

        // Call base class constructor (likely a more fundamental base)
        BaseConstructor(); // corresponds to FUN_0064d150

        // If heap-allocated, call cleanup function (maybe operator delete)
        if ((heapAllocated & 1) != 0) {
            CleanupFunction(this); // corresponds to FUN_009c8eb0
        }
    }

private:
    void BaseConstructor(); // placeholder for FUN_0064d150
    static void CleanupFunction(void* obj); // placeholder for FUN_009c8eb0
    static void* PTR_LAB_00e355fc; // vtable pointer (assumed static)
};