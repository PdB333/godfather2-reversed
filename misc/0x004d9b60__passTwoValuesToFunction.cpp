// FUNC_NAME: passTwoValuesToFunction
int __thiscall passTwoValuesToFunction(int* thisPtr, int param)
{
    // Call external function with param, thisPtr[0], thisPtr[1]
    FUN_004d9080(param, *thisPtr, *(thisPtr + 1));
    return param;
}