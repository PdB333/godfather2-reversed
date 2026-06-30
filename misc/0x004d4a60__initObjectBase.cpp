// FUNC_NAME: initObjectBase
undefined4* initObjectBase(undefined4* thisPtr, undefined4 param_2, undefined4 param_3)
{
    // Zero first three integer fields (offsets +0x00, +0x04, +0x08)
    *thisPtr = 0;
    thisPtr[1] = 0;
    thisPtr[2] = 0;
    // Call extended initialization with the third parameter (likely a type or data ID)
    initObjectExtended(thisPtr, param_3);
    return thisPtr;
}