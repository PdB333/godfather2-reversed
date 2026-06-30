// FUNC_NAME: RandomGenerator::generateSpherePoint
// Address: 0x0064c2a0
// Reconstructed from Ghidra decompilation. This function generates a random point on a unit sphere (or a point on the z-axis) using a bit-stream cache and random numbers. The direction is controlled by two bit-width parameters (bitsForAngle and bitsForZ).

// External constants (likely defined elsewhere in the game)
extern const float DAT_00e2a848; // scaling factor for angle
extern const float DAT_00e2b1a4; // likely 1.0f (radius squared)
extern const float DAT_00e2eff4; // another constant (maybe -1.0f or 0.0f)

// Forward declarations for helper functions (from the same modules)
int getRandomInt(void);                // FUN_0064be80
float cosFromDouble(double angle);     // FUN_00b99e20 (cosine)
float sinFromDouble(double angle);     // FUN_00b99fcb (sine)

// Structure assumed for the random generator state
struct RandomGeneratorState {
    // +0x00: unknown fields
    // +0x0C: int* bitArray;   // pointer to byte array for bit cache
    byte* bitArray;   // offset 0x0C
    // +0x18: uint currentBitPos;  // current bit index in the cache
    uint currentBitPos;    // offset 0x18
    // +0x1C: byte exhaustedFlag;
    byte exhaustedFlag;    // offset 0x1C
    // +0x2C: uint totalBits;        // total number of bits available in cache
    uint totalBits;        // offset 0x2C
};

void RandomGenerator::generateSpherePoint(float* outVec, char bitsForAngle, char bitsForZ) {
    // outVec[0] = x, outVec[1] = y, outVec[2] = z
    uint uVar2;
    int iVar3;
    float fVar5, fVar7;
    double dVar6;
    byte bVar1;
    uint uVar4;

    uVar2 = this->currentBitPos; // offset 0x18

    // If we've exhausted the bit cache, fall through to random generation
    if (this->totalBits < uVar2) { // offset 0x2C
        this->exhaustedFlag = 1;   // offset 0x1C
        goto random_generation;
    }

    // Read a byte from the bit array and check the current bit
    bVar1 = this->bitArray[uVar2 >> 3];  // offset 0x0C
    uVar4 = uVar2 + 1;
    this->currentBitPos = uVar4;

    // If the current bit is 0, go to random generation
    if ((bVar1 & (1 << (uVar2 & 7))) == 0) {
        goto random_generation;
    }

    // If we are at the end of the cache after incrementing, set exhausted flag
    if (this->totalBits < uVar4) {
        this->exhaustedFlag = 1;
        // Then fall through to the next bit check (but there is no more data, so use constants)
        fVar5 = DAT_00e2eff4;
        if (false) { // intentionally no goto; we will set fVar5 below
            // Empty block to mirror control flow
        }
    } else {
        // Read the next bit
        bVar1 = this->bitArray[uVar4 >> 3];
        this->currentBitPos = uVar2 + 2;
        fVar5 = DAT_00e2eff4;
        if ((bVar1 & (1 << (uVar4 & 7))) != 0) {
            goto constant_point;
        }
    }

    // If we get here, the first bit was 1 but the second bit was 0
    fVar5 = DAT_00e2b1a4;

constant_point:
    // Return a point purely on the z-axis (x=0, y=0)
    outVec[2] = fVar5;
    outVec[0] = 0.0f;
    outVec[1] = 0.0f;
    return;

random_generation:
    // Generate random numbers for the angle and the z-coordinate
    iVar3 = getRandomInt();
    outVec[2] = (float)iVar3 / (float)((1 << (bitsForZ - 1U)) - 1); // normalized to [0,1]

    iVar3 = getRandomInt();
    fVar5 = ((float)iVar3 / (float)((1 << (bitsForAngle - 1U)) - 1)) * DAT_00e2a848; // scaled angle

    fVar7 = sqrtf(DAT_00e2b1a4 - outVec[2] * outVec[2]); // horizontal radius from unit sphere

    // Convert angle to (cos, sin) and scale by radius
    dVar6 = (double)fVar5;
    outVec[0] = cosFromDouble(dVar6) * fVar7;
    outVec[1] = sinFromDouble(dVar6) * fVar7;
    return;
}