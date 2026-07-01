// FUNC_NAME: SomeClass::SomeClass

// Function address: 0x0080eae0
// This function appears to be a constructor for a class in the EA EARS framework.
// It takes a byte flag (param_2) that controls behavior after base initialization.
// If the lowest bit (0x1) is set, it calls a cleanup / destructor function (likely
// operator delete or a deinit routine) on the object. This pattern may indicate
// a constructor that can optionally free allocated memory (e.g., in case of
// early failure or conditional allocation). The function returns the this pointer.

// The called functions:
// - FUN_0080ea60: likely a base class constructor or common initialization
// - FUN_00624da0: likely a destructor / cleanup function (e.g., operator delete)

__thiscall undefined4 SomeClass::SomeClass(byte flags)
{
    // Call base initialization (e.g., base class constructor or member init)
    baseInit();

    // If the lowest bit is set, perform cleanup or destruction
    if ((flags & 1) != 0) {
        callDestructorOrCleanup();
    }

    // Return the this pointer (common in custom constructors)
    return this;
}