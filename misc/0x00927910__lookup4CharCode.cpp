// FUNC_NAME: lookup4CharCode
int lookup4CharCode(const char* str)
{
    // Check for null pointer
    if (str == nullptr)
        return 0;

    // Find length of the input string (scan until null)
    const char* end = str;
    while (*end != '\0')
        ++end;

    // Length of string (excluding first char) must be > 4 -> total length >= 6
    // i.e., we need at least characters str[0]..str[5]
    if ((end - (str + 1)) > 4)
    {
        // Extract 4 characters starting at str[1] into a local buffer
        // This skips the first character (str[0])
        char codeBuffer[5]; // 4 chars + null terminator
        codeBuffer[0] = str[1];
        codeBuffer[1] = str[2];
        codeBuffer[2] = str[3];
        codeBuffer[3] = str[4];
        codeBuffer[4] = '\0';

        // Hash the 4-character code and look up an ID
        // The following three subroutines implement a custom hash lookup
        void* hashCtx = FUN_005bff40(codeBuffer);   // Initialize hash context with codeBuffer
        FUN_005c3960(hashCtx);                      // Compute hash value
        int result = FUN_005c3ef0(hashCtx);         // Lookup and return internal ID

        // If a valid ID was found, subtract 0x10 to get external ID (offset)
        if (result != 0)
            return result - 0x10;
    }

    // No match or insufficient length
    return 0;
}