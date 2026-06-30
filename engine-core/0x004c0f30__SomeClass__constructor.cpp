// FUNC_NAME: SomeClass::constructor
// Function address: 0x004c0f30
// This function appears to be a constructor for a class, presumably from the EA EARS engine.
// It calls an initialization routine (FUN_004c0f60) and optionally invokes a function
// through a global pointer table if param_2 (a byte flag) has bit 0 set.
// The global table base is at DAT_01223410 with offset 0x2d4 pointing to a vtable-like structure.

class SomeClass {
public:
    // Constructor: takes an optional flag param_2 (bit0 = 1 triggers special cleanup?).
    // Returns the constructed object (this).
    SomeClass* __thiscall constructor(byte param_2) {
        // Call internal initialization routine
        this->init();

        // If the low bit of param_2 is set, call a function from a global table.
        // This likely represents a conditional destructor or release if construction fails.
        if ((param_2 & 1) != 0) {
            // DAT_01223410 is a global pointer (e.g., gEngine or gAllocator).
            // Offset 0x2d4 contains a pointer to a vtable or function table.
            // Offset +4 in that table is a function (likely a destructor or deallocator).
            typedef void (*CleanupFunc)(SomeClass* obj, int unknown);
            CleanupFunc cleanup = (CleanupFunc)(*(int*)(*(int*)(DAT_01223410 + 0x2d4) + 4));
            cleanup(this, 0);
        }

        return this;
    }

    // Stub for the called init function (address 0x004c0f60)
    void __thiscall init() {
        // Actual initialization logic would go here.
    }
};

// Global pointer referenced (address DAT_01223410)
extern int** DAT_01223410; // +0x2d4 likely points to an internal function table.