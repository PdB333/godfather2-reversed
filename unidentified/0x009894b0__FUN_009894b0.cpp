// FUNC_NAME: SomeClass::resetSomeState
void __fastcall SomeClass::resetSomeState(int thisPtr)
{
    FUN_009386b0();
    FUN_00934f50(*(char *)(thisPtr + 0x50));
    *(char *)(thisPtr + 0x50) = 0;
    *(int *)(thisPtr + 0x54) = 0;
    return;
}