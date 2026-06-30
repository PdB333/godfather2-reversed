// FUNC_NAME: ChecksumAccumulator::accumulateBytes
// Address: 0x0066a010
// Reconstructed C++ function for accumulating bytes into a bitwise OR checksum (dword buffer).
// TNL networking layer, likely used for building a flag mask or simple checksum.
//
// Struct layout (16 bytes):
// +0x00: int byteCount
// +0x04: int capacity (number of dwords in buffer)
// +0x08: int flags (internal state)
// +0x0C: uint32* buffer (pointer to dword array, allocated externally)

class ChecksumAccumulator {
private:
    int byteCount;          // +0x00
    int capacity;           // +0x04
    int flags;              // +0x08
    uint32* buffer;         // +0x0C

    // Helper: ensures the accumulator has at least 2 dwords capacity (FUN_00667740)
    // Returns 0 on success, non-zero on error.
    int ensureMinCapacity();

    // Helper: performs per-byte validation/allocation (FUN_00668e40, called with argument 8)
    // Returns 0 on success, non-zero on error.
    int checkPerByte();

    // Finalization after accumulation (FUN_00665b10)
    void finalize();

public:
    // Main entry point: resets accumulator and ORs each byte from 'data' into buffer[0].
    // Returns 0 on success, error code otherwise.
    int accumulateBytes(const uint8* data, int count);
};

int ChecksumAccumulator::accumulateBytes(const uint8* data, int count) {
    // If the buffer capacity is less than 2 dwords, try to allocate more.
    if (capacity < 2) {
        int ret = ensureMinCapacity();
        if (ret != 0) {
            return ret;
        }
    }

    // Reset internal state and clear the buffer.
    flags = 0;
    byteCount = 0;
    memset(buffer, 0, capacity * 4);

    // Process each input byte.
    for (int i = 0; i < count; ++i) {
        // Per-byte validation (e.g., memory limit, slot availability).
        int ret = checkPerByte(); // always called with constant 8
        if (ret != 0) {
            return ret;
        }

        // OR the current byte into the first dword of the buffer.
        buffer[0] |= (uint32)(*data);
        byteCount++;
        data++;
    }

    finalize();
    return 0;
}