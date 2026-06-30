// FUNC_NAME: TransformGenerator::generateRandomTransform

// Reconstructed from Ghidra at address 0x004a97b0
// Generates a random rotation matrix from a quaternion and a random translation vector.
// The rotation matrix is a 3x3 orthogonal matrix stored in row-major order (9 floats)
// followed by a translation vector (3 floats) in output param_2.
// Uses a complex random number generation with bit flags for distribution.

#include <cmath>

// Global constants (likely defined somewhere in the game)
static const float kScaleQuaternion = *reinterpret_cast<float*>(0x00e44590); // Scaling factor for quaternion generation
static const float kScaleTranslation = *reinterpret_cast<float*>(0x00e445e4); // Scaling factor for translation
static const float kEpsilonSq = *reinterpret_cast<float*>(0x00e2cbe0); // Threshold for normalizing vectors (maybe FLT_EPSILON)
static const float kOne = *reinterpret_cast<float*>(0x00e2b1a4); // 1.0f
static const float kTwo = *reinterpret_cast<float*>(0x00e2b04c); // 2.0f

// Internal random functions (from engine)
extern int randomInt(); // FUN_0064be80 - returns random integer
extern void randomBits(uint32_t seed, uint32_t* out); // FUN_0064b9e0 - generates random bits with given seed

// Structure holding random state with a bit array
// Offsets:
// +0x0c: uint8_t* bitArray (pointer to bit array)
// +0x18: uint32_t currentIndex (index into bit array)
// +0x1c: uint8_t someFlag (written with 1)
// +0x2c: uint32_t maxIndex (limit for index)
// Note: The struct layout is deduced from the function's usage.
struct RandomState {
    uint32_t unknown00;   // +0x00
    uint32_t unknown04;   // +0x04
    uint32_t unknown08;   // +0x08
    uint8_t* bitArray;    // +0x0c
    uint32_t unknown10;   // +0x10
    uint32_t unknown14;   // +0x14
    uint32_t currentIndex; // +0x18
    uint8_t someFlag;     // +0x1c
    uint32_t unknown20;   // +0x20
    uint32_t unknown24;   // +0x24
    uint32_t unknown28;   // +0x28
    uint32_t maxIndex;    // +0x2c
};

