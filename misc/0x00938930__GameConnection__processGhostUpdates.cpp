// FUNC_NAME: GameConnection::processGhostUpdates
// 0x00938930 - Processes a stream of ghost entity updates from a network packet buffer.
// Each iteration reads a fixed-size header (1 byte?), then a variable-length data chunk, and calls a callback stored somewhere.

// Assume: This is a member function of GameConnection (or derived from NetConnection).
// The packet buffer layout: [4 bytes unused] [4 bytes count] [variable data]
// The variable data consists of items: each has a 1-byte header (read by FUN_004d3bc0), then a counted data block (read by FUN_004d3b50).

// Forward declarations for internal functions (renamed for clarity)
void beginPacketProcessing(); // FUN_009386b0
void readGhostHeader(int dataPtr); // FUN_004d3bc0
int readGhostData(int *outDataPtr); // FUN_004d3b50 - reads length & data pointer, returns length
void finalizeGhostItem(); // FUN_00938890 - after processing each item

// The callback pointer is stored in the GameConnection object at offset ? (local_4 was uninitialized in decomp, but likely from a member variable)
// We'll assume it's at a known offset, e.g., +0x1C (callback function pointer)

// Max number of ghost updates per packet (common in TNL)
#define MAX_GHOST_UPDATES 300

struct PacketBuffer {
    int unknown;      // +0x00
    int itemCount;    // +0x04   number of items to process
    char data[1];     // +0x08   start of item data (flexible array)
};

int __thiscall GameConnection::processGhostUpdates(void* this, PacketBuffer* buffer) {
    int dataOffset = (int)&buffer->data[0];
    uint processedCount = 0;

    beginPacketProcessing();

    if (buffer->itemCount == 0) {
        return 1;
    }

    do {
        if (processedCount > MAX_GHOST_UPDATES - 1) {
            return 1; // safety cap
        }

        // Read the fixed header for this ghost item (typically a ghost ID or flags)
        readGhostHeader(dataOffset);

        // Read the variable-length data: sets localDataPtr and returns data length
        int localDataPtr;
        int dataLength = readGhostData(&localDataPtr); // local_c = dataLength

        // Notify ? the callback (originally local_4, likely stored in the object)
        // We'll assume it's retrieved from a member field, e.g., this+0x1C
        void (*callback)(int) = *(void (**)(int))((char*)this + 0x1C);
        finalizeGhostItem(); // post-processing per item

        // Advance the data pointer by 1 (header) + dataLength
        dataOffset = dataOffset + 1 + dataLength;

        if (localDataPtr != 0 && callback != 0) {
            callback(localDataPtr);
        }

        processedCount++;
    } while (processedCount < (uint)buffer->itemCount);

    return 1;
}