// FUNC_NAME: UnknownClass::someMethod
void __thiscall someMethod(int this, int param2)
{
    char cVar1;
    undefined4 local_2c;
    undefined ***local_28;
    undefined1 local_24;
    undefined **local_20;
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;
    
    cVar1 = FUN_00481620(); // likely some global check (e.g., isGameActive)
    if (cVar1 != '\0') {
        local_1c = *(undefined4 *)(this + 0x60); // +0x60: some member
        local_18 = *(undefined4 *)(this + 0x5c); // +0x5c: some member
        local_14 = *(undefined4 *)(this + 0x58); // +0x58: some member
        local_10 = *(undefined4 *)(param2 + 0x1ef8); // +0x1ef8: large offset, likely a member of param2
        local_8 = 0;
        local_4 = 0;
        local_24 = 0;
        local_28 = &local_20;
        local_20 = &PTR_LAB_00e35c24; // some global pointer table
        local_c = 0xffffffff;
        local_2c = DAT_0112ecfc; // some global data
        FUN_00408a00(&local_2c,0); // likely a function that processes a structure
    }
    return;
}