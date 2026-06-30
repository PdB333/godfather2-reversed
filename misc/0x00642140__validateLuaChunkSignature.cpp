// FUNC_NAME: validateLuaChunkSignature
// Function at 0x00642140: Validates the Lua bytecode header signature "\x1bLua".
// Reads bytes sequentially from an input stream and compares them against the magic.
// On mismatch, triggers an assertion failure with a log message.
void validateLuaChunkSignature(void)
{
    // Expected Lua bytecode signature (note \x1b = 0x1B = ESC)
    const char *signature = "\x1bLua";
    int readByte;
    
    do {
        // Read next byte from input stream (likely via some data source pointer in EAX)
        readByte = readNextByte(); // FUN_006418b0
        if (readByte != *signature) {
            // If mismatch and signature not fully consumed, assertion failure
            if (*signature == '\0') {
                return; // Full signature matched
            }
            // Log error: "bad signature in <stream name>"
            // in_EAX points to some structure (maybe a stream descriptor) with name at offset 0x10
            assertionFailedLog(*in_EAX, "bad signature in %s", in_EAX[4]); // FUN_00633920
            // Trigger debug break (swi 3)
            __debugbreak();
            return;
        }
        signature++;
    } while (*signature != '\0');
    
    return; // Signature valid
}