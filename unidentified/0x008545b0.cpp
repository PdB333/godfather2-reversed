// FUN_NAME: BitStreamReader::readFlagPairWithOptionalObject

// Reads two boolean flags from the bitstream, then optionally reads an object if the second flag is true.
// The object type (at +0x14) is checked; if 0 or 0x48, the second flag is cleared.
struct BitStreamReader {
    uint8_t* mBuffer;     // +0x0c
    uint32_t mBitOffset;  // +0x18
    uint8_t mOverflowFlag;// +0x1c
    uint32_t mTotalBits;  // +0x2c
};

struct ReadResult {
    bool mFlag0;   // +0x0c
    bool mFlag1;   // +0x0d
    void* mObject; // +0x10
};

// Forward declaration – reads an object from the stream, stores pointer at *out
extern void readObjectFromStream(BitStreamReader* stream, void** out);

void BitStreamReader::readFlagPairWithOptionalObject(ReadResult* result) {
    // Pre‑read setup (e.g., initial alignment or validation)
    FUN_004a9c90(this, result); // detailed behavior unknown

    // ---- Read first flag ----
    uint32_t bitPos = mBitOffset;
    if (bitPos >= mTotalBits) {
        mOverflowFlag = 1;
        result->mFlag0 = false;
    } else {
        uint8_t byteVal = *(mBuffer + (bitPos >> 3));
        result->mFlag0 = (byteVal & (1 << (bitPos & 7))) != 0;
        mBitOffset = bitPos + 1;
    }

    // ---- Read second flag ----
    bitPos = mBitOffset;
    if (bitPos >= mTotalBits) {
        mOverflowFlag = 1;
        result->mFlag1 = false;
    } else {
        uint8_t byteVal = *(mBuffer + (bitPos >> 3));
        result->mFlag1 = (byteVal & (1 << (bitPos & 7))) != 0;
        mBitOffset = bitPos + 1;
    }

    // If second flag was set, read an object and validate its type
    if (result->mFlag1) {
        readObjectFromStream(this, &result->mObject);
        int32_t objectType = *(int32_t*)(result->mObject + 0x14);
        // 0x48 is likely a “null” or “invalid” ghost ID
        if (objectType == 0 || objectType == 0x48) {
            result->mFlag1 = false;
        }
    }
}