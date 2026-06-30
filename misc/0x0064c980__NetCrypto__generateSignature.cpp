// FUNC_NAME: NetCrypto::generateSignature
// Address: 0x0064c980
// Role: Generates a message authentication code (HMAC-SHA256) for a network packet.
// Fields:
//   +0x0c: uint8_t* dataBuffer         // pointer to the start of the data to be signed
//   +0x18: uint32_t bitCount           // total number of bits processed so far (rounded to byte boundary here)

class NetCrypto {
    // other fields omitted
    uint8_t* dataBuffer;       // +0x0c
    uint32_t bitCount;         // +0x18

    // Internal helper functions (Ghidra names preserved for clarity)
    void initHash(void* context);                     // FUN_006595c0
    void updateHash(void* context, void* data, uint32_t len); // FUN_00659640
    void finalizeHash(void* context, void* outHash);   // FUN_00659730
    void applyHashKey(uint32_t keyLen, void* hash);    // FUN_0064b810 (likely HMAC-SHA256 with key of 0x28 bytes)
    void copyData(void* dest, void* src, uint32_t size); // FUN_0065a740 (assumed memcpy or XOR)

public:
    void generateSignature(int dataOffset, uint8_t* outputSignature) {
        uint32_t byteCount;
        uint8_t hashContext[212];   // local_d4, size from context structure
        uint8_t hashDigest[32];     // local_f4, 32 bytes for SHA256

        // Round bit count up to the next byte boundary
        byteCount = (bitCount + 7) >> 3;
        bitCount = byteCount * 8;

        // Initialize hash context
        initHash(hashContext);

        // Feed the data buffer from the start up to the new byte count
        updateHash(hashContext, dataBuffer, byteCount);

        // Finalize the hash to produce a 32-byte digest
        finalizeHash(hashContext, hashDigest);

        // Apply a keyed hash (HMAC) with a fixed key of 0x28 bytes
        applyHashKey(0x28, hashDigest);

        // Write the signature (or remainder of data) starting at the output
        // Note: iVar1 = dataBuffer + dataOffset
        uint8_t* sourcePtr = dataBuffer + dataOffset;
        uint32_t remainingBytes = ((bitCount + 7) >> 3) - dataOffset;
        copyData(outputSignature, sourcePtr, remainingBytes);
    }
};