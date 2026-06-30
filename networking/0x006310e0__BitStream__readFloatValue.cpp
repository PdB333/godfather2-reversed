// FUNC_NAME: BitStream::readFloatValue
// Address: 0x006310e0
// Role: Reads a float value from the stream, handling compressed and normal representations.
//        Uses a sentinel value to skip invalid entries.

#include <cstdint>

// External functions (declared elsewhere)
extern bool decodeCompressedFloat(float& outValue); // FUN_00636850
extern void debugPrint(const char* msg); // FUN_00627ac0 (prints "number" message)
extern void applyFloatConversion(); // FUN_00b9b988 (likely sets FPU mode or rounds float)

// Sentinel value used to mark invalid/empty entries
const float kInvalidFloat = 0.0f; // TODO: Replace with actual DAT_00e2b05c value if known

// Structure fields:
// +0x00: unknown (not used in this function)
// +0x04: unknown
// +0x08: uint8_t* writePtr (current write position in the output buffer)
// +0x0C: uint8_t* readPtr (current read position in the input buffer)
struct BitStreamBuffer {
    // ... other fields ...
    uint8_t* writePtr;   // offset +0x08
    uint8_t* readPtr;    // offset +0x0C
};

// Returns 1 on success, 0 on failure or when no valid float is found.
// Reads a 4-byte type tag and a 4-byte value from the stream.
// Type 3 = normal float, Type 4 = compressed float (decoded via decodeCompressedFloat).
// If the read value equals the sentinel, it discards it and tries the next entry.
void BitStream::readFloatValue(BitStreamBuffer* buf) {
    int* readPtr = reinterpret_cast<int*>(buf->readPtr);
    int* writePtr = reinterpret_cast<int*>(buf->writePtr);

    // If no data available, set result to zero and fall through to write a zero value.
    if (writePtr <= readPtr || readPtr == nullptr) {
        goto writeZero;
    }

    int type = *readPtr;
    float value;

    if (type == 3) {
        // Normal float: value is stored directly after type
        value = *reinterpret_cast<float*>(readPtr + 1);
    } else if (type == 4) {
        // Compressed float: decode via helper
        if (!decodeCompressedFloat(value)) {
            goto writeZero;
        }
        // Re-point readPtr to a temporary stack location so the following code
        // can use the same extraction logic.
        // (This is a workaround in decompiled code.)
        int dummyType = 3;
        float dummyValue = value;
        readPtr = &dummyType; // use stack as "readPtr"
    } else {
        goto writeZero;
    }

    // Now readPtr[1] is the float value (either from buffer or from local stack)
    value = reinterpret_cast<int*>(readPtr)[1];

    // Check for sentinel value (empty slot). If found, skip this entry.
    if (value == kInvalidFloat) {
        // Loop until we find a valid entry
        while (true) {
            readPtr = reinterpret_cast<int*>(buf->readPtr);
            if (writePtr <= readPtr || readPtr == nullptr) {
                // No more data, break with zero
                debugPrint("number");
                value = 0.0f;
                goto writeZero;
            }
            type = *readPtr;
            if (type == 3) {
                break; // valid normal float
            } else if (type == 4) {
                if (decodeCompressedFloat(value)) {
                    // Decoded successfully, will use this value
                    break;
                }
            }
            // Invalid type or decode failed: skip and continue
            debugPrint("number");
        }
    }

    // Write the output: type tag 3 and the float value
    writePtr = reinterpret_cast<int*>(buf->writePtr);
    *writePtr = 3;
    applyFloatConversion(); // some FPU operation
    reinterpret_cast<float*>(writePtr)[1] = static_cast<float>(static_cast<double>(value));
    buf->writePtr = reinterpret_cast<uint8_t*>(writePtr + 2); // advance by 8 bytes
    return 1;

writeZero:
    // Write a zero float value
    writePtr = reinterpret_cast<int*>(buf->writePtr);
    *writePtr = 3;
    applyFloatConversion();
    reinterpret_cast<float*>(writePtr)[1] = 0.0f;
    buf->writePtr = reinterpret_cast<uint8_t*>(writePtr + 2);
    return 1;
}