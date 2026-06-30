// FUNC_NAME: SomeClass::callVirtualMethod
void __fastcall SomeClass::callVirtualMethod(int thisPtr)
{
    int *vtablePtr;
    
    vtablePtr = (int *)FUN_006bca80(thisPtr + 0x60); // +0x60: offset to some member pointer
    if (vtablePtr != (int *)0x0) {
        (**(code **)(*vtablePtr + 0x20))(thisPtr); // Call virtual function at vtable offset 0x20
    }
    return;
}