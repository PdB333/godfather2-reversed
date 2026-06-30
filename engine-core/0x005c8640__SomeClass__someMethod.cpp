// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(int param_1)
{
    int *piVar1;
    
    piVar1 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_FUN_0112615c;
    *piVar1 = *piVar1 + 4;
    FUN_005cbe70(CONCAT44(8,in_EAX),4,param_1);
    return;
}