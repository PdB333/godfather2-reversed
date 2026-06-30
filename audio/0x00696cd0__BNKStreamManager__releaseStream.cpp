// FUNC_NAME: BNKStreamManager::releaseStream
// Address: 0x00696cd0
// Purpose: Release the audio stream handle and associated buffer, reset state to zero.

struct BNKStreamManager {
    // +0x00: vtable pointer
    int* streamHandle; // +0x04: pointer to audio data pointer (handle to allocated buffer)
    int streamSize;    // +0x08: size or status indicator
};

// Forward declarations for callees (actual implementations elsewhere)
void constructStreamTask(char taskBuf[8], BNKStreamManager* mgr, int* audioData, BNKStreamManager* mgrAgain, int* streamHandle);
void releaseStreamBuffer(void* ptr);

void __thiscall BNKStreamManager::releaseStream(BNKStreamManager* this) {
    char taskBuffer[8]; // Temporary buffer used to construct a stream-release task object

    // Build a task that will finalize the stream using both the handle and the actual data pointer
    constructStreamTask(taskBuffer, this, *(this->streamHandle), this, this->streamHandle);

    // Free the underlying resource (presumably the allocation pointed to by streamHandle)
    releaseStreamBuffer(this->streamHandle);

    // Clear the handle and size fields to avoid dangling pointers
    this->streamHandle = nullptr;
    this->streamSize = 0;
}