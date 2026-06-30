// FUNC_NAME: NetConnection::addChunk
// Function address: 0x0059a060
// Reconstructed from Ghidra decompilation. This function appears to copy data from a PacketBuffer
// into a chunk (likely for reliable packet transmission in TNL). The buffer descriptor is stored
// at offset 0x8 from the object (NetConnection). The chunk is allocated via FUN_00599aa0 using
// a key formed by concatenating 4 bytes from the buffer header. The chunk is then initialized
// with type 2, the data length from the buffer count, and a pointer to the buffer data.
// The chunk's flags are cleared (bits 0 and 1) to mark it as ready.

void __fastcall NetConnection::addChunk(void)
{
    // Pointer to the buffer descriptor (PacketBuffer) stored at +0x8 in this object
    PacketBuffer* buf = *(PacketBuffer**)(this + 8);
    
    // Validate buffer: currentSize (ushort at +2) should equal maxCount * sizeof(Element) + headerSize
    // Element size = 0x14 (20 bytes), header size = 0x18 (24 bytes)
    if ((uint)buf->currentSize != buf->maxCount * 0x14 + 0x18) {
        // Crash/assert failure
        (**(code **)(*DAT_01205590 + 4))();
    }
    
    // Build a 32-bit key from four bytes in the buffer header (offsets +4, +8, +0xC, +0x10)
    int key = ((buf->byte1 * 0x100 + buf->byte2) * 0x100 + buf->byte3) * 0x100 + buf->byte4;
    
    // Allocate or look up a chunk using the key (FUN_00599aa0 returns a pointer or 0)
    PacketChunk* chunk = FUN_00599aa0(this, key);
    if (chunk == 0) {
        (**(code **)(*DAT_01205590 + 4))(); // Crash
        return;
    }
    
    // Get the number of data elements (count) from buffer at +0x14
    int count = buf->maxCount; // Actually this is the count variable; it's stored at +0x14
    if ((uint)count > 0xffff) {
        (**(code **)(*DAT_01205590 + 4))(); // Crash: too many elements
    }
    
    short sCount = (short)count;
    if (sCount != 0) {
        // Initialize chunk fields:
        chunk->field48 = 0;              // +0x48: reserved/state
        chunk->field4c = 1;              // +0x4c: short, some flag
        chunk->field4e = sCount;         // +0x4e: short length (number of elements)
        chunk->field54 = (int)(buf + 0x18); // +0x54: pointer to start of data array
        chunk->field50 = 2;              // +0x50: short type (chunk type 2)
    }
    
    // Clear bottom two bits of flags at +0x10 (likely mark chunk as ready/sent)
    chunk->flags &= 0xFFFFFFFA;
}
// Note: The global DAT_01205590 is likely an error handler pointer (similar to an assertion macro).
// The actual structure offsets and field names are deduced from the decompiled logic.