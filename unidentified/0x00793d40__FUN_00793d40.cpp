// FUNC_NAME: UnknownClass::UnknownClass

// Constructor for class at address 0x00793d40.
// Calls a base class constructor (0x00414970) and sets the vtable pointer to 0x00d6a0c8.
// Arguments arg1 and arg2 are forwarded to the base constructor.

__thiscall UnknownClass::UnknownClass(undefined4 arg1, undefined4 arg2) {
    // Call the base class constructor (likely inherited from a common game object)
    BaseClassConstructor(arg1, arg2);
    
    // Set the vtable pointer for this object
    // Offsets assumed: +0x00 = vtable pointer
    this->vtable = &PTR_FUN_00d6a0c8;
    
    // Constructor returns this pointer (as seen in Ghidra decompilation)
    return this;
}