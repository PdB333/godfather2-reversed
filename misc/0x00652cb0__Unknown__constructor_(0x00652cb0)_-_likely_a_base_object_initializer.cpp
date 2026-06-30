// FUNC_NAME: Unknown::constructor (0x00652cb0) - likely a base object initializer
// Calls base constructor at 0x00652ea0, conditionally performs additional init (0x009c8eb0)
// when 'flags' bit 0 is set (e.g., allocation or derived class setup)

class Unknown; // forward declaration

__thiscall Unknown::Unknown(byte flags)
{
    // Call base class constructor (e.g., EARS object init)
    baseConstructor(); // FUN_00652ea0

    // Optional extra initialization (e.g., allocate internal buffer or register)
    if (flags & 1) {
        additionalInit(); // FUN_009c8eb0
    }

    return this;
}