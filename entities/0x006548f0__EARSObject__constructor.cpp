// FUNC_NAME: EARSObject::constructor
// Function address: 0x006548f0
// This function acts as a constructor for a class in the EARS engine.
// It calls a base class constructor (0x0065e330) and optionally performs
// additional initialization (0x009c8eb0) if the low bit of the flags parameter is set.
// The result is the constructed object pointer.

class EARSObject {
public:
    // Constructor with optional initialization flag
    EARSObject(byte flags);
};

EARSObject::EARSObject(byte flags) {
    // Call base class constructor
    // Likely initializes basic object fields (e.g., vtable pointer, reference count)
    baseClassConstructor(); // 0x0065e330

    // If the lowest bit of flags is set, perform extra initialization
    if (flags & 1) {
        // This might set up derived-specific vtable or allocate resources
        extraInitialization(this); // 0x009c8eb0
    }
}