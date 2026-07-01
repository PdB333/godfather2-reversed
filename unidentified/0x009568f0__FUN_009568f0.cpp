// FUNC_NAME: SomeClass::callVirtualMethod
void __fastcall callVirtualMethod(int thisPtr)
{
    // Dereference: thisPtr + 0x54 + (thisPtr + 0x6c) * 4 points to a vtable pointer
    // Then call the method at vtable offset 0x94 (i.e., the 37th virtual function, 0x94 / 4 = 37)
    // The vtable is obtained from the object at that computed address
    (**(code **)(**(int **)(thisPtr + 0x54 + *(int *)(thisPtr + 0x6c) * 4) + 0x94))();
    return;
}