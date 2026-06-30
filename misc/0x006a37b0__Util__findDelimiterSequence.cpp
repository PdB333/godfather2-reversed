// FUNC_NAME: Util::findDelimiterSequence
// Address: 0x006a37b0
// Finds a pattern of two 0x3f markers followed by 0x3e in an array of 16-bit values.
// Returns the index (element offset) of the element after the 0x3e, or -1 if pattern not found, -2 if initial marker missing.
#include <cstdint>

int Util::findDelimiterSequence(uint16_t* buffer) {
    // Check that the second short (index 1) is the start marker 0x3f
    if (buffer[1] != 0x3f) {
        return -2;
    }
    int i;
    // Scan for the next 0x3f starting from index 2
    for (i = 2; buffer[i] != 0x3f; i++) {
        // empty
    }
    // The element after the found 0x3f must be 0x3e
    if (buffer[i + 1] == 0x3e) {
        return i + 2;  // return index of element after the 0x3e
    }
    return -1;
}