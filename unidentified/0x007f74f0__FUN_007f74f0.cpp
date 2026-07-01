// FUNC_NAME: SomeClass::resetSomeFlag
void __fastcall SomeClass::resetSomeFlag(int this)
{
    *(undefined1 *)(this + 0xa30) = 0; // +0xa30: some boolean flag (set to false/0)
    return;
}