// FUNC_NAME: Debug::vprintf
struct DebugPrefixInfo {
    char unknown[8]; // placeholder for padding/other fields
    char* prefix;    // +0x08: pointer to prefix string
};

struct OutputHandlerVTable {
    void (*write)(const char*); // vtable[1] at offset 4
};

struct OutputHandler {
    OutputHandlerVTable** vtable; // +0x00: vtable pointer
    OutputHandler* next;          // +0x04: next handler in list
};

// Global state
extern DebugPrefixInfo* gDebugPrefix; // DAT_01205a5c
extern OutputHandler* gOutputHandlers; // DAT_01205a54

void Debug::vprintf(const char* format, ...) {
    // Allocate buffer on stack (0x1000 bytes)
    char buffer[4092];
    char* writePos = buffer;
    char* src;

    // If a debug prefix is set, prepend it
    if (gDebugPrefix != nullptr) {
        src = gDebugPrefix->prefix;
        // Copy prefix string into buffer
        int offset = 0;
        do {
            char c = *src;
            buffer[offset] = c;
            src++;
            offset++;
        } while (c != '\0');

        // Find end of copied prefix
        char* prefixEnd = buffer;
        while (*prefixEnd != '\0') {
            prefixEnd++;
        }

        // Append ": " after prefix
        *prefixEnd = ':';
        prefixEnd[1] = ' ';
        writePos = prefixEnd + 2;
    }

    // Format the message into the remaining buffer space
    va_list args;
    va_start(args, format);
    __vsnprintf(writePos, sizeof(buffer) - (writePos - buffer), format, args);
    va_end(args);

    // Call all registered output handlers
    OutputHandler* handler = gOutputHandlers;
    while (handler != nullptr) {
        handler->vtable[1]->write(buffer); // vtable[1] is the write method
        handler = handler->next;
    }

    // Write to Windows debug output
    OutputDebugStringA(buffer);
    OutputDebugStringA("\n");
}