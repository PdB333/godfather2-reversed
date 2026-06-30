// FUNC_NAME: StreamWriter::flushChunk
// Address: 0x00628940
// Role: Writes accumulated data chunk to output stream with type tag and size/checksum.

typedef unsigned int uint32_t;

// Forward declaration of the output stream class (likely from EA EARS engine)
struct OutputStream;

// Helper function to flush/buffer the output stream (FUN_00627360)
extern void flushOutputStream(OutputStream* stream);

// Helper function to write raw data to output stream and return a checksum/offset (FUN_00638920)
extern uint32_t writeStreamData(OutputStream* stream, const void* data, int size);

class StreamWriter {
    // +0x00: Pointer to next free byte in the internal data buffer (variable end pointer)
    int* mDataEnd;
    // +0x04: Counter for number of chunks written
    int mChunkCount;
    // +0x08: Pointer to the destination output stream manager
    OutputStream* mOutputStream;
    // +0x0C: Start of internal data buffer (variable size)

public:
    // Returns 1 on success, 0 if no data to write
    int flushChunk() {
        // Compute size of accumulated data: end pointer - base of object - header size (12 bytes)
        int dataSize = (int)mDataEnd - (int)this - 0xC;
        if (dataSize == 0) {
            return 0; // No data to write
        }

        OutputStream* out = mOutputStream;
        // Check if output buffer has space for at least 8 more bytes (type + result)
        // The structure at out+0x10 contains write position and capacity.
        // Current write position (at +0x20) >= capacity (at +0x24) ? Then flush buffer.
        if (*(uint32_t*)(*(int*)(out + 0x10) + 0x20) <= *(uint32_t*)(*(int*)(out + 0x10) + 0x24)) {
            flushOutputStream(out);
        }

        // Get current write pointer in the output stream (pointer to next free bytes)
        uint32_t* writePtr = *(uint32_t**)(out + 0x8);

        // Write chunk type identifier (4 = data chunk)
        *writePtr = 4;
        // Write the actual data and store returned value (likely checksum or offset)
        uint32_t result = writeStreamData(out, this + 3, dataSize); // this+3 points to data buffer at offset 0xC
        writePtr[1] = result;

        // Advance output write pointer by 8 bytes (type + result)
        *(int*)(out + 0x8) = *(int*)(out + 0x8) + 8;

        // Reset the internal data buffer to empty (mDataEnd points back to start of data area)
        mDataEnd = (int*)((char*)this + 0xC);
        // Increment chunk counter
        mChunkCount++;

        return 1;
    }
};