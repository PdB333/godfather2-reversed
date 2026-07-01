// FUNC_NAME: SomeClass::constructor
// Function address: 0x00916bc0
// Role: Constructor for an object of size 0xF0 (240 bytes). Allocates memory, initializes fields, and calls engine registration functions.

class SomeClass {
public:
    // +0x00: vtable pointer (implicit)
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: type ID (set to 0xD = 13)
    // +0x10: unknown
    // +0x14: function pointer (set to FUN_00982b30, likely a virtual method or callback)
    // ... rest of 0xF0 bytes

    // Constructor: takes a parameter (likely parent or context ID)
    void __thiscall constructor(int param_1) {
        int objPtr;

        // Allocate 0xF0 bytes (size of this object)
        objPtr = FUN_009c8e50(0xF0);  // operator new or custom allocator
        if (objPtr == 0) {
            objPtr = 0;  // allocation failed, set to null
        } else {
            // Call initialization function on the allocated memory (likely a base constructor or initializer)
            objPtr = FUN_00982280(0);  // returns pointer to initialized object (maybe this)
        }

        // Register with engine subsystems
        FUN_00981f10(2, 3);  // e.g., register object type, version
        FUN_00981eb0(param_1);  // set parent or attach to context

        // Set type ID to 0xD (13)
        *(int*)(objPtr + 0x0C) = 0xD;

        // Set a flag or enable something
        FUN_00982400(1);  // e.g., set active flag

        // Set function pointer at offset 0x14 to a specific handler
        *(void (__thiscall**)(void))(objPtr + 0x14) = &FUN_00982b30;  // likely a virtual function

        // Finalize initialization
        FUN_00982e10();  // e.g., notify engine, complete setup
    }
};