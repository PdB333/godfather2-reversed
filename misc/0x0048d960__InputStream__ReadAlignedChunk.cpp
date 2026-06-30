// FUNC_NAME: InputStream::ReadAlignedChunk
// Address: 0x0048d960
// Role: Reads a 32-byte aligned chunk from an input stream buffer, updates the stream position, and calls a handler with the chunk and additional parameters.

#include <cstring>
#include <cstdint>

// InputStream class (partially reconstructed)
class InputStream {
public:
    // +0x18: current read pointer (may be unaligned)
    void* mReadPos;
};

// Callback function type: receives 32-byte block, an offset, size, and flag.
// The block is passed by value as four 64-bit values (or as a single 32-byte structure?).
// We define it as a function taking four uint64_t and then three ints.
typedef void (*ChunkHandler)(uint64_t chunk0, uint64_t chunk1, uint64_t chunk2, uint64_t chunk3,
                             uint32_t param5, int size, int flag);

// Reconstructed function
void __thiscall InputStream::ReadAlignedChunk(InputStream* this_, void* handlerTable)
{
    // Align current read pointer to next 4-byte boundary
    void* alignedBufferStart = (void*)((uint32_t)this_->mReadPos + 3U & 0xfffffffc);
    this_->mReadPos = alignedBufferStart;

    // Copy 32 bytes from aligned position into local buffer
    uint64_t chunk[4]; // 32 bytes
    memcpy(chunk, alignedBufferStart, 0x20);

    // Set read pointer to after the copied block
    this_->mReadPos = (void*)((uint8_t*)alignedBufferStart + 0x20);

    // Read two ints from the immediate next positions (after the block)
    int dataSize = *(int*)((uint8_t*)alignedBufferStart + 0x20);
    this_->mReadPos = (void*)((uint8_t*)alignedBufferStart + 0x24);
    int alignmentSize = *(int*)((uint8_t*)alignedBufferStart + 0x24);

    // Compute aligned offset based on alignmentSize (likely a power of 2)
    uint32_t alignedOffset = ((uint32_t)alignedBufferStart + (uint32_t)alignmentSize + 0x27) & ~((uint32_t)alignmentSize - 1U);

    // Update read pointer: after alignment and data size
    this_->mReadPos = (void*)((dataSize + 3U & 0xfffffffc) + alignedOffset);

    // Call the handler with the chunk and derived parameters
    // The first 4 parameters are the 32-byte block (split into 4 64-bit values)
    // last three: alignedOffset (or 0 if dataSize==0), dataSize, flag=1
    ChunkHandler handler = *(ChunkHandler*)handlerTable; // first entry in callback table
    handler(chunk[0], chunk[1], chunk[2], chunk[3],
            -(uint32_t)(dataSize != 0) & alignedOffset,
            dataSize,
            1);
}