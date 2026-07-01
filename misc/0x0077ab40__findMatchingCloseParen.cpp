// FUNC_NAME: findMatchingCloseParen
// Function address: 0x0077ab40
// Role: Scans a string buffer starting from index 1, assuming index 0 is an opening parenthesis '('.
// Counts nested parentheses until depth returns to 0, then stops at the matching closing parenthesis.
// Used as a helper to skip parenthesized expressions in script/string parsing.

void findMatchingCloseParen(void* state) {
    // state is a pointer to a struct with fields:
    // +0x00: char* buffer  (pointer to character array)
    // +0x04: int length    (length of buffer)
    int* stateFields = (int*)state;
    char* buffer = (char*)stateFields[0];  // +0x00
    int length = stateFields[1];           // +0x04

    int depth = 1;          // assume first character is '(' at index 0
    uint index = 1;         // start scanning from index 1

    if (1 < (uint)length) {
        do {
            if (buffer[index] == '(') {
                depth++;
            }
            if (buffer[index] == ')') {
                depth--;
            }
            // Increment index and check bounds only if depth != 0
            // When depth reaches 0, loop exits immediately
        } while ((depth != 0) && (++index < (uint)length));
    }
    // Note: index now points to the matching ')', but result is not stored.
    // Caller may rely on side effects or this function is a validation check.
}