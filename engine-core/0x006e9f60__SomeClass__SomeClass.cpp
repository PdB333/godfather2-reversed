// FUNC_NAME: SomeClass::SomeClass
// 0x006e9f60 - Constructor for SomeClass (object size 0xAC = 172 bytes)
// __thiscall: this is passed in ECX, param_2 is a byte flag (bit0 controls additional initialization)

class SomeClass {
public:
    // Constructor with optional initialization flag
    SomeClass(byte allocFlag);
};

// Base class constructor at 0x006e9e90
void SomeBaseClassConstructor(void); // Forward declaration

// Internal memory initialization function at 0x0043b960
void initializeMemory(void* ptr, unsigned int size);

SomeClass::SomeClass(byte allocFlag) {
    // Call base class constructor (base class at offset 0x00, likely EARSObject or similar)
    SomeBaseClassConstructor();

    // If the low bit of allocFlag is set, perform additional memory setup
    if ((allocFlag & 1) != 0) {
        initializeMemory(this, 0xAC);  // Size of this object (172 bytes)
    }
}