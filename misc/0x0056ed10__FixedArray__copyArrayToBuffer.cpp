// FUNC_NAME: FixedArray::copyArrayToBuffer
// Address: 0x0056ed10
// Role: Copies the internal array data to an output buffer if the current count is within the requested maximum.
// - The internal array stores 32-byte elements.
// - Returns true if the copy was performed (count <= maxElements), false otherwise.
// - The output buffer is zeroed except for the fields: +0x08 byte set to 1, +0x0A ushort (capacity), +0x0C int (count), and the data copied starting at +0x10.

#include <cstring>

// Assuming these types exist (from the context):
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;

// Structure representing the output buffer layout
struct ArrayBuffer {
    undefined4 field_0;    // +0x00: zeroed
    undefined4 field_4;    // +0x04: zeroed
    undefined1 field_8;    // +0x08: set to 1
    undefined1 field_9;    // +0x09: zeroed
    undefined2 capacity;   // +0x0A: copied from source
    undefined4 count;      // +0x0C: copied from source
    undefined1 data[1];    // +0x10: start of copied array (variable length)
};

// This is the reconstructed function
bool __thiscall FixedArray::copyArrayToBuffer(int thisPtr, unsigned int maxElements, void* outBuffer) {
    // The this pointer points to the FixedArray object.
    // Offsets: +0x0A = capacity (ushort), +0x0C = count (int), +0x10 = data array (each element 32 bytes)
    unsigned short capacity = *(unsigned short*)(thisPtr + 0x0A);
    int count = *(int*)(thisPtr + 0x0C);
    
    // Only copy if the current count does not exceed the requested maximum
    if (capacity <= maxElements) {
        // Initialize the output buffer fields
        ArrayBuffer* buf = (ArrayBuffer*)outBuffer;
        buf->field_0 = 0;
        buf->field_4 = 0;
        buf->field_9 = 0;
        buf->field_8 = 1;
        buf->capacity = capacity;
        buf->count = count;
        
        // Copy the actual array data (count * 32 bytes)
        memcpy(&buf->data[0], (void*)(thisPtr + 0x10), count << 5); // shift left 5 = multiply by 32
        
        return true;
    }
    return false;
}