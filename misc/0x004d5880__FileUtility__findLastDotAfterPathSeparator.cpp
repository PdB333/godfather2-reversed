// FUNC_NAME: FileUtility::findLastDotAfterPathSeparator
char* __fastcall findLastDotAfterPathSeparator(int unused, struct StringBuffer* buffer)
// 004d5880 - Finds the last '.' character that appears after the last path separator ('/' or '\\') in a string.
// If no dot is found after the last separator, returns NULL.
// Note: This function identifies only the first dot after a separator; if multiple dots exist in the filename,
// it returns the first one, not the last (e.g., "file.backup.txt" returns pointer to '.' in "backup").
// This is likely used for simple extension extraction assuming filenames have a single dot.
// The unused parameter may be a discarded 'this' pointer or a constant.
{
    char* pCur = buffer->data;                     // start of string
    char* pDot = NULL;                             // candidate dot pointer
    char* pEnd = buffer->data + buffer->length;    // end of string

    if (pCur == NULL)
        return NULL;

    for (; pCur < pEnd; ++pCur)
    {
        if (pDot == NULL)
        {
            if (*pCur == '.')
                pDot = pCur;  // first dot after last separator (or start)
        }
        else
        {
            // path separator resets the search: next dot becomes candidate
            if (*pCur == '/' || *pCur == '\\')
                pDot = NULL;
        }
    }

    // pDot points to the first dot after the last path separator, if any.
    return pDot;
}