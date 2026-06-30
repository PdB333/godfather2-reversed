// FUNC_NAME: Debug::outputFloat
void Debug::outputFloat(float value) {
    float result = formatFloat(value); // FUN_00595490 - possibly converts to string or formats
    if (flags & 1) {
        result = formatFloat(result);
        formatFloat(result); // second call for side effect (maybe flush or double output)
    }
    char buffer[48];
    formatString(buffer); // FUN_0059bde0 - likely fills buffer with prefix/context

    // Virtual methods for output (console, file, etc.)
    (this->vtable[4])(local_20);   // +0x10: outputLine? local_20 is a 28-byte buffer
    (this->vtable[7])(stackBuffer); // +0x1c: outputRaw? stackBuffer is 4-byte
}

// Additional notes:
// - this->flags is at offset +0x04 (bit 0 enables additional formatting)
// - FUN_00595490 is a conversion/formatting helper (returns float)
// - FUN_0059bde0 likely initializes a string or struct in buffer[48]
// - local_20 and auStack_54 are output buffers for virtual functions