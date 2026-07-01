// FUNC_NAME: SomeClass::playSoundOrSomething
void __fastcall SomeClass::playSoundOrSomething(int this)
{
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;

    if (*(int *)(this + 0x60) != -1) {
        // +0x60 is some index, likely a sound or event ID
        FUN_009746e0((&DAT_00e574c8)[*(int *)(this + 0x60) * 3]);
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