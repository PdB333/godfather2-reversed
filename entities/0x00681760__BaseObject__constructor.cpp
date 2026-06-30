// FUNC_NAME: BaseObject::constructor
// Class with dual vtable pointers (at +0x00 and +0x04) and a global initialized flag
class BaseObject {
public:
    void* vtable1; // +0x00 (pointer to purecall vtable for abstract base)
    void* vtable2; // +0x04 (pointer to actual class vtable)

    // Global flag that is reset during construction (at 0x0112994c)
    static int g_initialized;

    // Constructor: param_2 is a byte flag; if bit0 is set, memory is freed after initialization
    BaseObject* __thiscall constructor(byte flags) {
        BaseObject* self = this;
        BaseObject* vtableOffsetPtr = this;

        // Guard against null this pointer
        if (this != nullptr) {
            vtableOffsetPtr = this + 1;  // Points to offset +0x04
        }

        // Set the second vtable pointer first (destination vtable)
        *vtableOffsetPtr = &PTR_LAB_00d580f4;  // +0x04: real vtable

        // Reset global initialized flag
        g_initialized = 0;

        // Set the first vtable pointer (abstract base purecall vtable)
        *this = &PTR___purecall_00d580a8;      // +0x00: purecall vtable

        // If the allocation flag (bit0) is set, free the object
        if ((flags & 1) != 0) {
            // Calling operator delete on the object (FUN_009c8eb0)
            operator delete(this);
        }

        return this;
    }
};

// Global variable definition (actual address: 0x0112994c)
int BaseObject::g_initialized = 0;