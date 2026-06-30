// FUNC_NAME: DataBufferProcessor::processBuffer

#include <cstring>

// External functions (EA EARS engine internal)
extern "C" {
    void* __cdecl earAlloc(size_t size);                            // FUN_009c8e50
    void  __cdecl earFree(void* ptr);                              // FUN_009c8eb0
    const char* __cdecl decodeBuffer(const char* buf);             // FUN_004dafd0 – returns a processed string pointer
    void __cdecl earStringSet(EARSString* str, const char* val);  // FUN_00408260
    void __cdecl earStringAppend(EARSString* str, int ch);         // FUN_00408a00
    void __cdecl earStringDestroy(EARSString* str);                // FUN_00408310
}

// 8‑byte EA string structure (typical EARSString)
struct EARSString {
    char*   data;     // +0x00
    uint16_t length;  // +0x04
    uint16_t capacity; // +0x06
};

// Data buffer descriptor (offset of size field: +0x04)
struct DataBuffer {
    void*   data;     // +0x00
    size_t  size;     // +0x04
};

// Command structure for buffer operations (indices relative to param_2)
struct BufferCommand {
    int  mode;        // [0] – 1: copy from source, 2: call callback
    int  _pad[2];     // [1],[2] unused
    int  offset;      // [3] – source offset (mode 1)
    union {
        size_t   copySize;                // [4] – source size (mode 1)
        void  (*callback)(void*, char*, size_t); // [4] – callback function (mode 2)
    };
    char* sourcePtr;  // [5] – source buffer base (mode 1)
    int   _pad2;      // [6] – unused
    void* userData;   // [7] – callback user data (mode 2)
};

// Reconstructed function at 0x00487620
void DataBufferProcessor::processBuffer(DataBuffer* buffer, BufferCommand* cmd)
{
    // Allocate destination buffer from the EARS memory pool
    size_t size = buffer->size;
    char* dst = static_cast<char*>(earAlloc(size));

    // Dispatch based on command mode
    if (cmd->mode == 1) {
        // Mode 1: copy from source with offset
        size_t available = cmd->copySize - cmd->offset;
        if (available < size) {
            size = available;
        }
        memcpy(dst, cmd->sourcePtr + cmd->offset, size);
        cmd->offset += size;
    }
    else if (cmd->mode == 2) {
        // Mode 2: invoke callback with the allocated buffer
        cmd->callback(cmd->userData, dst, size);
    }

    // Process the buffer as a string (decode, hash, or log)
    EARSString localStr;
    localStr.data     = nullptr;
    localStr.length   = 0;
    localStr.capacity = 0;

    if (dst != nullptr && dst[0] != '\0') {
        const char* processed = decodeBuffer(dst);
        earStringSet(&localStr, processed);
    }

    // Build a temporary string (likely a wide‑char or formatted copy)
    EARSString tempStr = localStr;   // shallow structure copy
    tempStr.length   = 0;
    tempStr.capacity = 0;
    earStringAppend(&tempStr, 0);    // append terminator
    earStringDestroy(&localStr);

    // Free the temporary buffer
    earFree(dst);
}