// FUNC_NAME: SomeClass::setState
// Address: 0x005669f0
// Role: Sets a state to 3 and delegates to a virtual function with a hardcoded argument of 1.

// Assuming class has a vtable pointer at offset 0xc and a state variable at offset 0x10.
// The virtual function at vtable+0x50 takes three arguments: entityId, flags, and a boolean (always 1 here).

void __thiscall SomeClass::setState(uint entityId, uint flags) {
    // Call virtual function at vtable offset 0x50 with entityId, flags, and 1
    (*(void (__thiscall*)(uint, uint, int))(**(int**)(this + 0xc) + 0x50))(entityId, flags, 1);
    // Set state to 3 (likely an enum value like STATE_ACTIVE or STATE_RUNNING)
    *(int*)(this + 0x10) = 3;
}