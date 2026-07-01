// FUNC_NAME: constructorWithFlag
// Address: 0x0090b460
// The function is a __thiscall member function that initializes an object.
// It unconditionally calls a base initializer (FUN_0090af60, likely vtable or default constructor).
// If the flag's lowest bit is set, it calls an extra initialization/cleanup routine (FUN_009c8eb0) on this object.
// Returns the this pointer as an unsigned 32-bit integer (common for constructors that return self).

uint32_t __thiscall constructorWithFlag(uint8_t flags) {
    // Base class initialization – no explicit arguments, probably sets up vtable or calls default constructor
    baseInitializer(); // FUN_0090af60

    // Conditional extra step: if bit0 of 'flags' is set, perform additional setup/cleanup
    if (flags & 1) {
        conditionalExtraInit(this); // FUN_009c8eb0
    }

    // Return the 'this' pointer (cast to uint32_t)
    return reinterpret_cast<uint32_t>(this);
}