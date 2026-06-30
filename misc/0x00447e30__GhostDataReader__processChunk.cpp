// FUNC_NAME: GhostDataReader::processChunk
// Address 0x00447e30: Process a chunk of data from a ghost data reader (type 1: copy from buffer, type 2: invoke callback)
// Uses dynamic stack allocation for temporary receive buffer

#include <cstring> // for memcpy

void GhostDataReader::processChunk(void* param) {
    // param is passed in EAX - points to a structure containing the size (offset +4)
    uint32_t requestedSize = *(uint32_t*)((uint8_t*)param + 4);

    // Allocate a temporary buffer on the stack (aligned to 16 bytes via __alloca_probe_16)
    int stackOffset = -static_cast<int>(requestedSize);
    // The actual buffer is at &stackBuffer (relative to original stack pointer)
    // In decompilation: puVar7 = &stack0xffffffe4 + iVar4;

    int* object = this;  // unaff_ESI is the object pointer (this)
    int type = *object;  // +0x00: type flag (1 = buffer read, 2 = callback)

    if (type == 1) {
        int readOffset = object[3];      // +0x0C: current read offset in buffer
        uint32_t availableSize = object[4] - readOffset;  // +0x10: total data size
        if (availableSize < requestedSize) {
            requestedSize = availableSize;
        }
        uint8_t* bufferBase = reinterpret_cast<uint8_t*>(object[5]);  // +0x14: pointer to data buffer
        uint8_t* source = bufferBase + readOffset;

        // memcpy to the temporary stack buffer
        memcpy(&stackBuffer, source, requestedSize);

        // Update read offset
        object[3] = readOffset + requestedSize;
    }
    else if (type == 2) {
        int callbackArg = object[7];      // +0x1C: argument for callback
        auto callbackFunc = reinterpret_cast<void(*)(uint32_t, void*, int)>(object[4]);  // +0x10: function pointer

        // Prepare parameters for the callback (size, temp buffer, argument)
        // The temporary buffer is on stack
        callbackFunc(requestedSize, &stackBuffer, callbackArg);
    }

    // After processing, call cleanup/validation function (FUN_0043ab10)
    // Followed by destructor or finalizer (FUN_00447d70)
    FUN_0043ab10();  // unknown: possibly checksum or validation
    FUN_00447d70();  // unknown: likely cleanup/free resources
}