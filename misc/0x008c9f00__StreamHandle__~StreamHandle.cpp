// FUNC_NAME: StreamHandle::~StreamHandle
// 0x008c9f00 - Destructor for StreamHandle, releases associated stream resource and zeroes fields

#include <cstddef>

struct StreamHandle {
    void* streamPtr;   // +0x00 - pointer to stream object
    int field_4;       // +0x04 - unknown state/flag
    int field_8;       // +0x08 - unknown state/flag
};

// Forward declaration of the resource release function
extern void __fastcall ReleaseStreamResource(void* streamPtr); // FUN_009c8f10

void __fastcall StreamHandle::~StreamHandle(StreamHandle* this) {
    // Clear flags
    this->field_4 = 0;
    // Release the underlying stream
    ReleaseStreamResource(this->streamPtr);
    // Clear pointer and remaining fields
    this->streamPtr = nullptr;
    this->field_8 = 0;
}