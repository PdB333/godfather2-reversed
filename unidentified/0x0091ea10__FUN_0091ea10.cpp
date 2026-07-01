// FUNC_NAME: SomeClass::configure
void SomeClass::configure(int this) {
    // Get vtable pointer from a global manager (likely a system singleton)
    int** vtablePtr = (int**)FUN_009c8f80();
    // Configure parameters: mode=2, type=0x10, flags=0
    int params[3] = {2, 0x10, 0};
    // Call virtual method on this object via the vtable
    ((void (__thiscall*)(int, int*))(*vtablePtr))(this, params);
}