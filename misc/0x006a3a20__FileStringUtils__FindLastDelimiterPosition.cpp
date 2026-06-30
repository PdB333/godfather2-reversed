// FUNC_NAME: FileStringUtils::FindLastDelimiterPosition
// Function at 0x006a3a20: Finds the last occurrence of any delimiter from a set (DAT_00d5d624) in a length-prefixed wide string.
// If the delimiter is a backslash (0x5c), additional checks ensure it's not escaped by an odd number of preceding backslashes.
// Returns the index (in shorts from the beginning of the string structure, including the length prefix)
// of the found delimiter, or -1 if none found.
// Input: param_1 = pointer to a short-length prefixed wide string (first short = character count, then characters)
// The string is assumed to be non-null and valid.

#include <wchar.h>

// Helper function (FUN_006a37f0): Finds the next occurrence of any character in the set pointed by pSet,
// starting from the given pointer pStr. Returns the offset (in shorts) from pStr to the found character,
// or -1 if not found.
extern int FindNextCharInSet(const short* pStr, const short* pSet);

// Global delimiter set (likely L"\\/" or L"\\")
extern const short* g_pDelimiterSet;

int FindLastDelimiterPosition(const short* pString)
{
    // pString[0] = length, characters start at pString[1]
    int index = 1; // start past the length prefix

    while (true)
    {
        // Find next delimiter from current position
        int offset = FindNextCharInSet(pString + index, g_pDelimiterSet);
        if (offset < 0)
        {
            return -1; // no more delimiters
        }
        index += offset; // index now points to the found delimiter

        // Check if the character immediately before the found one is a backslash (0x5c)
        if (pString[index - 1] != L'\\')
        {
            // Not a backslash -> this delimiter is terminal (e.g., forward slash)
            break;
        }

        // It is a backslash – check if it's part of an escape sequence (double backslash)
        bool isEvenEscapeCount = true;               // bVar1
        const short* pCursor = &pString[index - 1];  // point to the found backslash itself (psVar3)

        do
        {
            isEvenEscapeCount = !isEvenEscapeCount;  // toggle for each backslash encountered
            pCursor--;                               // move backwards
        } while (*pCursor == L'\\');                 // continue while preceding char is also a backslash

        if (isEvenEscapeCount)
        {
            // Even number of consecutive backslashes (including this one) -> this backslash is part of an escaped literal
            // (e.g., "\\\\" produces two literal backslashes, second is the literal)
            // Since we want unescaped backslashes (separators), we accept only odd counts.
            // But in this code, isEvenEscapeCount being true causes a return => it treats even as unescaped.
            // This matches the decompiled logic.
            return index;
        }
        // Otherwise, this backslash is considered part of an escape sequence – skip it and continue.
        index++;
        if (index == 0) // overflow check (unlikely)
        {
            return -1;
        }
    }

    return index;
}