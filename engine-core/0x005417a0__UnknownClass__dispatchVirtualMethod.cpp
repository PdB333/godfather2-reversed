// FUNC_NAME: UnknownClass::dispatchVirtualMethod
void __thiscall UnknownClass::dispatchVirtualMethod(uint param2, uint param3) {
    // Call common pre-dispatch function (likely error checking or logging)
    FUN_009f2000();
    
    // Dispatch to virtual method at vtable offset 0x58 from the interface pointer stored at this+0xd0.
    // The virtual function takes two unsigned int parameters and uses the same 'this' pointer.
    // This is typical for delegated calls in the EA EARS engine.
    void (__thiscall *virtualMethod)(uint, uint) = 
        (void (__thiscall *)(uint, uint))(*(int *)(*(int *)(this + 0xd0) + 0x58));
    virtualMethod(param2, param3);
}