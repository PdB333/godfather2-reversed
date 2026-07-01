// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(int param_2, char param_3)
{
    int iVar1;
    
    iVar1 = *(int *)(param_2 + 0x10);
    FUN_009823b0();
    FUN_009c8eb0(param_2);
    if (param_3 != '\0') {
        *(undefined4 *)(iVar1 + 0x18) = 2;
    }
    FUN_008f2dd0();
    return;
}