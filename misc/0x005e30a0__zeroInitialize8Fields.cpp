// FUNC_NAME: zeroInitialize8Fields
void __fastcall zeroInitialize8Fields(int* param_1)
{
    param_1[0] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[7] = 0; // note: indices 7 and 6 are swapped in original binary
    param_1[6] = 0;
}