// FUNC_NAME: SomeClass::virtualDispatch_0x20C
void __fastcall SomeClass::virtualDispatch_0x20C(int *thisPtr)
{
    // Calls virtual function at vtable offset 0x20C (index 0x20C/4 = 0x83)
    // This is a thin dispatch wrapper that calls through the vtable
    (**(code **)(*thisPtr + 0x20c))();
    return;
}