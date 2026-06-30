// FUNC_NAME: SomeClass::wrapperMethod
void SomeClass::wrapperMethod(int param1, int param2, int param3, int param4, int param5)
{
    // Calls the actual implementation at 0x005c01d0 with a hardcoded 1 as the third argument
    FUN_005c01d0(param1, param2, 1, param3, param4, param5);
    return;
}