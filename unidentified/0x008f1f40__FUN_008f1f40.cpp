// FUNC_NAME: SomeClass::releaseOrDestroy
void __fastcall SomeClass::releaseOrDestroy(int this)
{
    // Call virtual function at offset +0x2c (likely a release/cleanup method)
    (**(code **)(**(int **)(this + 0x2c)))(0);
    
    // Call virtual function at offset +0x28 (vtable+4) with argument 0x3c (60)
    // This looks like a memory deallocation or size-based free
    (**(code **)(**(int **)(this + 0x28) + 4))(*(undefined4 *)(this + 0x2c), 0x3c);
    
    // Clear the pointer at +0x2c
    *(undefined4 *)(this + 0x2c) = 0;
}