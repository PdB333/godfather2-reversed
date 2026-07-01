// FUNC_NAME: findMatchingParen
// Function address: 0x0077ab40
// Finds the index of the closing parenthesis matching the opening '(' at position 0
// of a string described by a pointer/length pair. Returns via void (likely omitted).
// Fields: +0x00 char* data, +0x04 int length

void findMatchingParen(int* stringDesc) {
    uint index = 1;                    // Start scanning from index 1
    int depth = 1;                     // Initial depth: one '(' at index 0

    if (1 < (uint)stringDesc[1]) {     // Only if string length > 1
        do {
            if (*(char*)(*stringDesc + index) == '(') {
                depth++;
            }
            if (*(char*)(*stringDesc + index) == ')') {
                depth--;
            }
            // Continue while depth > 0 and index < length
            if (depth == 0) break;
            index++;
        } while (index < (uint)stringDesc[1]);
    }
    // At this point, index is the position of the matching ')'
    // (but the function does not return it; caller may read global/parameter?)
}