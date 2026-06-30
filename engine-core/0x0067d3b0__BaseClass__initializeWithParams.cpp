// FUNC_NAME: BaseClass::initializeWithParams
void BaseClass::initializeWithParams() {
    // Get vtable pointer from global function
    void** vtable = (void**)FUN_009c8f80(); // likely returns a singleton vtable pointer

    // Parameters: mode = 2, size = 0x10 (16), flags = 0
    int params[3] = { 2, 0x10, 0 };

    // Call first virtual function (index 0) with this and parameter array
    // The function likely configures some internal state based on given params
    ((void (__thiscall*)(void*, int*))(*vtable))(this, params);
}