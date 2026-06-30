// FUNC_NAME: SomeClass::resetState

void __thiscall SomeClass::resetState(int *this)
{
    // Set field at offset 0x578 (0x15e * 4) to 0
    this[0x15e] = 0;
    
    // Release resource at offset 0x574 (0x15d * 4)
    FUN_009c8f10(this[0x15d]);  // likely a release/free function
    
    // Clear pointer and additional field
    this[0x15d] = 0;
    this[0x15f] = 0;
    
    // Call virtual function at vtable offset 0xd0 (index 52)
    // This might be a reset or cleanup virtual method
    (*(void (**)(void))(*this + 0xd0))();
}