// FUNC_NAME: BitStream::writeCompressedFloat
// Reconstructed from Ghidra decompilation at 0x00632010
// This function reads a float from the stream buffer and writes it
// in a compressed format: mantissa and exponent stored as two floats.
// It handles two type tags: 3 (inline float) and 4 (referenced float via external read).

#include <cmath> // for frexp

// Constants (from data references)
static const float SENTINEL_FLOAT = *(float*)0x00e2b05c; // 0.0 or Infinity? Used as no-op skip
static const char* ERR_MSG = (char*)0x00e2a8a8; // "number"

// Forward declarations
bool readFloat(void* context, float& outFloat); // FUN_00636850
void logError(const char* msg); // FUN_00627ac0

int BitStream::writeCompressedFloat(void* thisPtr)
{
    // thisPtr layout:
    // +0x08 : mWritePtr  (pointer to current write position in buffer)
    // +0x0c : mReadPtr   (pointer to current read position in buffer)
    // Buffer entries are 8-byte pairs: [type (int)] [value (float)]

    int* readPos = *(int**)((int)thisPtr + 0x0c);
    float value;
    int readExponent; // Actually local_4c[0] used as exponent output
    int* tempFlags;   // alias for local_4c+1

    // --- Stage 1: Read a float from the stream ---
    // Check if there is data to read (readPos < mWritePtr)
    if (*(int**)((int)thisPtr + 0x08) <= readPos)
        goto cannotRead;
    if (readPos == NULL)
        goto cannotRead;

    if (*readPos == 3) // Type 3: inline float follows
    {
        // read the float value directly
        value = *(float*)(readPos + 1);
    }
    else if (*readPos == 4) // Type 4: externally referenced float
    {
        int readOk;
        float externalFloat;
        readOk = readFloat(thisPtr, externalFloat); // FUN_00636850
        if (readOk == 0)
            goto cannotRead;
        tempFlags = (int*)&readExponent + 1; // point to local_4c[1]
        *tempFlags = 3; // set type for potential later use? Unclear.
        value = externalFloat;
        readPos = tempFlags; // reuse read pointer to skip this entry? Actually overwritten below.
    }
    else
    {
        goto cannotRead; // Unknown type
    }

    // Read the actual float from the pointer (already set above for type 3)
    value = (float)readPos[1]; // This statement is redundant for type 3 but present

    // --- Stage 2: Skip sentinel values ---
    if (value == SENTINEL_FLOAT)
    {
        while (true)
        {
            // Refresh readPos from context
            readPos = *(int**)((int)thisPtr + 0x0c);
            if (*(int**)((int)thisPtr + 0x08) <= readPos || readPos == NULL)
                goto cannotRead;
            if (*readPos == 3)
                break; // Valid inline float
            if (*readPos == 4)
            {
                int readOk2;
                readOk2 = readFloat(thisPtr, &value);
                if (readOk2 != 0)
                    break; // Valid referenced float
            }
            // Invalid data: log error and try again
            logError(ERR_MSG);
        }
    }

    // --- Stage 3: Decompose float into mantissa and exponent using frexp ---
    double dVal = (double)value;
    int exponent;
    double mantissa = frexp(dVal, &exponent); // _frexp returns mantissa in [0.5, 1.0)

    // Write the mantissa as a float with type tag 3
    int* writePtr = *(int**)((int)thisPtr + 0x08);
    writePtr[0] = 3;          // type tag
    writePtr[1] = (int)mantissa; // mantissa as float (cast via int? Actually it's written as float)
    // Increment write pointer by 8 bytes
    *(int*)((int)thisPtr + 0x08) += 8;

    // Write the exponent as a float with type tag 3
    writePtr = *(int**)((int)thisPtr + 0x08);
    writePtr[0] = 3;
    writePtr[1] = (float)exponent;
    // Increment write pointer by 8 bytes
    *(int*)((int)thisPtr + 0x08) += 8;

    return 2; // Number of items written (mantissa + exponent)

cannotRead:
    value = 0.0f;
    return 0; // Signal failure
}