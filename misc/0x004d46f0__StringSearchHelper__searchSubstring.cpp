// FUNC_NAME: StringSearchHelper::searchSubstring
void __thiscall StringSearchHelper::searchSubstring(char **this, char *searchStr, char *externalStr)
{
    // this points to object with first member being a char* (offset +0x00): m_pBuffer
    // searchStr: substring to look for; externalStr: optional external string to search in
    // If externalStr is provided, search in it; otherwise search in m_pBuffer.
    // Note: The return value of _strstr is discarded, suggesting this function is for side effects
    // (e.g., logging, breakpoints) or the decompiler missed actual usage.
    if ((searchStr != (char *)0x0) && (*searchStr != '\0')) 
    {
        if (externalStr != (char *)0x0) 
        {
            _strstr(externalStr, searchStr);
            return;
        }
        if ((char *)*this != (char *)0x0) 
        {
            _strstr((char *)*this, searchStr);
        }
    }
    return;
}