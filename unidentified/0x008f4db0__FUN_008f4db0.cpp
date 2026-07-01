// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int this, undefined4 param_2)
{
    // Call to FUN_008f1e20 with parameters: 7, value at (this - 0x2060), value at (this - 0x205c)
    FUN_008f1e20(7, *(undefined4 *)(this + -0x2060), *(undefined4 *)(this + -0x205c));
    
    // Store param_2 at offset (this - 0x2078)
    *(undefined4 *)(this + -0x2078) = param_2;
    
    // Call to FUN_008f4650
    FUN_008f4650();
    
    return;
}