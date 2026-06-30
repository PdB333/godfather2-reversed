// FUNC_NAME: AnimationDecoder::decodeFrameData

// 0x0057a900 - Decodes animation frame data from a compressed bitstream.
// Reads bone transforms (8 floats per bone) and optionally extra data (4 floats).
// Uses variable-length nibble-based offset encoding for stream navigation.
// Handles interpolation between frames based on fractional time component.

#include <cstdint>

// Forward declarations of helper functions (implemented elsewhere)
float* allocateBuffer(int count);          // 0x0056ef10
float readFloatFromStream(byte** stream, float time); // 0x00579aa0
float readFloatFromStreamWithTime(byte** stream, float time, int frame); // 0x0057a240
void skipFloat();                          // 0x00579a50
float* allocateFloatArray(int count);      // 0x00580b40
float* allocateOtherBuffer(int count);     // 0x005807d0

// Constants (from data section)
const float ONE = 1.0f;                    // DAT_00e2b1a4
const float FRAC_THRESHOLD = 0.5f;         // DAT_00e2e780 (example value)
const int DECODE_TABLE_MULT[16] = { ... }; // DAT_00e2c758
const int DECODE_TABLE_ADD[16] = { ... };  // DAT_00e2c720

// Decodes a variable-length offset from the bitstream using nibble-based encoding.
// Returns the number of bytes to advance.
static int decodeOffset(byte* stream) {
    uint8_t nibble = *stream & 0x0F;
    if (nibble == 5) {
        // Special case: next 2 bytes are the offset
        return *(uint16_t*)(stream + 2);
    } else {
        // Use tables: offset = mult[nibble] * (high nibble of next byte) + add[nibble]
        uint8_t nextByte = *(stream + 1);
        uint8_t highNibble = (nextByte >> 4) | ((*stream >> 4) << 4); // Actually: (stream[1] << 4) | (stream[0] >> 4)
        // Correction: The original code does: ((uint)pbVar6[1] << 4 | (uint)(*pbVar6 >> 4))
        // So it's (stream[1] << 4) | (stream[0] >> 4)
        uint8_t combined = (stream[1] << 4) | (stream[0] >> 4);
        return DECODE_TABLE_MULT[nibble] * combined + DECODE_TABLE_ADD[nibble];
    }
}

// Advances the stream pointer by following a chain of offsets.
static byte* advanceStream(byte* stream, int steps) {
    for (int i = 0; i < steps; ++i) {
        uint8_t nibble = *stream & 0x0F;
        int offset = decodeOffset(stream);
        stream += offset;
        // Continue with next nibble at new position
        // The original code does multiple levels of indirection (up to 7 levels)
        // This is a simplified version; actual implementation repeats the pattern.
    }
    return stream;
}

