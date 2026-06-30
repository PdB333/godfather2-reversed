// FUNC_NAME: ValidateAndClearHandle

char ValidateAndClearHandle(int unused, uint32* handlePtr)
{
    char isValid;
    isValid = CheckHandleValidity(handlePtr);
    if (isValid == '\0') {
        *handlePtr = 0;
        return 0;
    }
    return 1;
}