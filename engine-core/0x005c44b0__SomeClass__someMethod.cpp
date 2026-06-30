// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(int param_1, int param_2)
{
    char result;
    
    result = FUN_005c43d0(param_1);
    if (result == '\0') {
        // Call virtual function through vtable at offset +4
        (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(param_1, param_2);
    }
    return;
}