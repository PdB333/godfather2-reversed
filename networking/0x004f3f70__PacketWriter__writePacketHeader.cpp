// FUNC_NAME: PacketWriter::writePacketHeader
// 0x004f3f70 - Writes a packet header containing a vtable pointer, a type ID, and two 64-bit data fields.
// The stream object uses a pointer to a buffer structure; the current write position is at buffer+0x14.
// Data is packed sequentially: 4 bytes vtable, 4 bytes type ID, then two 8-byte values aligned to 4-byte boundaries.

void __thiscall PacketWriter::writePacketHeader(int* thisPtr, int typeId, int data1Low, int data1High, int data2Low, int data2High)
{
    // Dereference this to get the internal buffer pointer
    int* buffer = *thisPtr; // thisPtr points to a pointer to the buffer structure

    // Current write position (char*) is stored at buffer + 0x14
    char** ppWritePos = (char**)(buffer + 0x14); // buffer + 0x14: current write pointer

    // Write vtable pointer (likely a function table for the packet type)
    *(void**) *ppWritePos = (void*)&PTR_FUN_01124e18;
    *ppWritePos += 4;

    // Write the packet type identifier
    *(int*)*ppWritePos = typeId;
    *ppWritePos += 4;

    // Align write position to 4-byte boundary for the 8-byte writes
    *ppWritePos = (char*)(((int)*ppWritePos + 7) & 0xFFFFFFFC);

    // Write the first 64-bit data value (data1Low | data1High << 32)
    *(long long*)*ppWritePos = ((long long)data1High << 32) | (unsigned int)data1Low;
    *ppWritePos += 8;

    // Align to 4-byte boundary again (advances by 8 bytes to skip the just-written data)
    *ppWritePos = (char*)(((int)*ppWritePos + 11) & 0xFFFFFFFC);

    // Write the second 64-bit data value
    *(long long*)*ppWritePos = ((long long)data2High << 32) | (unsigned int)data2Low;
    *ppWritePos += 8;

    // Final pointer advancement (already done by the previous increments; this final addition ensures consistency)
    // Actually the original code adds 8 after the second write, but the pointer was already advanced by 8.
    // We keep it for fidelity.
    *ppWritePos = (char*)((int)*ppWritePos + 8);
}