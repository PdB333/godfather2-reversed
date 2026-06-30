// FUNC_NAME: StringPool::removeLastString
// Address: 0x004d5310
// Role: Removes the last string from a string pool buffer if its length matches the given string's length.
// The pool stores strings consecutively in a buffer. This function walks through the buffer,
// finds the last string, and if its end exactly matches the pool's used region, zeroes its first byte
// and decrements the used size.

// This is a __thiscall method operating on a StringPool struct.
// StringPool layout:
//   +0x00 char* m_pBuffer;   // start of the string buffer
//   +0x04 int   m_usedSize;   // number of bytes used (offset to next free slot)

// Helper function: given a pointer into the pool, returns the start of the next string (skipping over the null terminator).
// Implemented as a separate function (FUN_004d4e20) in the original binary.
extern char* __cdecl getNextString(char* ptr);

class StringPool {
public:
    char* m_pBuffer;   // +0x00
    int   m_usedSize;  // +0x04

    // Removes the last string if its length equals strlen(strToMatch).
    // Returns this pointer.
    StringPool* removeLastString(char* strToMatch) {
        if (m_pBuffer == nullptr) {
            return this;
        }

        char* current = getNextString(m_pBuffer);
        if (current == nullptr) {
            return this;
        }

        // Compute length of input string (excluding null terminator)
        int strLen = 0;
        char* strPtr = strToMatch;
        while (*strPtr != '\0') {
            ++strPtr;
            ++strLen;
        }

        // Walk through all strings to find the last one.
        char* next = getNextString(current + strLen);
        while (next != nullptr) {
            char* nextNext = getNextString(next + strLen);
            current = next;
            next = nextNext;
        }

        // If the end of the last string exactly matches the used region boundary,
        // "pop" it by zeroing its first byte and adjusting the used size.
        if (current + strLen == m_pBuffer + m_usedSize) {
            *current = '\0';               // Mark as removed
            m_usedSize = (int)(current - m_pBuffer);   // Shrink used region
        }

        return this;
    }
};