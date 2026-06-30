// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x0056e210
// Role: Constructor for EARSObject with optional deallocation flag.
// Called from various places; the byte parameter controls whether a cleanup
// function is invoked after base initialization. Bit 0 set indicates the
// object should call its deallocation routine (e.g., if it was heap-allocated).

class EARSObject {
public:
    // Constructor: initializes base components, then conditionally frees memory.
    // param_1 (this): pointer to the object being constructed.
    // param_2: flags byte; bit 0 => call deallocate on completion.
    // Returns this (parameter passed back).
    EARSObject* __thiscall constructor(byte flags) {
        // Call base class initialization (e.g., vtable setup, member init).
        baseConstruct();

        // If bit 0 is set, the object should be deallocated after construction.
        // This pattern is used for temporary objects or placement-new scenarios.
        if ((flags & 1) != 0) {
            deallocate(this);  // Custom deallocation function at 0x009c8eb0
        }

        return this;
    }

private:
    // Internal initialization function (FUN_0056e230).
    void __thiscall baseConstruct() {
        // Initializes EARSObject members, probably sets vtable pointer,
        // zeroes fields, etc.
    }

    // Deallocation helper (FUN_009c8eb0).
    // Takes the object pointer and frees its memory (e.g., via free or pool return).
    static void __cdecl deallocate(EARSObject* obj);
};