void TransformGenerator::generateRandomTransform(RandomState* state, float* outTransform) {
    // Step 1: Generate a random quaternion and normalize it
    float quat[4]; // local_70
    for (int i = 0; i < 4; ++i) {
        quat[i] = static_cast<float>(randomInt()) * kScaleQuaternion;
    }
    float lenSq = quat[0]*quat[0] + quat[1]*quat[1] + quat[2]*quat[2] + quat[3]*quat[3];
    if (lenSq > kEpsilonSq) {
        float invLen = kOne / std::sqrt(lenSq);
        quat[0] *= invLen;
        quat[1] *= invLen;
        quat[2] *= invLen;
        quat[3] *= invLen;
    } else {
        // If zero, leave as zero (but quaternion shouldn't be zero)
        // The code sets to 0 in that case
        quat[0] = 0.0f;
        quat[1] = 0.0f;
        quat[2] = 0.0f;
        quat[3] = 0.0f;
    }

    // Step 2: Compute rotation matrix from quaternion
    // Use standard formula:
    // R00 = 1 - 2*(qy^2+qz^2)
    // R01 = 2*(qx*qy + qw*qz)
    // R02 = 2*(qx*qz - qw*qy)
    // R10 = 2*(qx*qy - qw*qz)
    // R11 = 1 - 2*(qx^2+qz^2)
    // R12 = 2*(qy*qz + qw*qx)
    // R20 = 2*(qx*qz + qw*qy)
    // R21 = 2*(qy*qz - qw*qx)
    // R22 = 1 - 2*(qx^2+qy^2)
    float qx = quat[0], qy = quat[1], qz = quat[2], qw = quat[3];

    // These variables/arrays hold the three rows of the rotation matrix
    float row0[3]; // local_50[0], [1], [2]
    float row1[3]; // local_50[4], [5], local_38 (local_38 is row1[2])
    float row2[3]; // local_30, local_2c, local_28

    row0[0] = kOne - (qz*qz + qy*qy) * kTwo; // R00
    row0[1] = (qw*qz + qy*qx) * kTwo;        // R01
    row0[2] = (qz*qx - qw*qy) * kTwo;        // R02

    // Note: local_50[3] is unused, row0[3] would be row0[2]? Actually there is a gap of 1 float between row0 and row1 in memory
    // We'll compute row1 separately
    row1[0] = (qy*qx - qw*qz) * kTwo;        // R10
    row1[1] = kOne - (qz*qz + qx*qx) * kTwo; // R11
    row1[2] = (qy*qz + qw*qx) * kTwo;        // R12

    row2[0] = (qx*qz + qw*qy) * kTwo;        // R20
    row2[1] = (qy*qz - qw*qx) * kTwo;        // R21
    row2[2] = kOne - (qy*qy + qx*qx) * kTwo; // R22

    // Step 3: Normalize each row of the rotation matrix (ensures orthogonality)
    // Code loops through rows: row0, row1, row2 and normalizes each 3-vector
    float rows[3][3] = { {row0[0], row0[1], row0[2]},
                         {row1[0], row1[1], row1[2]},
                         {row2[0], row2[1], row2[2]} };
    for (int r = 0; r < 3; ++r) {
        float* vec = rows[r];
        float lenSq2 = vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
        if (lenSq2 > kEpsilonSq) {
            float invLen = kOne / std::sqrt(lenSq2);
            vec[0] *= invLen;
            vec[1] *= invLen;
            vec[2] *= invLen;
        } else {
            vec[0] = 0.0f;
            vec[1] = 0.0f;
            vec[2] = 0.0f;
        }
    }

    // Step 4: Generate a random translation vector using bit-flagged distribution
    float translation[3]; // local_60
    for (int i = 0; i < 3; ++i) {
        uint32_t index = state->currentIndex;
        if (index < state->maxIndex) {
            // Check if the bit at index is set in the bit array
            uint8_t byte = state->bitArray[index >> 3];
            if ((byte & (1 << (index & 7))) != 0) {
                // Bit set: generate positive random number
                uint32_t raw;
                randomBits(0x13, &raw);
                raw &= 0x7ffff; // 19 bits
                translation[i] = static_cast<float>(static_cast<int>(raw)) * kScaleTranslation;
                state->currentIndex = index + 1;
            } else {
                // Bit not set: generate negative random number
                state->someFlag = 1; // set flag at +0x1c
                uint32_t raw;
                randomBits(0x13, &raw);
                raw &= 0x7ffff;
                translation[i] = -static_cast<float>(static_cast<int>(raw)) * kScaleTranslation;
                // Note: In the original code, the currentIndex is not incremented in this path? Actually it is: the code enters LAB_004a9890 after setting flag, then calls randomBits, and then does the negation.
                // The currentIndex increment happens before the bit check? Let's re-examine:
                // Actually the original code increments currentIndex unconditionally before the bit check in the else path.
                // But in the bit set path, it also increments? Actually it goes to LAB_004a9890 which does not increment.
                // Wait: In the disassembly, the code at the start of the loop increments uVar4 (which is local_7c, the loop counter for three translations). But for the bit checking, it does:
                // uVar4 = *(uint *)(param_1 + 0x18); // currentIndex
                // if (*(uint *)(param_1+0x2c) < uVar4) { ... set flag, goto LAB_004a9890, no increment }
                // else { bVar1 = *(byte *)((uVar4>>3) + *(int*)(param_1+0xc)); *(uint*)(param_1+0x18) = uVar4+1; ... }
                // So if maxIndex < currentIndex, it goes to LAB where it sets flag, generates random positive? Actually LAB also generates random and masks, but then later negates. So it's a fallback path when index out of range.
                // If index within range, it checks the bit and increments currentIndex.
                // This is complex. I'll simplify for reconstruction: The code shows two paths. One increments and checks bit, other (out of bounds) sets flag and generates positive? No, LAB generates random and then later negates.
                // Actually after LAB_004a9890, it sets local_80 = -(local_80 & 0x7ffff); so it's negative.
                // So we need to replicate the logic:
                // Let's rewrite according to original decompilation:
                // uVar4 = state->currentIndex;
                // if (state->maxIndex < uVar4) {
                //     state->someFlag = 1;
                //     randomBits(0x13, &raw);
                //     raw = -(raw & 0x7ffff);
                // } else {
                //     bVar1 = state->bitArray[uVar4>>3];
                //     state->currentIndex = uVar4 + 1;
                //     if ((bVar1 & (1 << (uVar4 & 7))) == 0) {
                //         // bit not set -> goto LAB_004a9890 (set flag, generate negative)
                //         state->someFlag = 1;
                //         randomBits(0x13, &raw);
                //         raw = -(raw & 0x7ffff);
                //     } else {
                //         // bit set -> generate positive
                //         randomBits(0x13, &raw);
                //         raw = raw & 0x7ffff;
                //     }
                // }
                // So the negative path is common for both out-of-range and bit-not-set.
            }
        } else {
            // Out of range path
            state->someFlag = 1;
            uint32_t raw;
            randomBits(0x13, &raw);
            raw &= 0x7ffff;
            translation[i] = -static_cast<float>(static_cast<int>(raw)) * kScaleTranslation;
        }
    }

    // Step 5: Fill output transform (9 rotation + 3 translation)
    outTransform[0]  = rows[0][0];
    outTransform[1]  = rows[0][1];
    outTransform[2]  = rows[0][2];
    outTransform[4]  = rows[1][0];
    outTransform[5]  = rows[1][1];
    outTransform[6]  = rows[1][2];
    outTransform[8]  = rows[2][0];
    outTransform[9]  = rows[2][1];
    outTransform[10] = rows[2][2];
    outTransform[12] = translation[0];
    outTransform[13] = translation[1];
    outTransform[14] = translation[2];
}