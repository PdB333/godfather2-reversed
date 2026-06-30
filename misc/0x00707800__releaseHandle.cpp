// FUNC_NAME: releaseHandle
void __fastcall releaseHandle(int* pHandle) {
    // If the handle is non-zero, release the resource and clear it
    if (*pHandle != 0) {
        FUN_004daf90(pHandle); // Internal release/free function
        *pHandle = 0;
    }
}