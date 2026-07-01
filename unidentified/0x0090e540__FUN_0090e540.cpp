// FUNC_NAME: SomeClass::clearOrResetSomething
void __fastcall SomeClass::clearOrResetSomething(int this)
{
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;
    
    local_c = *(undefined4 *)(this + 0x50); // +0x50: some pointer or value
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0); // likely memset or similar initialization
    return;
}