// FUNC_NAME: ResourceManager::loadResource
undefined4 __thiscall ResourceManager::loadResource(ResourceManager *this, int resourceId, int *outResult)
{
    int localArray1[3]; // stack buffer for intermediate data
    int *callbackPtr;   // function pointer? Actually code*
    int localArray2[3]; // another buffer
    int *returnCallback; // code*

    localArray1[0] = 0;
    localArray1[1] = 0;
    localArray1[2] = 0;
    callbackPtr = nullptr;

    bool isValid = FUN_00699b70(resourceId, localArray1); // check resource validity
    if (!isValid) {
        // global range check (DAT_00e506ac might be current slot index, DAT_01129f90/8c are bounds)
        if ((-1 < DAT_00e506ac) && (DAT_00e506ac < (DAT_01129f90 - DAT_01129f8c) >> 2)) {
            FUN_004d3bc0(resourceId); // maybe load from disk
            FUN_0069b380(localArray2); // fill localArray2 with data
            FUN_004d3e20(outResult);   // finalize
            if (localArray2[0] != 0) {
                // call a function pointer stored in returnCallback (should be set by FUN_0069b380, but decompilation missing)
                (*returnCallback)(localArray2[0]);
            }
        }
        FUN_004d3b50(outResult);
    } else {
        FUN_004d3b50(localArray1);
    }
    if (localArray1[0] != 0) {
        (*callbackPtr)(localArray1[0]);
    }
    return (undefined4)this;
}