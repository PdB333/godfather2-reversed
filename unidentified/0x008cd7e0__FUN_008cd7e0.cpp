// FUNC_NAME: SomeGameObject::constructor
// Function address: 0x008cd7e0
// Role: Constructor for a base game object (EARS framework). Sets vtable pointer, calls base initializer,
// and conditionally performs additional cleanup based on allocFlag (bit 0). Returns this pointer.

class SomeGameObject {
public:
    // vtable pointer at offset +0x00 (set to PTR_FUN_00d7c978)
    // Other fields unknown

    // Constructor-like method (returns this pointer)
    SomeGameObject* constructor(uint8 allocFlag) {
        this->vtable = reinterpret_cast<void**>(0x00d7c978); // Set vtable to class-specific table
        baseInitializer();                                    // FUN_004149b0 - base class initialization
        if (allocFlag & 1) {
            // If bit 0 is set, call cleanup/destructor function (FUN_009c8eb0)
            // Typically used to handle dynamic allocation or error cleanup
            cleanupFunction(this);
        }
        return this;
    }

    // Stub for base initializer (FUN_004149b0)
    void baseInitializer();

    // Stub for cleanup function (FUN_009c8eb0)
    void cleanupFunction(void* obj);
};