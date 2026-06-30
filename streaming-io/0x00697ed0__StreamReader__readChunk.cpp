// FUNC_NAME: StreamReader::readChunk
// Function address: 0x00697ed0
// Reads a chunk of data from a file handle, allocates buffer, processes it.
// Returns 8 on success, 0 on failure. Output bool indicates if more data remains.

#include <windows.h>

int __thiscall StreamReader::readChunk(bool* outHasMoreData) {
    DWORD bytesRead;
    bool hasMoreData = *(int*)(this + 0x28) != 0;  // +0x28: remaining size
    *outHasMoreData = hasMoreData;
    if (!hasMoreData) {
        return 8;  // No more data, success
    }

    // Allocate a temporary 8-byte header (type=4, flags=0)
    int* header = (int*)allocateMemory(8);  // FUN_009c8e50
    if (header != nullptr) {
        header[0] = 4;           // Type field
        *(short*)(header + 2) = 0;  // Flags low
        *(short*)((char*)header + 6) = 0; // Flags high
    }
    *(int**)(this + 0x14) = header;  // +0x14: temporary header pointer

    // Read 4 bytes into the beginning of this object (likely chunk size or sub-header)
    if (!ReadFile(*(HANDLE*)(this + 0x18), this, 4, &bytesRead, nullptr)) {
        return 0;  // Read failed
    }

    int remainingSize = *(int*)(this + 0x24) - bytesRead;  // +0x24: total size?
    *(int*)(this + 0x28) = remainingSize;

    // Allocate buffer for the remaining data
    void* buffer = reallocateMemory(remainingSize);  // FUN_009c8e80
    *(void**)(this + 0x2c) = buffer;

    // Read the remaining data into the buffer
    if (!ReadFile(*(HANDLE*)(this + 0x18), buffer, *(DWORD*)(this + 0x28), &bytesRead, nullptr)) {
        return 0;  // Read failed
    }

    // Replace the temporary header with the actual data buffer
    *(int*)(this + 0x14) = (int)buffer;          // +0x14: now points to data
    *(int*)(this + 0x30) = (int)buffer + 8;      // +0x30: pointer after 8-byte header

    // Process the buffer (e.g., decompress)
    int result = processData(0, buffer, *(int*)(this + 0x28));  // FUN_00ab8560
    *(int*)(this + 0x1c) = result;  // +0x1c: store result

    // Update remaining size and output flag
    *(int*)(this + 0x28) = *(int*)(this + 0x28) - bytesRead;
    *outHasMoreData = *(int*)(this + 0x28) != 0;

    return 8;  // Success
}