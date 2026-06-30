// FUNC_NAME: SomeManager::someCheckAndReturn
int SomeManager::someCheckAndReturn(int param_1)
{
    int iVar1;
    int uVar2;

    iVar1 = FUN_006b0ee0(param_1);
    if (iVar1 != 0) {
        uVar2 = FUN_006b6680();
        return uVar2;
    }
    return 0;
}