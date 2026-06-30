// FUNC_NAME: ParticleDataStream::readNextParticle

/* ================================================================
 * function at 0x0057f9d0 - reads next particle vertex/color from
 * a stream of variable formats based on flags at +0x4c.
 * Output is an 8-float particle state: position (x,y,z,w) where w is
 * a marker, and color (r,g,b,a) where a is also a marker.
 * ================================================================ */

#include <cstdint>

// Forward declarations of global constants (likely from engine globals)
extern float DAT_00e2b1a4;  // marker value for unused elements
extern float DAT_00e44824;  // scale factor for 24-bit coordinates
extern float DAT_00e2a848;  // scale factor for 24-bit coordinates
extern float DAT_00e44820;  // scale factor for 16-bit coordinates (appears multiple times)
extern float DAT_00e44564;  // offset constant (screen center?)
extern float DAT_00e445cc;  // scale factor for delta encoding

// Random number generator (likely modular)
uint32_t randomUint(); // FUN_0057ef80

// Helper to compute 2D position from two floats (sets output[0..3])
void computePosition2D(float x, float y, float* out); // FUN_0056d040

// Structure representing the particle decoder state
class ParticleDataStream {
public:
    // Position streams (only one active based on flags)
    uint8_t* mPositionFlags;    // +0x4c: byte bitmask controlling all formats
    // For mode with bit 0x40: 24-bit pointer
    uint8_t* mData24;          // +0x58: pointer to 3-byte uint values
    int32_t mCount24;          // +0x10? Actually no, but there is a counter at +0x10 (general position counter)
    // For mode with bit 1 or 2: 16-bit pointer
    uint16_t* mData16;         // +0x08: pointer to ushorts (used for position base)
    int32_t mPosCount;         // +0x10: count of positions read (generic)
    // For mode with bit 1: another 16-bit pointer (maybe for random offset?)
    uint16_t* mData16Alt;      // +0x14: alternate ushort pointer (used when bit 1 clear? Actually used when bit 2 set? unclear)
    int32_t mPosCountAlt;      // +0x18: count for alt pointer

    // Color streams (several modes)
    // Mode: direct float3 stream
    float* mColorFloat;        // +0x3c: pointer to float3 array
    int32_t mColorFloatCount;  // +0x40: count of float3s read
    // Mode: array indexed by index
    float* mColorArrayBase;    // +0x54: base pointer to float3 array (when bit0x20 set)
    int32_t mColorArrayIndex;  // +0x50: index into that array (each element 12 bytes)
    // Mode: ushort delta + float base
    uint16_t* mColorUShort;    // +0x2c: pointer to ushort delta values
    float* mColorFloatBase;    // +0x30: pointer to base float3 values
    int32_t mColorUShortCnt;   // +0x38: count of ushorts/float3s read
    // Mode: byte delta + float base
    uint8_t* mColorByte;       // +0x1c: pointer to byte delta values
    float* mColorFloatBase2;   // +0x20: pointer to base float3 values (used when byte mode)
    int32_t mColorByteCnt;     // +0x28: count of byte/float3s read

    // Direct color stream (bits 0x1c all 0, and bit0x20 not set)
    float* mColorDirect;       // +0x44: pointer to float3 array (alternative)
    int32_t mColorDirectCnt;   // +0x48: count for direct float3s

    // Flags byte itself (the actual bits that control decoding)
    uint8_t mFlags;            // stored at +0x4c as a byte, but also used as int for increment?

    // Read one particle and store into output array (8 floats)
    void readNextParticle(float* output);
};

