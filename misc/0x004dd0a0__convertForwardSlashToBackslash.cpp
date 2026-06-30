// FUNC_NAME: convertForwardSlashToBackslash
void __fastcall convertForwardSlashToBackslash(undefined4 param_1, int* param_2)
{
    uint uVar1 = 0;
    if (param_2[1] != 0) {
        do {
            if (*(short*)(*param_2 + uVar1 * 2) == 0x2f) { // '/'
                *(undefined2*)(*param_2 + uVar1 * 2) = 0x5c; // '\\'
            }
            uVar1 = uVar1 + 1;
        } while (uVar1 < (uint)param_2[1]);
    }
    return;
}