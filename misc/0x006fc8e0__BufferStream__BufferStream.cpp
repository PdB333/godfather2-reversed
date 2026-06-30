// FUNC_NAME: BufferStream::BufferStream
// Function address: 0x006fc8e0
// Role: Constructor for a resizable buffer stream.
// Initializes internal fields, allocates/default buffer (128KB), and sets global reference.

#include <cstdint>

// Forward declarations of internal memory functions
extern void MemoryInitialize(int param1, int param2);
extern void MemoryFree(void* ptr);
extern void* MemoryAlloc(uint32_t size);

// Global default buffer size/reference (from .data at 0x00d5780c)
extern uint32_t gDefaultBufferSize;

class BufferStream {
public:
    // Constructor (__thiscall)
    BufferStream() {
        // Offset +0x18: pointer to a sub-object (initialized to null)
        int* subObjPtr = reinterpret_cast<int*>(this) + 6;
        *subObjPtr = 0;
        *(subObjPtr + 1) = 0; // Offset +0x1C

        // Some global initialization (likely memory system)
        MemoryInitialize(0, 1);

        // Zero-initialize first 6 int fields
        // Offsets 0x00-0x14: unknown fields, buffer pointer, buffer size, etc.
        reinterpret_cast<int*>(this)[0] = 0;
        reinterpret_cast<int*>(this)[1] = 0;
        reinterpret_cast<int*>(this)[2] = 0; // buffer pointer
        reinterpret_cast<int*>(this)[3] = 0; // buffer size
        reinterpret_cast<int*>(this)[4] = 0;
        reinterpret_cast<int*>(this)[5] = 0;

        // Free sub-object if previously allocated
        if (*subObjPtr != 0) {
            MemoryFree(reinterpret_cast<void*>(*subObjPtr));
            *subObjPtr = 0;
        }

        // Set field at offset +0x20 to 0, field at +0x24 to global value
        reinterpret_cast<int*>(this)[8] = 0;
        reinterpret_cast<int*>(this)[9] = static_cast<int>(gDefaultBufferSize);

        // Ensure buffer size is at least 128KB
        if (reinterpret_cast<int*>(this)[3] < 0x20000) {
            // Free existing buffer if any
            if (reinterpret_cast<int*>(this)[2] != 0) {
                MemoryFree(reinterpret_cast<void*>(reinterpret_cast<int*>(this)[2]));
            }
            // Update size and allocate new buffer
            reinterpret_cast<int*>(this)[3] = 0x20000;
            reinterpret_cast<int*>(this)[2] = reinterpret_cast<int>(MemoryAlloc(0x20000));
        }
    }
};