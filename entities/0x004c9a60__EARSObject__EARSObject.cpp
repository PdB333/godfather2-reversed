// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x004c9a60
// Role: Constructor for an EARSObject. Calls the base class initializer (FUN_004ca180) and returns the this pointer.
// This is typical for EA EARS engine objects, where constructors chain to base initialization.
// Note: The decompilation shows __fastcall with one parameter, but this is actually __thiscall – this pointer in ECX.
void EARSObject::EARSObject() {
    // Base class initialization (likely sets vtable pointer or initializes base data)
    // The target function (FUN_004ca180) is a non-virtual base constructor or initializer.
    FUN_004ca180();
    // No further initialization in this derived constructor.
    // The implicit this pointer is returned automatically by the compiler.
}