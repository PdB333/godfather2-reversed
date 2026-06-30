// FUNC_NAME: SomeClass::constructor
// Address: 0x00559b50
// Role: Initializes a game object with a vtable pointer and calls base constructor.
// Calls base constructor at 0x00557e20, then sets up vtable from global PTR_LAB_00dcf98c.
void SomeClass::constructor(undefined4 arg1, undefined4 arg2, undefined4 arg3) {
    // base constructor
    BaseClass::constructor(); // FUN_00557e20

    // Store third argument (unused later)
    undefined4 savedArg = arg3;

    // Zero flag
    char flag = 0;

    // Point to vtable for this class
    undefined** vtablePtr = &PTR_LAB_00dcf98c;

    // Initialize object with vtable and parameters
    // FUN_00c0a110(arg1, this, arg2, &vtablePtr);
    // This likely sets the object's vtable pointer and stores arguments.
    FUN_00c0a110(arg2, this, arg1, &vtablePtr); // param order: (arg1? this, arg2, &vtable)
}