// FUNC_NAME: TokenReader::skipDotsThenColon
int TokenReader::skipDotsThenColon() {
    // Step 1: Obtain a character from some global source (like the current token stream)
    int initialChar = getGlobalStreamChar();      // Calls FUN_0063dd40
    // Step 2: Insert that character back into this reader's stream (offset +0x1c)
    pushBackToStream(*(int*)(this + 0x1c), initialChar); // Calls FUN_0063e160

    // Step 3: Check the current character stored at offset +0xc
    int currentChar = *(int*)(this + 0xc);
    // Step 4: Skip all '.' characters
    while (currentChar == '.') {
        advanceAndRead();                         // Calls FUN_0063e790
        currentChar = *(int*)(this + 0xc);
    }
    // Step 5: Expect a ':' character
    if (currentChar != ':') {
        return 0;                                 // Failure
    }
    // Step 6: Consume the ':' and advance
    advanceAndRead();                             // Calls FUN_0063e790
    return 1;                                     // Success
}