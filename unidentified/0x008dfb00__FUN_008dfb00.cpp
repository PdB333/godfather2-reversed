// FUNC_NAME: SomeClass::initialize
void __fastcall SomeClass::initialize(int this)
{
    // Call some initialization function with parameter 0
    FUN_008de5a0(0);
    
    // Call a virtual function at offset 0x28 from the vtable pointer at this+0x58
    // The vtable pointer is at this+0x58, and we call the function at vtable+0x28 (the 11th virtual function)
    // Parameter: 0x40 (64)
    (**(code **)(*(int *)(this + 0x58) + 0x28))(0x40);
    
    // Call another initialization function
    FUN_008dc610();
    
    return;
}