// FUNC_NAME: SomeClass::constructor
// Address: 0x0083fc80
// This is a constructor that initializes an object with a vtable and two function pointers.
// Offsets:
//   +0x00: vtable pointer (PTR_FUN_00d744f8)
//   +0x3C (0xF*4): pointer to PTR_LAB_00d744e8
//   +0x48 (0x12*4): pointer to PTR_LAB_00d744e4
// The constructor calls a base class constructor (FUN_0083f8e0) and then allocates/internal init via FUN_0083f970(0x1A).

undefined4* __thiscall SomeClass::constructor(undefined4* this, undefined4 arg)
{
    // Call base class constructor with the provided argument
    FUN_0083f8e0(arg);
    
    // Set vtable pointer to the class's virtual function table
    *this = &PTR_FUN_00d744f8;
    
    // Store a pointer at offset 0x3C (15 indices * 4 bytes) - likely a callback or interface
    this[0xF] = &PTR_LAB_00d744e8;
    
    // Store another pointer at offset 0x48 (18 indices * 4 bytes) - likely another callback
    this[0x12] = &PTR_LAB_00d744e4;
    
    // Perform additional initialization (possibly allocation of an internal buffer or registration)
    FUN_0083f970(0x1A);
    
    return this;
}