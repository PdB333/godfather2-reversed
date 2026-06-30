// FUNC_NAME: EARSObject::EARSObject
// Address: 0x004bf890
// Constructor for EARSObject with a flags parameter.
// If flags & 1, calls a deallocation/cleanup routine immediately after base initialization.

class EARSObject {
public:
    EARSObject(byte flags) {
        // Global/base class initialization (likely a memory pool or reference counter).
        FUN_0064f540();

        if (flags & 1) {
            // Flag bit 0 set: free or finalize the object after construction.
            FUN_009c8eb0(this);  // May be operator delete or destructor call
        }
        // Note: Implicit return of this pointer is not shown (pseudo-code behavior).
    }
};