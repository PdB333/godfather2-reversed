// FUNC_NAME: StreamManager::closeStream

class StreamManager;

struct StreamManagerVTable {
    void (*stopStream)();                 // vtable + 0x260
    void (*releaseStream)(int id);        // vtable + 600 (0x258)
    void (*finalizeStream)();             // vtable + 0x25c
};

class StreamManager {
public:
    StreamManagerVTable* vtable;          // +0x00
    // ... many other fields ...
    int field_0x74C;                     // +0x74C (some state, must be non-zero and != 0x48)
    int field_0x24B4;                    // +0x24B4 (stream handle/state, must be non-zero and != 0x48)
    void* field_0x24BC;                  // +0x24BC (pointer to a stream object to be released)
    // ... rest of class ...

    void closeStream();
};

// External function assumed to release/free the stream object at the given address
void FUN_004daf90(void* streamObj);

void StreamManager::closeStream() {
    // Only proceed if both stream state values are valid (non-zero and not set to 0x48)
    if (field_0x24B4 != 0 && field_0x24B4 != 0x48 &&
        field_0x74C != 0 && field_0x74C != 0x48) 
    {
        // Stop the current stream
        vtable->stopStream();

        // Compute stream index: subtract 0x48 from the handle, or 0 if handle was 0
        int streamIndex;
        if (field_0x24B4 == 0)
            streamIndex = 0;
        else
            streamIndex = field_0x24B4 - 0x48;

        // Release the stream by its index
        vtable->releaseStream(streamIndex);

        // Finalize/cleanup after release
        vtable->finalizeStream();

        // If there is a pending stream object, release it and clear the pointer
        if (field_0x24BC != 0) {
            FUN_004daf90(field_0x24BC);
            field_0x24BC = 0;
        }
    }
}