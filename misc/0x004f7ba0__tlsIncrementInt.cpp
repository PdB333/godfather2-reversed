// FUNC_NAME: tlsIncrementInt
// Function address: 0x004f7ba0
// Role: Increments an integer in a thread-local storage (TLS) counter array.
// Accesses a base pointer from the first TLS slot, offsets 0x30 bytes to reach
// the counter array, then increments the element at the given byte offset.
// Returns the address of the incremented integer, or 0 if the offset is 0.

#include <cstdint>

// Helper to read FS segment offset (TIB/TLS on Windows)
inline void* readFsDword(uint32_t offset) {
    void* result;
    __asm {
        mov eax, fs:[offset]
        mov result, eax
    }
}

int* tlsIncrementInt(int byteOffset) {
    if (byteOffset == 0) {
        return nullptr;
    }

    // FS:0x2C -> pointer to TLS array (first slot)
    void** tlsArray = (void**)readFsDword(0x2C);
    // First TLS slot points to a structure; +8 yields base of counter array
    int* counterBase = *(int**)((char*)tlsArray[0] + 8);
    // Offset 0x30 to the counter array, then add the caller-provided byte offset
    int* counter = (int*)((char*)counterBase + 0x30 + byteOffset);
    (*counter)++;
    return counter;
}