// FUNC_NAME: WriteStream::writeAlignedHeader
// Address: 0x004e6c10
// Role: Writes a message header with a vtable pointer, message type, aligned 16-byte GUID, and additional flags. The stream maintains a cursor pointer at offset 0x14 within its internal buffer.

// PTR_LAB_01124b94 is a global vtable for a message header class.
extern void* g_MessageHeaderVTable; // actually PTR_LAB_01124b94

class WriteStream {
public:
    // The buffer structure (allocated externally):
    // offset 0x00: start of internal buffer
    // offset 0x14: current write pointer (stores pointer to next free location in buffer)
    // The data area begins after the header.
    uint8_t* m_buffer; // pointer to the allocated buffer (at this+0)
    // Note: In the decompiled code, *this gives m_buffer, and m_buffer+0x14 is the cursor.
    
    void writeAlignedHeader(uint32_t messageType, const uint8_t guid[16], uint32_t additionalFlags) {
        uint8_t* buffer = m_buffer; // iVar2 = *param_1
        
        // Write vtable pointer into the location pointed by the current cursor.
        // The cursor is a pointer stored at buffer+0x14.
        // First, dereference the cursor to get the target address, then write the vtable.
        void** cursor = *(void***)(buffer + 0x14); // read current cursor pointer
        *cursor = &g_MessageHeaderVTable;           // write vtable
        // Advance cursor by 4 bytes (size of a pointer).
        *(uintptr_t*)(buffer + 0x14) = (uintptr_t)(cursor) + 4;
        
        // Write messageType at the new cursor location.
        cursor = *(void***)(buffer + 0x14); // re-read updated cursor
        *(uint32_t*)cursor = messageType;
        *(uintptr_t*)(buffer + 0x14) = (uintptr_t)(cursor) + 4;
        
        // Align the cursor to the next 16-byte boundary.
        cursor = *(void***)(buffer + 0x14);
        uint8_t* alignedCursor = (uint8_t*)(((uintptr_t)cursor + 0x13) & ~0xF);
        *(uintptr_t*)(buffer + 0x14) = (uintptr_t)alignedCursor;
        
        // Write 16 bytes from guid at the aligned position.
        uint8_t* writePtr = alignedCursor;
        memcpy(writePtr, guid, 16);
        
        // Write additionalFlags at offset 16 from the aligned cursor.
        *(uint32_t*)(writePtr + 16) = additionalFlags;
        
        // Advance the cursor by 0x14 (20) bytes from the aligned base.
        *(uintptr_t*)(buffer + 0x14) = (uintptr_t)(alignedCursor + 0x14);
    }
};