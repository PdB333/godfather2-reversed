// FUNC_NAME: ObjectBase::Constructor
// Function address: 0x00680d90
// Role: Constructor for object with vtable pointer at offset +0x20.
// Calls a base initializer and optionally frees memory if the lower bit of flag is set.

// Reconstructed C++
class ObjectBase {
public:
    // Vtable pointer at +0x20
    void** vtable; // +0x20

    // Constructor - param_2: bit 0 indicates whether to free memory after construction
    int __thiscall Constructor(byte flag) {
        // Null-check on this pointer (debug safety)
        void** vtableDest = (this != nullptr) ? (void**)(this + 0x20) : nullptr;
        // Set vtable to class-specific table
        *vtableDest = &PTR_LAB_00d580e8;  // Assign vtable

        // Reset global variable (likely a singleton counter or manager state)
        DAT_011298f4 = 0;

        // Call base-class initializer / sub-constructor
        FUN_007edfb0();

        // If flag bit 0 is set, free the memory (e.g., heap-allocated object)
        if ((flag & 1) != 0) {
            FUN_009c8eb0(this);  // operator delete or custom deallocator
        }
        return (int)this;
    }
};