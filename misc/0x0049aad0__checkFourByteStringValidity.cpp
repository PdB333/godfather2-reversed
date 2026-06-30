// FUNC_NAME: checkFourByteStringValidity
void checkFourByteStringValidity(uint32_t valueFirstHalf, uint32_t valueSecondHalf) {
    char isValid = 0;
    // Treat the first parameter as a 4-byte array (adjacent to second on stack)
    char* bytes = (char*)&valueFirstHalf;
    for (int i = 0; i < 4; ++i) {
        if (isValid != 0) {
            return;
        }
        if (bytes[i] != 0) {
            isValid = FUN_00b93170(bytes[i]); // Returns non-zero if character invalid
        }
    }
    // Function silently returns; caller checks global state? (isValid is discarded)
}