// FUNC_NAME: UnknownClass::constructor
// Address: 0x00895820
// Role: Constructor for an unknown class. Calls base constructor and conditionally initializes memory.

// Note: FUN_00895740 is likely a base class constructor or initializer.
// FUN_0043b960 appears to be a memory clearing function (memset-like) with size 0x78 (120 bytes).
// The param_2 flag (bit 0) controls whether the memory clearing is performed.

class UnknownClass {
public:
    // Constructor
    // param_2: flags (bit 0 = clear memory)
    __thiscall UnknownClass(byte param_2) {
        // Call base class constructor or initializer
        FUN_00895740();

        // If bit 0 of param_2 is set, clear the object's memory (size 0x78)
        if ((param_2 & 1) != 0) {
            FUN_0043b960(this, 0x78); // Likely memset(this, 0, 0x78)
        }
    }
};