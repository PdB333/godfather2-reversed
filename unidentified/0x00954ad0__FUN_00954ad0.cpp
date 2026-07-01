// FUNC_NAME: unknown::delegateTo_00849050
void FUN_00954ad0(undefined4 param_1, undefined4 param_2)
{
    // This function simply forwards param_2 to another function at 0x849050.
    // param_1 is unused, suggesting this might be a thunk or a wrapper.
    // The caller at 0x976990 likely passes a context object as param_1 (this pointer)
    // and the actual argument as param_2.
    FUN_00849050(param_2);
    return;
}