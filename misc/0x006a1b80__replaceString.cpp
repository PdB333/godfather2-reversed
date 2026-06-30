// FUNC_NAME: replaceString
// Address: 0x006a1b80
// Replaces all occurrences of substring 'from' in 'str' with substring 'to'.
// Returns a newly allocated string (caller must free with free() or equivalent).
// Uses CRT functions: strstr, malloc, memcpy, strcpy_s.

char* replaceString(char* str, char* from, char* to)
{
    char* pFrom;       // pointer for scanning source
    char* pStr;        // pointer for scanning str
    char* pTo;         // pointer for scanning to
    size_t fromLen;    // length of from string
    size_t toLen;      // length of to string
    size_t chunkSize;  // size of chunk before an occurrence
    int count;         // number of occurrences found
    char* result;      // output buffer
    char* pResult;     // pointer into result for building
    char* found;       // result of strstr
    
    // Calculate lengths
    pStr = str;
    while (*pStr != '\0') pStr++;
    pFrom = from;
    while (*pFrom != '\0') pFrom++;
    pTo = to;
    while (*pTo != '\0') pTo++;
    
    // toLen = length of replacement, fromLen = length of search
    toLen = (size_t)(pTo - to);
    fromLen = (size_t)(pFrom - from);
    
    // Count occurrences
    count = 0;
    found = strstr(str, from);
    while (found != NULL)
    {
        count++;
        found = strstr(found + fromLen, from);
    }
    
    // Allocate memory: original length + (toLen - fromLen) * count + 1
    size_t totalLen = (size_t)(pStr - str) + (toLen - fromLen) * count + 1;
    result = (char*)malloc(totalLen);
    if (result == NULL) return NULL;
    
    // Build result string
    pResult = result;
    found = strstr(str, from);
    while (found != NULL)
    {
        chunkSize = (size_t)(found - str);
        memcpy(pResult, str, chunkSize);
        pResult += chunkSize;
        memcpy(pResult, to, toLen);
        pResult += toLen;
        str = found + fromLen; // advance past this occurrence
        found = strstr(str, from);
    }
    // Copy remaining part after last occurrence
    strcpy_s(pResult, totalLen - (size_t)(pResult - result), str);
    
    return result;
}