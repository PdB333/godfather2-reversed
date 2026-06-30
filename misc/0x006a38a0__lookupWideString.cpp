// FUNC_NAME: lookupWideString
// Function address: 0x006a38a0
// Scans an array of wide string pointers for an exact match (up to compareLength characters,
// and the string must be exactly that length). Returns the matching string pointer or 0.
wchar_t* lookupWideString(const wchar_t** tablePtr, int tableSize, const wchar_t* searchString, size_t compareLength)
{
    int resultPtr; // Will hold pointer cast to int
    int i = 0;
    if (0 < tableSize) {
        do {
            resultPtr = _wcsncmp(searchString, tablePtr[i], compareLength);
            if (resultPtr == 0) {
                resultPtr = (int)tablePtr[i];
                // Check if the character at compareLength index is null (i.e., string length == compareLength)
                if (*(short*)(resultPtr + compareLength * 2) == 0) {
                    return (wchar_t*)resultPtr;
                }
            }
            i++;
        } while (i < tableSize);
    }
    return 0;
}