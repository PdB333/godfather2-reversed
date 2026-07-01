// FUNC_NAME: StringTokenizer::tokenize
// Function address: 0x00817170
// Role: Tokenizes a string using delimiters and stores tokens in a dynamic array.
// Class layout (offsets relative to this):
//   +0x04: char** m_buffer       (pointer to array of token pointers)
//   +0x08: int m_size            (current number of tokens)
//   +0x0C: int m_capacity        (allocated capacity)
//   +0x10: char* m_sourceString  (string to tokenize, or null for default)

void __thiscall StringTokenizer::tokenize(int this, undefined4 delimiter1, undefined4 delimiter2)
{
    char* tokenStart;
    int tokenLength;
    char* nextToken;
    int newCapacity;
    char** slot;

    // Unused global reference (likely debug or version info)
    // local_8 = DAT_0122349c;

    // Get source string; if null, use a default string (e.g., empty or placeholder)
    tokenStart = *(char**)(this + 0x10);
    if (tokenStart == (char*)0x0) {
        tokenStart = &DAT_0120546e;  // default string
    }

    while (true) {
        // Call tokenizer function: extracts next token from tokenStart
        // Parameters: source, delimiter1, &tokenLength, delimiter2, &nextToken, 0, 0, 0
        FUN_0048be50(tokenStart, delimiter1, &tokenLength, delimiter2, &nextToken, 0, 0, 0);
        if (tokenLength == 0) {
            break;  // No more tokens
        }

        // Check if array needs to grow
        if (*(int*)(this + 8) == *(int*)(this + 0xc)) {
            // Capacity full: double it (or set to 1 if currently 0)
            if (*(int*)(this + 0xc) == 0) {
                newCapacity = 1;
            } else {
                newCapacity = *(int*)(this + 0xc) * 2;
            }
            FUN_00816d90(newCapacity);  // Reallocate buffer
        }

        // Store token pointer and increment size
        slot = (undefined4*)(*(int*)(this + 4) + *(int*)(this + 8) * 4);
        *(int*)(this + 8) = *(int*)(this + 8) + 1;
        if (slot != (undefined4*)0x0) {
            *slot = tokenStart;  // Store pointer to current token
        }

        // Move to next token start
        tokenStart = nextToken;
        if (nextToken == (char*)0x0) {
            break;  // End of string
        }
    }
    return;
}