// FUNC_NAME: SomeClass::SomeClass
// Address: 0x00581a50
// Role: Constructor with conditional destructor call

// Forward declarations for internal functions
void SomeClass::baseConstructor(); // FUN_00581a70
void SomeClass::destructor();      // FUN_009c8eb0

SomeClass::SomeClass(byte flags) {
    baseConstructor();
    if (flags & 1) {
        destructor();
    }
    // return this is implicit for constructors
}