// FUNC_NAME: createAllocationWrapper
int __cdecl createAllocationWrapper(void* context, int creationId)
{
    int initParams[3];
    initParams[0] = 2;
    initParams[1] = 0x10;
    initParams[2] = 0;
    int* result = FUN_0043b980(0x60, initParams, creationId);
    if (result != 0) {
        return FUN_00906040(context);
    }
    return 0;
}