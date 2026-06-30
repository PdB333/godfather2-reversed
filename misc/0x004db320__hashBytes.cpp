// FUNC_NAME: hashBytes
// Function address: 0x004db320
// Role: Simple hash function using multiplier 0x1003f over a byte buffer.
// Used extensively for hashing data (likely strings or packet data) in the EARS engine.
// Callers: multiple locations in networking, streaming, etc.

int hashBytes(const unsigned char* data, int length)
{
    int hash = 0;
    if (data != nullptr && length > 0) {
        const unsigned char* end = data + length;
        do {
            unsigned char ch = *data;
            data++;
            hash = hash * 0x1003f + ch;
        } while (data < end);
    }
    return hash;
}