// Main function
int AnimationDecoder::decodeFrameData(int* param_1) {
    // param_1 is a struct: [owner, data, time, numBones, numFrames, numExtra]
    void* owner = (void*)param_1[0];
    byte* data = (byte*)param_1[1];
    float time = *(float*)&param_1[2];
    int numBones = param_1[3];
    int numFrames = param_1[4];
    int numExtra = param_1[5];

    // Split time into integer and fractional parts
    int frame = (int)time;
    float frac = time - (float)frame;

    // Determine which data pointer to use based on some flag in data structure
    byte* stream;
    if ((*(uint32_t*)(data + 4) & 0xFF) < 10) {
        stream = *(byte**)(data + 0x24);
    } else {
        stream = *(byte**)(data + 0x2C);
    }

    // Determine if we need to interpolate (frac > threshold) and compute complement
    float invFrac = ONE - frac;
    bool interpolate = false;
    float fracUsed = frac;
    if (FRAC_THRESHOLD < frac) {
        if (FRAC_THRESHOLD < invFrac) {
            interpolate = true;
            fracUsed = invFrac;
        } else {
            // Move to next frame
            frame++;
            time = (float)frame;
            frac = 0.0f;
            invFrac = ONE;
            interpolate = false;
        }
    } else {
        frac = 0.0f;
        invFrac = ONE;
        interpolate = false;
        time = (float)frame;
    }

    // Get or allocate bone transform buffer (8 floats per bone)
    float* boneBuffer = *(float**)(*(int*)owner + 0x38);
    if (boneBuffer == nullptr) {
        boneBuffer = allocateBuffer(numBones);
        *(float**)(*(int*)owner + 0x38) = boneBuffer;
    }
    float* boneOut = boneBuffer + 0x10; // Skip header? Actually +0x10 from allocated block

    // Get type indicator array (at owner+0x34 + 0x14)
    char* typeIndicators = (char*)(*(int*)(*(int*)owner + 0x34) + 0x14);

    // Determine which data pointer to use for reading (based on same flag)
    byte* dataPtr;
    if ((*(uint32_t*)(data + 4) & 0xFF) < 10) {
        dataPtr = *(byte**)(data + 0x20);
    } else {
        dataPtr = *(byte**)(data + 0x28);
    }

    // Check if dataPtr is negative (meaning we need to read from stream)
    if ((int)dataPtr < 0) {
        // Read bone transforms
        for (int i = 0; i < numBones; ++i) {
            if (typeIndicators[i] == 0x02) {
                // Read 7 floats for bone transform (position, rotation, scale?)
                if (interpolate) {
                    boneOut[0] = readFloatFromStream(&stream, time);
                    boneOut[1] = readFloatFromStream(&stream, time);
                    boneOut[2] = readFloatFromStream(&stream, time);
                    boneOut[3] = readFloatFromStream(&stream, time);
                    boneOut[4] = readFloatFromStream(&stream, time);
                    boneOut[5] = readFloatFromStream(&stream, time);
                    boneOut[6] = readFloatFromStream(&stream, time);
                    boneOut[7] = ONE; // w component?
                } else {
                    boneOut[0] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[1] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[2] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[3] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[4] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[5] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[6] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[7] = ONE;
                }
            } else if (typeIndicators[i] != 0x00) {
                // Skip 7 floats (unknown type)
                skipFloat();
                skipFloat();
                skipFloat();
                skipFloat();
                skipFloat();
                skipFloat();
                skipFloat();
            }
            boneOut += 8;
            stream = stream; // local_c updated inside read functions
        }

        // Now read extra data (if any)
        if (numExtra > 0) {
            // Advance stream by (numFrames - numBones) steps? Actually the loop uses param_1[4] - param_1[3]
            int steps = numFrames - numBones;
            for (int j = 0; j < steps; ++j) {
                // Complex nibble-based stream navigation (simplified)
                stream = advanceStream(stream, 7); // 7 levels of indirection
            }

            // Get or allocate extra data buffer
            float* extraBuffer = *(float**)(*(int*)owner + 0x40);
            if (extraBuffer == nullptr) {
                extraBuffer = allocateFloatArray(numExtra);
                *(float**)(*(int*)owner + 0x40) = extraBuffer;
            }
            float* extraOut = extraBuffer + 0x10;

            // Read extra floats
            for (int k = 0; k < numExtra; ++k) {
                if (interpolate) {
                    readFloatFromStream(&stream, time);
                } else {
                    readFloatFromStreamWithTime(&stream, time, frame);
                }
                *extraOut = fracUsed; // Actually the original stores fVar15 (which is fracUsed or 0)
                extraOut++;
            }
        }
    } else {
        // dataPtr >= 0: use a different buffer (at owner+0x3c)
        float* otherBuffer = *(float**)(*(int*)owner + 0x3C);
        if (otherBuffer == nullptr) {
            otherBuffer = allocateOtherBuffer(numBones);
            *(float**)(*(int*)owner + 0x3C) = otherBuffer;
        }
        float* otherOut = otherBuffer + 0x10;

        // Read both bone transforms and extra data simultaneously
        for (int i = 0; i < numBones; ++i) {
            if (typeIndicators[i] == 0x02) {
                if (interpolate) {
                    boneOut[0] = readFloatFromStream(&stream, time);
                    boneOut[1] = readFloatFromStream(&stream, time);
                    boneOut[2] = readFloatFromStream(&stream, time);
                    boneOut[3] = readFloatFromStream(&stream, time);
                    boneOut[4] = readFloatFromStream(&stream, time);
                    boneOut[5] = readFloatFromStream(&stream, time);
                    boneOut[6] = readFloatFromStream(&stream, time);
                    boneOut[7] = ONE;
                    otherOut[0] = readFloatFromStream(&stream, time);
                    otherOut[1] = readFloatFromStream(&stream, time);
                    otherOut[2] = readFloatFromStream(&stream, time);
                    otherOut[3] = ONE;
                } else {
                    boneOut[0] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[1] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[2] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[3] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[4] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[5] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[6] = readFloatFromStreamWithTime(&stream, time, frame);
                    boneOut[7] = ONE;
                    otherOut[0] = readFloatFromStreamWithTime(&stream, time, frame);
                    otherOut[1] = readFloatFromStreamWithTime(&stream, time, frame);
                    otherOut[2] = readFloatFromStreamWithTime(&stream, time, frame);
                    otherOut[3] = ONE;
                }
            } else if (typeIndicators[i] != 0x00) {
                // Skip 10 floats (7 bone + 3 extra)
                skipFloat(); skipFloat(); skipFloat(); skipFloat(); skipFloat();
                skipFloat(); skipFloat(); skipFloat(); skipFloat(); skipFloat();
            }
            boneOut += 8;
            otherOut += 4;
            stream = stream;
        }

        // Read extra data (similar to above)
        if (numExtra > 0) {
            int steps = numFrames - numBones;
            for (int j = 0; j < steps; ++j) {
                stream = advanceStream(stream, 7);
            }

            float* extraBuffer = *(float**)(*(int*)owner + 0x40);
            if (extraBuffer == nullptr) {
                extraBuffer = allocateFloatArray(numExtra);
                *(float**)(*(int*)owner + 0x40) = extraBuffer;
            }
            float* extraOut = extraBuffer + 0x10;

            for (int k = 0; k < numExtra; ++k) {
                if (interpolate) {
                    readFloatFromStream(&stream, time);
                } else {
                    readFloatFromStreamWithTime(&stream, time, frame);
                }
                *extraOut = fracUsed;
                extraOut++;
            }
        }
    }

    return 1; // Success
}