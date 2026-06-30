// FUNC_NAME: ObjectSerializer::writeWithHeader
// Address: 0x004b2a50
// This function writes an object's data to a custom memory stream, including a vtable pointer and alignment.

#include <cstring> // for memcpy

// PTR_LAB_01124528 is a static vtable pointer (likely for the object type)
extern void* PTR_LAB_01124528;

// The memory stream structure (assumed layout)
struct MemoryStream {
    char* data;       // +0x00: pointer to memory block
    char* writePtr;   // +0x14: current write position
};

// __fastcall: ecx = this (unused), edx = pStream (int*), stack = extraData (first word of object)
void __fastcall ObjectSerializer::writeWithHeader(void* thisPtr, int* pStream, unsigned int extraData)
{
    // Get the stream's base pointer from the handle
    int baseAddr = *pStream;
    MemoryStream& stream = *(MemoryStream*)baseAddr;

    // Step 1: Write the vtable pointer at current position
    *(void**)stream.writePtr = &PTR_LAB_01124528;
    stream.writePtr += 4;

    // Step 2: Copy the object data from the stack into a local buffer (0x854 bytes)
    // The stack data starts at the third parameter location (extraData) on the stack.
    // We copy 0x215 (533) 4-byte dwords = 0x854 bytes.
    unsigned int localBuffer[534]; // array large enough
    unsigned int* src = (unsigned int*)&extraData; // point to the start of the stack object
    for (int i = 0; i < 533; i++) {
        localBuffer[i] = *src;
        src++;
    }

    // Step 3: Write extraData again at the current stream position (after vtable)
    *(unsigned int*)stream.writePtr = extraData;

    // Step 4: Align the write pointer to the next 4-byte boundary
    char* alignedDest = (char*)(((int)(stream.writePtr) + 7) & ~3);
    stream.writePtr = alignedDest;

    // Step 5: Copy the entire local buffer (0x854 bytes) to the aligned destination
    memcpy(stream.writePtr, localBuffer, 0x854);
    stream.writePtr += 0x854;
}