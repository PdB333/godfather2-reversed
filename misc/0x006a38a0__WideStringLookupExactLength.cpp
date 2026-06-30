// FUNC_NAME: WideStringLookupExactLength
// Function address: 0x006a38a0
// Searches an array of wide strings for a string of exact length compareLength.
// Returns a pointer to the matching string in the array, or nullptr if not found.
wchar_t* WideStringLookupExactLength(wchar_t** stringArray, int arrayCount, wchar_t* searchString, size_t compareLength)
{
    int iVar1;
    int iVar2;
    
    iVar2 = 0;
    if (arrayCount > 0) {
        do {
            iVar1 = _wcsncmp(searchString, stringArray[iVar2], compareLength);
            if (iVar1 == 0) {
                // Check that the target string is exactly compareLength characters long (null terminator at that position)
                if (*(short*)(stringArray[iVar2] + (compareLength * 2)) == 0) {
                    return stringArray[iVar2];
                }
            }
            iVar2 = iVar2 + 1;
        } while (iVar2 < arrayCount);
    }
    return nullptr;
}