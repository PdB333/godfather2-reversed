// FUNC_NAME: hashBuffer
// Function address: 0x004db3f0
// Role: Generic data hash function using multiplier 0x1003f (65599). Used for networking/replication checksums.
// Computes: hash = hash * 65599 + byte for each byte in data.

uint32_t hashBuffer(uint32_t initialHash, const uint8_t* data, int length)
{
    if (data && (length > 0))
    {
        const uint8_t* end = data + length;
        do
        {
            uint8_t b = *data++;
            initialHash = initialHash * 0x1003f + b;
        } while (data < end);
    }
    return initialHash;
}