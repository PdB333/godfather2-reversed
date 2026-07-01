// FUNC_NAME: findWideStringInRange
// Address: 0x0098b000
// Searches for a wide string entry in a range of entries (begin inclusive, end exclusive)
// Each entry consists of: +0x00 pointer to wchar_t string, +0x04 length in characters (or bytes? treated as count)
// Returns immediately if a matching entry is found, otherwise returns after scanning all.
// Used for duplicate detection or validation in string tables.

void findWideStringInRange(int *begin, int *end, int *entry)
{
    int *current = begin;
    
    // Scan from begin to end (exclusive)
    if (current != end) {
        do {
            // Compare the length field of the current entry with the target entry
            if (current[1] == entry[1]) {
                // If length is zero, both strings are empty -> match found
                if (current[1] == 0) {
                    return;
                }
                
                // Compare the wide strings pointed to by the first word of each entry
                wchar_t *srcStr = (wchar_t *)*current;
                wchar_t *tgtStr = (wchar_t *)*entry;
                int compareResult = 0;
                
                do {
                    wchar_t srcCh = *srcStr;
                    wchar_t tgtCh = *tgtStr;
                    
                    if (srcCh != tgtCh) {
                        compareResult = (srcCh < tgtCh) ? -1 : 1;
                        break;
                    }
                    if (srcCh == 0) {
                        compareResult = 0;
                        break;
                    }
                    
                    srcStr++;
                    tgtStr++;
                } while (true);
                
                if (compareResult == 0) {
                    return; // Match found
                }
            }
            
            current++;
        } while (current != end);
    }
    
    return; // No match found
}