// FUNC_NAME: caseInsensitiveWideSubstringSearch
// Address: 0x004dc860
// Purpose: Scans a null-terminated wide string (ushort*) for a null-terminated pattern, case-insensitively for ASCII letters A-Z.
// Returns (void): early exit when pattern is found, otherwise falls through to end.
void __fastcall caseInsensitiveWideSubstringSearch(ushort *pattern, ushort *str) {
    // Guard: if input string is empty, nothing to search
    if (*str == 0) {
        return;
    }

    ushort *scanPos = str;          // current position in the searched string
    while (*scanPos != 0) {
        ushort *pPattern = pattern; // restart pattern from beginning
        ushort *pSub = scanPos;     // substring start at current scan position

        // Compare substring against pattern character by character
        while (*pPattern != 0) {
            ushort chSub = *pSub;
            ushort chPat = *pPattern;

            // Case-insensitive conversion for uppercase A-Z (0x41-0x5A → 0x61-0x7A)
            if (chSub >= 'A' && chSub <= 'Z') chSub += 0x20;
            if (chPat >= 'A' && chPat <= 'Z') chPat += 0x20;

            if (chSub != chPat) {
                break; // mismatch, move to next position in str
            }

            pSub++;
            pPattern++;
        }

        // If all pattern characters matched (pattern reached end), we found a match
        if (*pPattern == 0) {
            return; // early success return
        }

        scanPos++; // advance one position in the searched string
    }
    // Not found – fall through to implicit return
}