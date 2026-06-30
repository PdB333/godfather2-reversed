// FUNC_NAME: JsonWriter::writeString
// Function address: 0x0062ce80
// Writes a double-quoted JSON string with proper escaping, handling buffer growth and chunking.

#include <cstdint>

// Buffered writer context (12 bytes + temporary)
struct StreamBuffer {
    char* writePtr;       // +0x00: Current write position
    int32_t writtenCount; // +0x04: Number of items written (e.g., strings)
    void* manager;        // +0x08: Buffer manager object
    char temp[4];         // +0x0C: Temporary storage for chunk size
};

// External helpers (guessed names based on behavior)
extern char* getStringFromObject(void* obj);
extern int32_t getStringLength();
extern bool checkBufferOverflow(StreamBuffer* buf);   // FUN_00628940
extern void growBuffer(StreamBuffer* buf);           // FUN_006289a0
extern void writeRawData(const void* data, int size); // FUN_00628b20
extern void* saveBufferState();                      // FUN_00627290
extern void resetBuffer(void* mgr, int mode);        // FUN_00626f80
extern void flushBuffer(int mode);                   // FUN_00626fd0
extern void restoreBufferState(void* state);         // FUN_00627010
extern void commitBuffer();                          // FUN_006270e0
extern int32_t writeChunk(void* mgr, char* data, int size); // FUN_00638920

// Debug output
extern void debugString(const char* msg);            // FUN_00627ac0
extern const char* ERROR_STRING;                     // PTR_s_string_00e2a8ac

void jsonWriter_writeString(void* fromObject, StreamBuffer* buf) {
    char* src = getStringFromObject(fromObject);
    if (src == nullptr) {
        debugString(ERROR_STRING);
    }

    int32_t remaining = getStringLength(); // length of source string (decrementing counter)
    
    // Ensure buffer has space for opening quote
    if (buf->writePtr >= (char*)(buf + 0x83) && checkBufferOverflow(buf)) {
        growBuffer(buf);
    }
    *buf->writePtr = '"';
    buf->writePtr++;

    while (true) {
        if (remaining == 0) {
            // Write closing quote
            if (buf->writePtr >= (char*)(buf + 0x83) && checkBufferOverflow(buf)) {
                growBuffer(buf);
            }
            *buf->writePtr = '"';
            buf->writePtr++;
            return;
        }
        remaining--;

        switch (*src) {
        case '\0': // null character -> write "null" as 4-byte token
            writeRawData(&DAT_00e418a0, 4); // assumed "null" constant
            goto advance_src; // skip character write
        default: {
            // Check for buffer overflow and possibly flush a chunk
            if (buf->writePtr >= (char*)(buf + 0x83)) {
                int32_t dataSize = buf->writePtr - (char*)(buf + 0x0C);
                if (dataSize != 0) {
                    int32_t mgr = (int32_t)buf->manager;
                    // Save/restore state around buffer flush
                    uint32_t state = saveBufferState();
                    resetBuffer(mgr, 0);
                    flushBuffer(0);
                    resetBuffer(mgr, 0);
                    restoreBufferState(state);
                    commitBuffer();

                    // Write chunk header and data via manager
                    uint32_t* chunkEntry = *(uint32_t**)(mgr + 8);
                    *chunkEntry = 4; // size of raw data following? Or type 4?
                    uint32_t written = writeChunk(mgr, buf->temp, dataSize);
                    chunkEntry[1] = written;
                    *(int32_t*)(mgr + 8) = (int32_t)(chunkEntry + 2); // advance pointer
                    buf->writtenCount++;
                    buf->writePtr = (char*)(buf + 0x0C); // reset to temp area
                    growBuffer(buf);
                }
            }
            // Write the character (potentially escaped later)
            *buf->writePtr = *src;
            break;
        }
        case '\n':  // 0x0A
        case '"':   // 0x22
        case '\\':  // 0x5C
            // Escape: write backslash before the character
            if (buf->writePtr >= (char*)(buf + 0x83) && checkBufferOverflow(buf)) {
                growBuffer(buf);
            }
            *buf->writePtr = '\\';
            buf->writePtr++;

            if (buf->writePtr >= (char*)(buf + 0x83) && checkBufferOverflow(buf)) {
                growBuffer(buf);
            }
            *buf->writePtr = *src;
            break;
        }

        // Advance write pointer (unless we jumped to advance_src)
        if (*src != '\0') {
            buf->writePtr++;
        }
advance_src:
        src++;
    }
}