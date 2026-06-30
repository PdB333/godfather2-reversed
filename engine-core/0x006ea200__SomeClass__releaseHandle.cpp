// FUNC_NAME: SomeClass::releaseHandle
void __thiscall SomeClass::releaseHandle(void)
{
    int handle = *(int *)(this + 0x70); // offset +0x70: handle or pointer to managed resource
    int unused1 = 0;                   // cleared but unused
    int unused2 = 0;                   // cleared but unused
    FUN_00408a00(&handle, 0);          // release or stop with handle and flags=0
    return;
}