// FUNC_NAME: SomeClass::someMethod
void __fastcall SomeClass::someMethod(int thisPtr)
{
    // Call sub-function on offset +0x18 (likely a member object or sub-component)
    FUN_008ae870(thisPtr + 0x18);
    
    // Call a function pointer stored at offset +0x8, passing values from +0x10 and +0x14
    // This appears to be a virtual method call or callback invocation
    (**(code **)(thisPtr + 8))(*(undefined4 *)(thisPtr + 0x10), *(undefined1 *)(thisPtr + 0x14));
    
    return;
}