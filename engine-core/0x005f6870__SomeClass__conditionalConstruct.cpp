// FUNC_NAME: SomeClass::conditionalConstruct
// Function address: 0x005f6870
// Role: Constructor-like function that initializes the object and optionally calls a post-init or cleanup function based on a flag.

class SomeClass {
public:
    // Constructor (placement or regular) called from conditionalConstruct
    void BaseInit();  // FUN_005f68e0

    // Post-constructor operation, possibly destructor or additional setup
    void PostInitOrCleanup();  // FUN_009c8eb0

    // Main constructor with conditional behavior
    // param_2: bit0 controls whether PostInitOrCleanup is called
    void* conditionalConstruct(byte param_2) {
        BaseInit();
        if ((param_2 & 1) != 0) {
            PostInitOrCleanup();
        }
        return this; // Return this pointer as required by pattern
    }
};