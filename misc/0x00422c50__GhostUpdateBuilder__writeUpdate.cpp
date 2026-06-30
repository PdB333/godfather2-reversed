// FUNC_NAME: GhostUpdateBuilder::writeUpdate
// Reconstructed from 0x00422c50 - writes a ghost update packet header and data
// Uses a buffer with a write cursor at offset 0x14 from the base object pointer.
// The buffer is pointed to by the handle stored at the class's first member (this+0).
// Parameters:
//   this  - pointer to a handle (int*) that points to the actual object with buffer.
//   id    - 4-byte identifier (presumably ghost update type)
//   data  - 64-byte data block to copy into the update
//   flag  - boolean flag written at the end

#include <cstring>

class GhostUpdateBuilder {
public:
    void __thiscall writeUpdate(uint32_t id, void* data, bool flag);
};

void __thiscall GhostUpdateBuilder::writeUpdate(uint32_t id, void* data, bool flag) {
    // Get the actual object pointer from the handle (this points to handle)
    uint8_t* basePtr = *(uint8_t**)this;  // +0x00: handle to object
    
    // Write vtable pointer for the update structure
    *(uint32_t**)(basePtr + 0x14) = &PTR_LAB_0110b690;  // +0x14: write cursor points to vtable slot
    // Advance cursor by 4 bytes (size of vtable pointer)
    uint8_t* cursor = *(uint8_t**)(basePtr + 0x14);  // restore cursor after increment
    cursor += 4;
    *(uint8_t**)(basePtr + 0x14) = cursor;
    
    // Re-fetch base pointer (handle may have changed? but likely stable)
    basePtr = *(uint8_t**)this;
    
    // Write the id (4 bytes) at current cursor position
    *(uint32_t*)cursor = id;  // cursor points to location after vtable
    cursor += 4;
    *(uint8_t**)(basePtr + 0x14) = cursor;
    
    // Align cursor to next 16-byte boundary before writing data block
    cursor = (uint8_t*)((uint32_t)(cursor + 0x13) & 0xFFFFFFF0);
    *(uint8_t**)(basePtr + 0x14) = cursor;
    
    // Copy 64 bytes of data into the buffer
    memcpy(cursor, data, 0x40);
    cursor += 0x40;
    *(uint8_t**)(basePtr + 0x14) = cursor;
    
    // Write the boolean flag as a single byte
    *cursor = flag ? 1 : 0;
    cursor += 1;
    
    // Align cursor to next 4-byte boundary (for future writes)
    cursor = (uint8_t*)((uint32_t)(cursor + 4) & 0xFFFFFFFC);
    *(uint8_t**)(basePtr + 0x14) = cursor;
}