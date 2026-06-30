// FUNC_NAME: BitStream::readFloat
// Address: 0x0062a9e0
// Reconstructed C++ for The Godfather 2 (EARS engine, x86)

// Forward declarations of internal functions
bool readPackedInt(BitStream* stream);
void overflowError();
void errorPrint(const char* message);

// Constants
static const float ROUNDING_CONSTANT = 0.5f; // or DAT_00e44578 = 0.5f

// BitStream state structure (incomplete, only known offsets)
struct BitStreamState {
    int field_0x00;       // unknown
    int field_0x04;       // unknown
    int field_0x08;       // unknown
    int field_0x0c;       // unknown
    int field_0x10;       // unknown
    int field_0x14;       // unknown
    int field_0x18;       // unknown
    int field_0x1c;       // unknown
    int readCount;        // +0x20
    int bitCount;         // +0x24
};

// BitStream class partial definition
class BitStream {
public:
    int* mReadPtr;        // +0x04? Actually offset not specified, but used as this+0x0 is something else; we'll define fields based on decompile.
    // In the decompile, offsets are:
    // +0x08: end pointer (mEndPtr)
    // +0x0c: current read pointer (mReadPtr)
    // +0x10: pointer to BitStreamState (mState)
    // To keep offsets as comments, we'll define fields with appropriate names.
    // Let's define an anonymous struct layout:
    // offset 0x00: unknown (maybe vtable?)
    // offset 0x04: unknown
    // offset 0x08: int* mEndPtr;
    // offset 0x0c: int* mReadPtr;
    // offset 0x10: BitStreamState* mState;
};

// Note: offset +0x00 and +0x04 are not used in this function, but we preserve them.

// Decompiled function reconstruction
unsigned int BitStream::readFloat() {
    int* mReadPtr = *(int**)(this + 0xc);  // +0xc: current read position pointer
    int* mEndPtr = *(int**)(this + 0x8);   // +0x8: end of readable data
    BitStreamState* state = *(BitStreamState**)(this + 0x10); // +0x10: state structure

    int rawValue;

    // --- First attempt: read a compressed integer? ---
    if (mReadPtr < mEndPtr && mReadPtr != nullptr) {
        if (*mReadPtr == 4) {
            // Tag 4: direct value at offset 0x10 from the indirect pointer
            rawValue = mReadPtr[1] + 0x10;
        }
        else {
            int success = readPackedInt(this);  // variant-length int decode
            if (success != 0) {
                rawValue = mReadPtr[1] + 0x10;
            }
            else {
                rawValue = 0;
            }
            // Overflow check
            if (state->readCount <= state->bitCount) {
                overflowError();
            }
        }
        if (rawValue == 0) {
            goto error;
        }
    }
    else {
error:
        errorPrint("BitStream::readFloat: Not enough data or invalid pointer");
    }

    // --- Second attempt: re-read the same position? (likely reads the actual float value) ---
    mReadPtr = *(int**)(this + 0xc); // re-read pointer
    if (mReadPtr < mEndPtr && mReadPtr != nullptr) {
        if (*mReadPtr == 4) {
            rawValue = *(int*)(mReadPtr[1] + 0xc);  // read from indirect offset 0xc
        }
        else {
            int success = readPackedInt(this);
            if (success != 0) {
                rawValue = *(int*)(mReadPtr[1] + 0xc);
            }
            else {
                rawValue = 0;
            }
        }
    }
    else {
        rawValue = 0;
    }

    // Write the float result to output buffer (pointed by mEndPtr? no, mEndPtr is used as write pointer)
    // Actually the output buffer is at this+0x8 (same as mEndPtr). This is unusual; perhaps this function
    // writes into the same buffer? Or maybe mEndPtr is overloaded as write pointer during output?
    // Assuming an output region at this+0x8.
    float* outputPtr = (float*)*(int**)(this + 0x8);
    *outputPtr = 3.0f;   // write a tag? constant 3
    float value = (float)rawValue;
    if (rawValue < 0) {
        value += ROUNDING_CONSTANT;  // rounding for negative fixed-point?
    }
    outputPtr[1] = value;
    // Advance output pointer
    *(int*)(this + 0x8) = (int)outputPtr + 8;

    return 1;
}