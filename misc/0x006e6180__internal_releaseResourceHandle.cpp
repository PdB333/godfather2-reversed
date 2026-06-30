// FUNC_NAME: internal_releaseResourceHandle
void __fastcall internal_releaseResourceHandle(int *handlePtr)
{
    // If the handle (stored as integer) is non-null, release it and zero out
    if (*handlePtr != 0) {
        FUN_004daf90(handlePtr); // Release the resource associated with the handle
        *handlePtr = 0;
    }
}