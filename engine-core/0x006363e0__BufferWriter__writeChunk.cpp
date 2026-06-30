// FUNC_NAME: BufferWriter::writeChunk
// Address: 0x006363e0
// Writes a chunk into a packet buffer: a 4‑byte type (0x04) and a 4‑byte value.
// If remaining capacity is less than 9 bytes, calls flushBuffer().
// The string argument is unused (likely a debugging artifact or compiler residue).
// Returns 1 on success.

int __fastcall BufferWriter::writeChunk(BufferWriter* this, const char* /* unused */) {
    // Member offsets:
    // +0x08: current write pointer (char*)
    // +0x14: pointer to start of buffer (char*) – base address of writable region
    // +0x18: pointer to end of buffer (char*) – capacity limit

    // Retrieve base buffer address
    char* bufferStart = *reinterpret_cast<char**>(reinterpret_cast<char*>(this) + 0x14);
    *reinterpret_cast<char**>(reinterpret_cast<char*>(this) + 0x8) = bufferStart;

    // Write chunk type
    *reinterpret_cast<uint32_t*>(bufferStart) = 4;

    // Compute and write chunk value (likely a hash, sequence number, or ID)
    uint32_t chunkValue = getChunkValue(); // FUN_00638920
    *reinterpret_cast<uint32_t*>(bufferStart + 4) = chunkValue;

    // Check remaining capacity (8 bytes for this chunk + 1 byte overhead? actual condition: < 9)
    char* bufferEnd = *reinterpret_cast<char**>(reinterpret_cast<char*>(this) + 0x18);
    if (bufferEnd - bufferStart < 9) {
        flushBuffer(); // FUN_00635c70 – flushes or expands buffer
    }

    // Advance write pointer by size of written chunk (8 bytes)
    *reinterpret_cast<char**>(reinterpret_cast<char*>(this) + 0x8) = bufferStart + 8;

    return 1;
}