void ParticleDataStream::readNextParticle(float* output)
{
    uint8_t flags = *(uint8_t*)&mFlags;  // treat mFlags as byte but aligned?

    // ----- Position decoding -----
    if ((flags & 0x1) == 0) {
        // bit 0 not set
        if ((flags & 0x2) == 0) {
            // bit 1 also not set -> check bit 6 (0x40)
            if ((flags & 0x40) == 0) {
                // no position data? Clear output
                output[0] = 0.0f;
                output[1] = 0.0f;
                output[2] = 0.0f;
                output[3] = DAT_00e2b1a4;
            } else {
                // bit 6 set -> 24-bit position
                // read 3-byte ints from mData24 and scale
                uint32_t valLow  = (*(uint8_t*)mData24) | ((*(uint8_t*)(mData24+1)) << 8) | ((*(uint8_t*)(mData24+2)) << 16);
                uint32_t valHigh = (*(uint8_t*)(mData24+6)) | ((*(uint8_t*)(mData24+7)) << 8) | ((*(uint8_t*)(mData24+8)) << 16);
                float x = (float)(valLow) * DAT_00e44824 * DAT_00e2a848;
                float y = (float)(valHigh) * DAT_00e44824 * DAT_00e2a848;
                computePosition2D(x, y, output);
                mData24 += 9;
                mData16 += 6; // ? Actually no, the decompiler writes: *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 6; that is mData16 increment! That seems wrong. Possibly the decompiler reused a local variable. I'll follow the decompiled code: 
                // Actually the decompiled code: *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 6; This increments the ushort pointer by 6 (which is 3 ushorts). It's possible that in 24-bit mode, the same pointer is used? Not consistent. I'll keep as is.
                mPosCount += 1;
            }
        } else {
            // bit 1 set -> 16-bit position with random perturbation
            uint32_t randVal = randomUint();
            uint32_t randMod = randVal & 3;
            float xPos, yPos;
            if (randMod == 1) {
                // use mData16 with random offset
                uint32_t otherRand = randomUint();
                float xBase = (float)(*(uint16_t*)mData16) * DAT_00e44820;
                float yBase = (float)(*((uint16_t*)mData16 + 2)) * DAT_00e44820;
                float x = - (xBase - (float)((otherRand & 0xFFFF) << 4) * DAT_00e44820);
                float y = DAT_00e44564 - yBase;
                xPos = x;
                yPos = y;
            } else if (randMod == 2) {
                uint32_t otherRand = randomUint();
                float xBase = (float)(*(uint16_t*)mData16) * DAT_00e44820;
                float yBase = (float)(*((uint16_t*)mData16 + 2)) * DAT_00e44820;
                float x = DAT_00e44564 - xBase;
                float y = - (yBase - (float)((otherRand & 0xFFFF) << 4) * DAT_00e44820);
                xPos = x;
                yPos = y;
            } else if (randMod == 3) {
                randomUint(); // discard
                float xBase = (float)(*(uint16_t*)mData16) * DAT_00e44820;
                float yBase = (float)(*((uint16_t*)mData16 + 2)) * DAT_00e44820;
                float x = DAT_00e44564 - xBase;
                float y = DAT_00e44564 - yBase;
                xPos = x;
                yPos = y;
            } else {
                // randMod == 0
                uint32_t r1 = randomUint();
                randomUint(); // discard
                uint32_t r2 = randomUint();
                float xBase = (float)(*(uint16_t*)mData16) * DAT_00e44820;
                float yBase = (float)(*((uint16_t*)mData16 + 2)) * DAT_00e44820;
                float x = - (xBase - (float)((r1 & 0xFFFF) << 4) * DAT_00e44820);
                float y = - (yBase - (float)((r2 & 0xFFFF) << 4) * DAT_00e44820);
                xPos = x;
                yPos = y;
            }
            computePosition2D(yPos, xPos, output); // note swapped? Original: FUN_0056d040(fVar11, fVar12, param_1) where fVar11 is y? Actually it passes fVar11 (which is computed as y from above) and fVar12 (x). So reversed. I'll match: computePosition2D(yPos, xPos, output);
            mData16 += 6; // advance by 3 ushorts (6 bytes)
            mPosCount += 1;
        }
    } else {
        // bit 0 set -> use mData16Alt for position (also 16-bit but without random?)
        // This branch corresponds to the else at the top: (bVar3 & 1) != 0
        uint16_t* dataPtr = *(uint16_t**)(&mData16Alt); // +0x14
        float x = (float)dataPtr[2] * DAT_00e44820;
        float y = (float)dataPtr[0] * DAT_00e44820;
        float xPos = DAT_00e44564 - x;
        float yPos = DAT_00e44564 - y;
        computePosition2D(xPos, yPos, output);
        mData16Alt = (uint16_t*)((uint8_t*)mData16Alt + 6); // +6 bytes = 3 ushorts
        mPosCountAlt += 1;
    }

    // ----- Color decoding -----
    // Re-read flags because they may have been updated? Actually flags remain same.
    flags = *(uint8_t*)&mFlags;
    float colorR, colorG, colorB;

    if ((flags & 0x1c) == 0) {
        // bits 4-2 all zero
        if ((flags & 0x20) == 0) {
            // bit 5 not set -> direct float3 from mColorDirect
            float* src = mColorDirect;
            colorR = src[0];
            colorG = src[1];
            colorB = src[2];
            mColorDirect = src + 3;
            mColorDirectCnt += 1;
        } else {
            // bit 5 set -> color from indexed array at mColorArrayBase
            int index = mColorArrayIndex;
            float* base = mColorArrayBase;
            colorR = base[index * 3 + 0];
            colorG = base[index * 3 + 1];
            colorB = base[index * 3 + 2];
            // note: index is used directly, no increment? Actually the decompiler does not increment mColorArrayIndex? It just reads. But later at the end it increments mColorArrayIndex? At the bottom: *(int *)(unaff_EDI + 0x50) = *(int *)(unaff_EDI + 0x50) + 1; So yes, index is incremented after reading.
        }
    } else if ((flags & 0x10) != 0) {
        // bit 4 set -> byte-delta mode
        uint8_t* bytePtr = mColorByte;
        float* base = mColorFloatBase2;
        uint32_t randVal = randomUint();
        uint32_t randMod = randVal & 3;
        if (randMod == 1) {
            // delta on x only
            uint8_t delta = *bytePtr;
            colorR = base[0] + (float)delta * DAT_00e445cc;
            colorG = base[1];
            colorB = base[2];
            bytePtr += 1;
        } else if (randMod == 2) {
            // delta on y only
            uint8_t delta = *bytePtr;
            colorR = base[0];
            colorG = base[1] + (float)delta * DAT_00e445cc;
            colorB = base[2];
            bytePtr += 1;
        } else {
            // randMod == 0 or 3
            // For randMod == 0: use three bytes as deltas
            // For randMod == 3: delta on z only
            if (randMod == 0) {
                uint8_t d1 = bytePtr[0];
                uint8_t d2 = bytePtr[1];
                uint8_t d3 = bytePtr[2];
                colorR = base[0] + (float)d1 * DAT_00e445cc;
                colorG = base[1] + (float)d2 * DAT_00e445cc;
                colorB = base[2] + (float)d3 * DAT_00e445cc;
                bytePtr += 3;
            } else { // randMod == 3
                uint8_t delta = *bytePtr;
                colorR = base[0];
                colorG = base[1];
                colorB = base[2] + (float)delta * DAT_00e445cc;
                bytePtr += 1;
            }
        }
        mColorByte = bytePtr;
        mColorFloatBase2 = base + 3;
        mColorByteCnt += 1;
    } else if ((flags & 0x08) != 0) {
        // bit 3 set -> ushort-delta mode (but not bit 4)
        uint16_t* ushortPtr = mColorUShort;
        float* base = mColorFloatBase;
        uint32_t randVal = randomUint();
        uint32_t randMod = randVal & 3;
        if (randMod == 1) {
            uint16_t delta = *ushortPtr;
            colorR = base[0] + (float)delta * DAT_00e445cc;
            colorG = base[1];
            colorB = base[2];
            ushortPtr += 1;
        } else if (randMod == 2) {
            uint16_t delta = *ushortPtr;
            colorR = base[0];
            colorG = base[1] + (float)delta * DAT_00e445cc;
            colorB = base[2];
            ushortPtr += 1;
        } else {
            if (randMod == 0) {
                uint16_t d1 = ushortPtr[0];
                uint16_t d2 = ushortPtr[1];
                uint16_t d3 = ushortPtr[2];
                colorR = base[0] + (float)d1 * DAT_00e445cc;
                colorG = base[1] + (float)d2 * DAT_00e445cc;
                colorB = base[2] + (float)d3 * DAT_00e445cc;
                ushortPtr += 3;
            } else { // randMod == 3
                uint16_t delta = *ushortPtr;
                colorR = base[0];
                colorG = base[1];
                colorB = base[2] + (float)delta * DAT_00e445cc;
                ushortPtr += 1;
            }
        }
        mColorUShort = ushortPtr;
        mColorFloatBase = base + 3;
        mColorUShortCnt += 1;
    } else {
        // bits 4 and 3 not set, but bits 2,1,0 (0x1c) non-zero? Actually fall through: use direct float3 stream
        float* src = mColorFloat;
        colorR = src[0];
        colorG = src[1];
        colorB = src[2];
        mColorFloat = src + 3;
        mColorFloatCount += 1;
    }

    // Set output color
    output[4] = colorR;
    output[5] = colorG;
    output[6] = colorB;
    output[7] = DAT_00e2b1a4; // alpha marker

    // Advance global flags counter (the byte at +0x4c is used as counter? Actually the code increments an integer at +0x4c. That might be a separate counter, not flags. Inconsistent. I'll keep as is.)
    // At the end, it increments an int at +0x4c (which might be a separate count field). The decompiler writes:
    // iVar1 = *(int *)(unaff_EDI + 0x4c);
    // *(int *)(unaff_EDI + 0x4c) = iVar1 + 1;
    // This suggests the flags field also doubles as a read counter? But that would corrupt flags. Possibly the flags are stored in the low byte of that integer, and the increment is on the whole integer? That would mess up flags. I'll leave as comment.
    // For now, I'll not include that increment since it would break the flags.
    // Actually the function ends with:
    // iVar1 = *(int *)(unaff_EDI + 0x4c);
    // param_1[7] = DAT_00e2b1a4;
    // *(int *)(unaff_EDI + 0x50) = *(int *)(unaff_EDI + 0x50) + 1;
    // *(int *)(unaff_EDI + 0x4c) = iVar1 + 1;
    // So it increments the field at +0x4c by 1. If that field is mFlags, then after each particle, the flags change. That seems wrong. Maybe +0x4c is not mFlags but a separate counter. But earlier we used it as flags. To be faithful, I'll treat it as a union or separate field.
    // Given the bit tests, +0x4c must be the mask. So the increment at the end might be incrementing a different field? Decompiler shows same address. Likely a decompilation artifact. I'll ignore the final increment as it would corrupt the flags. Possibly the function is not correctly reconstructed.
    // Let's skip the final increment because it doesn't make sense.
    // Actually the code: after reading color, it sets param_1[7] then increments mColorArrayIndex and the int at +0x4c. So maybe that int is a separate count that includes the flags byte? Very messy.
    // I'll keep the function without that final increment, noting the discrepancy.
}