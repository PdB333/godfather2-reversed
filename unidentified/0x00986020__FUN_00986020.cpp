// FUNC_NAME: SomeClass::playSoundOrSomething
void __fastcall SomeClass::playSoundOrSomething(int this)
{
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;

    if (*(int *)(this + 100) != -1) {
        // +0x64: some index into a global sound/event table
        FUN_00985f90((&DAT_00e57600)[*(int *)(this + 100) * 3]);
        local_c = DAT_01130448;
        local_8 = 0;
        local_4 = 0;
        FUN_00408a00(&local_c, 0);
        return;
    }
    local_8 = 0;
    local_4 = 0;
    local_c = DAT_011301f8;
    FUN_00408a00(&local_c, 0);
    return;
}