// FUNC_NAME: SomeClass::setSomeFlag
void __fastcall FUN_00931780(int param_1)
{
    char flag = FUN_008f3c70(); // Get some flag value
    *(char *)(param_1 + 0x70) = flag; // +0x70: some flag field
    return;
}