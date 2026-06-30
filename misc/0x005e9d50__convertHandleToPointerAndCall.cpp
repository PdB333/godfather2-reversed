// FUNC_NAME: convertHandleToPointerAndCall
void __fastcall convertHandleToPointerAndCall(uint handle)
{
    uint handleCopy;
    uint* pHandleCopy = &handleCopy;
    handleCopy = handle;
    uint result = convertHandleToAddress(handle, &handleCopy);
    processAddress(result, pHandleCopy);
}