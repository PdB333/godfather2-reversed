// FUNC_NAME: SomeGameObject::resetState
void __fastcall SomeGameObject::resetState(int this)
{
    // Clear bit 0 of flags at +0x84
    *(unsigned short *)(this + 0x84) &= 0xFFFE;

    // Check pointer at +0xD8; if null, call reset helpers
    if (*(int *)(this + 0xD8) == 0) {
        FUN_00837020();
        FUN_008370e0();
    }

    // Temporary structure for compare/assign calls
    struct TempStruct {
        int a;
        int b;
        int c;
        char d;
    };

    TempStruct temp;
    temp.b = DAT_00d58cbc;
    temp.a = DAT_00d58cbc;
    temp.c = DAT_0112dbe0;
    temp.d = 0;
    FUN_00408a00(&temp.c, 0); // Compare and set (address of third element)

    // Set bit 2 of flags
    *(unsigned short *)(this + 0x84) |= 4;

    // Reuse temp with different data
    temp.c = DAT_0112dbd8;
    temp.d = 0;
    FUN_00408a00(&temp.c, 0);

    // Copy values to this+0xB4 and this+0xB0
    int uVar1 = DAT_00d73c70;
    *(int *)(this + 0xB4) = *(int *)(this + 0xAC);
    *(int *)(this + 0xB0) = uVar1;
}