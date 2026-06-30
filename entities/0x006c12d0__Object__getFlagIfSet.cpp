// FUNC_NAME: Object::getFlagIfSet
// Function at 0x006c12d0: returns the given flag if a virtual check passes, else 0.
// The virtual function at vtable+0x10 performs the actual test, returning a char (0/fail or non-zero/pass).
uint __thiscall Object::getFlagIfSet(uint flag) {
    uint local_4 = 0; // output parameter for virtual call

    // Call the virtual test function; returns char indicating success.
    // vtable offset 0x10 corresponds to the third virtual method (after destructor and default).
    char result = (*(char (__thiscall**)(uint, uint*))(*(uintptr_t*)this + 0x10))(flag, &local_4);

    // If result is non-zero, mask with flag (return flag), else return 0.
    return -(uint)(result != 0) & flag;
}