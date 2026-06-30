// FUNC_NAME: String16::erase
class String16 {
public:
    wchar_t* buffer; // +0x00
    int len;         // +0x04 (number of wchar_t elements, excluding null terminator)

    // Erases 'count' wchar_t elements starting at index 'start'.
    // If start+count >= len, all elements from start onward are removed.
    // Returns this pointer.
    String16* erase(int start, int count) {
        if (count == 0) {
            return this;
        }

        // If the range extends beyond or to the end, just truncate at start
        if ((unsigned int)len <= (unsigned int)(start + count)) {
            len = start;
            buffer[start] = 0; // null-terminate
            return this;
        }

        // Move the remaining tail forward
        memmove(&buffer[start], &buffer[start + count], (len - start - count) * sizeof(wchar_t));
        len -= count;
        buffer[len] = 0; // null-terminate
        return this;
    }
};