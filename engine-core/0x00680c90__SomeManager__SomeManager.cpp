// FUNC_NAME: SomeManager::SomeManager

// Constructor for a manager class (EARS engine).
// Sets vtable at +0x20, initializes global flag, calls initialization routine,
// and optionally performs cleanup (e.g., delete) based on flags parameter.
// Global DAT_011298c8 is used as a singleton initialization flag.

class SomeManager {
    // +0x00: other members (likely base or data)
    // +0x20: vtable pointer
public:
    __thiscall SomeManager(byte flags) {
        if (this == nullptr) {
            return this;
        }
        // Set vtable at offset +0x20
        *(void**)(this + 0x20) = &PTR_LAB_00d580d8;

        // Reset global initialization flag
        DAT_011298c8 = 0;

        // Call base class / member initialization
        FUN_007edfb0();

        // If the object was heap-allocated (flag bit 0 set), call cleanup/destructor
        // This is a typical EA EARS pattern for constructor that handles placement new
        if ((flags & 1) != 0) {
            FUN_009c8eb0(this);
        }

        return this;
    }
};