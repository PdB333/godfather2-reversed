// FUNC_NAME: SomeClass::callVirtualMethodAt0x270
void __fastcall SomeClass::callVirtualMethodAt0x270(int thisPtr)
{
    // Dereference the vtable pointer at +0x58 from this object
    // Then call the virtual function at offset 0x270 in the vtable
    (**(code **)(**(int **)(thisPtr + 0x58) + 0x270))();
    return;
}