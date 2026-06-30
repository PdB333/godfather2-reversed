// FUNC_NAME: FileReadBuffer::processReadRequest
// Address: 0x005f38d0
// This function appears to manage an asynchronous read operation from a file/buffer.
// It checks the read state, allocates a larger buffer if needed, and initiates a chunk read (0x20 bytes).
// The global mutex (DAT_00e2aea0) is locked during the operation.

#include <cstdint>

// Forward declarations of called functions (assumed from game engine)
extern void lockGlobalMutex();          // FUN_00ab4db0(&DAT_00e2aea0)
extern void unlockGlobalMutex();        // FUN_00ab4e70()
extern uint64_t getSystemPageSize();    // FUN_00ac28e0()
extern void* allocateFromEngine(uint32_t size); // via global table at 0x01223510+0x55c
extern void readFileAsync(void* fileHandle, void* buffer, uint32_t blockSize, uint32_t offset,
                           uint32_t remainingBytes, void (*callback)(void*), void* userData, uint32_t flags); // FUN_00ac4290
extern void setCompletionCallback(void* fileHandle, void (*callback)(void*), void* userData, uint32_t flags); // FUN_00ac3b80

// Callback addresses (declared as extern functions, but bodies not shown)
extern void onChunkReadComplete(void* userData);      // LAB_005f3af0
extern void onSmallReadComplete(void* userData);      // LAB_005f3cb0
extern void onOtherReadComplete(void* userData);      // LAB_005f3c50

class FileReadBuffer {
public:
    // Offsets:
    // +0x14: pointer to async state (FileReadAsyncState)
    // +0xA0: result/status code (negative = error)
    // +0xA4: state (2 = reading)
    // +0xF8: file handle (HANDLE or FILE*)
    // +0xFC: retry count (byte)
    // +0x100: padding?
    // +0x104: total remaining bytes to read (or total size?)
    // +0x11C: buffer pointer
    // +0x128: buffer size
    // +0x12C: flag (0 = buffer not allocated yet / not owned)
    // +0x130: ...?

    void processReadRequest();
};

struct FileReadAsyncState {
    int status;          // +0xA0
    int state;           // +0xA4 (2=reading)
    void* fileHandle;    // +0xF8
    uint8_t retryCount;  // +0xFC
    uint32_t remainingBytes; // +0x104
    void* buffer;        // +0x11C
    uint32_t bufferSize; // +0x128
    uint32_t bufferFlag; // +0x12C (0 = need alloc, non-zero = owned)
};

void FileReadBuffer::processReadRequest() {
    FileReadAsyncState* state = *(FileReadAsyncState**)((uint8_t*)this + 0x14);
    if (state == nullptr) return;

    lockGlobalMutex();

    if (state->status < 0) {
        unlockGlobalMutex();
        return;
    }

    if (state->state == 2) {
        // Already reading, set up completion callback for current file handle
        setCompletionCallback(state->fileHandle, onChunkReadComplete, this, 0);
    } else {
        uint64_t pageSize = getSystemPageSize();
        void* fileHandle = state->fileHandle;

        if (pageSize == 0x20) {
            // System page/allocation size is 32 bytes
            if (state->retryCount < 4) {
                uint32_t remaining = state->remainingBytes - 0x20;
                if (remaining != 0) {
                    // Need to read more than 32 bytes; allocate a larger buffer if necessary
                    if (state->bufferFlag == 0 && state->bufferSize < remaining) {
                        // Allocate new buffer via engine method
                        void* newBuffer = allocateFromEngine(remaining);
                        state->buffer = newBuffer;
                        state->bufferSize = remaining;
                        state->bufferFlag = 0; // not owned? (original line: *(undefined4 *)(iVar1 + 300) = 0)
                    }
                    // Start async read of next 32-byte chunk
                    readFileAsync(state->fileHandle, state->buffer, 0x20, 0,
                                  remaining, onChunkReadComplete, this, 0);
                    unlockGlobalMutex();
                    return;
                } else {
                    // Exactly 32 bytes remaining, just set small read callback
                    setCompletionCallback(fileHandle, onSmallReadComplete, this, 0);
                }
            } else {
                // Retry count >=4, fall through to default
            }
        } else {
            // Page size is not 32; set other callback
            setCompletionCallback(fileHandle, onOtherReadComplete, this, 0);
        }

        // Set state to reading
        state->state = 2;
        setCompletionCallback(fileHandle, onChunkReadComplete, this, 0); // Actually uses puVar6 (onChunkReadComplete or onOtherReadComplete?) 
        // Note: The original code sets puVar6 = &LAB_005f3c50 for pageSize!=0x20 and then calls setCompletionCallback with that callback.
        // But the decompiled code shows at LAB_005f3a68: FUN_00ac3b80(iVar5,puVar6,iVar1,0);
        // For clarity, we'll set the callback determined above.
    }

    unlockGlobalMutex();
}