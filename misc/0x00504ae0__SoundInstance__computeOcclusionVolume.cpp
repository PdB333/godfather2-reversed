// FUNC_NAME: SoundInstance::computeOcclusionVolume
// Address: 0x00504ae0
// Computes occlusion and attenuation factors for a 3D sound source.
// Takes this (SoundInstance*) and source (SoundSource*) as fastcall parameters.
// Fills this+0x44 (directVolume), this+0x4c (occlusionFactor), this+0x50 (finalVolume).

struct SoundParams {
    uint32_t flags;     // +0x14: bitmask (0x70000, 0x20000,0x40000,0x6)
    float orientationX; // +0x30
    float orientationY; // +0x34
    float orientationZ; // +0x38
    float unknown3C;    // +0x3C (multiplier)
    float threshold;    // +0x40 (distance threshold)
    float farVolume;    // +0x44 (volume at far distance)
};

struct SoundInstance {
    void* somePtr;         // +0x08 (pointer into a matrix/rotation table)
    SoundParams* params;   // +0x20
    float baseDistance;    // +0x5C (source distance)
    float lateralFactor;   // +0x60 (square of lateral component? or another coordinate)
    float directVolume;    // +0x44 (output)
    float occlusionFactor; // +0x4C (output)
    float finalVolume;     // +0x50 (output)
};

struct SoundSource {
    float listenerPos[3]; // +0x70,0x74,0x78
    uint32_t materialIdx; // +0x16C (index into sound material table)
};

// Global constants (approximate values)
extern float fOne;          // DAT_00e2b1a4 = 1.0f
extern float fOneDivTwo;    // DAT_00e44760 (maybe 0.5f or similar)
extern float fInvSquare;    // DAT_00e2d99c (some reciprocal constant)
extern float fZero;         // DAT_00e44564 (maybe 0.0f)
extern void* PTR_SQRT;      // PTR_FUN_00e4462c (likely sqrt function or constant)

// Sound material table (0x38 bytes per entry, at DAT_011a0f28)
struct SoundMaterial {
    short index;       // +0x02
    unsigned short flags; // +0x04
};

uint __fastcall computeOcclusionVolume(SoundInstance* this, SoundSource* source) {
    SoundMaterial* material = nullptr;
    if (source->materialIdx < 0x1000) {
        material = &((SoundMaterial*)0x011a0f28)[source->materialIdx];
    }

    float baseDist = this->baseDistance;               // +0x5C
    SoundParams* params = this->params;                // +0x20
    float sourceMaterialFactor = (float)material->index;  // from table +0x02
    unsigned short materialFlags = material->flags;       // from table +0x04

    // direct volume: (baseDist / index) * params->unknown3C * fOneDivTwo
    this->directVolume = (baseDist / sourceMaterialFactor) * params->unknown3C * fOneDivTwo;

    // occlusion factor: using squared distance ratio
    float lateralSq = this->lateralFactor * this->lateralFactor; // from +0x60
    float distSq = baseDist * baseDist + lateralSq;
    float denom = (float)materialFlags * (float)materialFlags + sourceMaterialFactor * sourceMaterialFactor;
    float rawOcclusion = fOne - (distSq * fInvSquare) / denom;
    if (rawOcclusion > 0.0f) {
        if (rawOcclusion > fOne) rawOcclusion = fOne;
    } else {
        rawOcclusion = 0.0f;
    }
    this->occlusionFactor = rawOcclusion * rawOcclusion;

    uint32_t flags = params->flags; // +0x14
    if (flags & 0x70000) {
        int materialIdx = 0;
        if (!(flags & 0x20000)) {
            if (flags & 0x40000) {
                materialIdx = 2;
            }
        } else {
            materialIdx = 1;
        }

        // Thread-local storage: get a matrix base pointer
        int matrixBase = *(int*)(*(int**)(*(int*)(0x2C) + 0x2C) + 8); // FS segment manipulation
        float* matrix = (float*)((*(int*)(this->somePtr) + 0x80) + matrixBase); // +0x08 -> +0x80

        float sourceX = matrix[0];
        float sourceY = matrix[1];
        float sourceZ = matrix[2];

        // If orientation is relative (flags & 6 == 0), add params orientation
        if ((flags & 6) == 0) {
            sourceX += params->orientationX;
            sourceY += params->orientationY;
            sourceZ += params->orientationZ;
        }

        // Vector from listener to source
        float dx = sourceX - source->listenerPos[0];
        float dy = sourceY - source->listenerPos[1];
        float dz = sourceZ - source->listenerPos[2];

        // Select rotation matrix row based on materialIdx
        int rowOffset = (materialIdx + 5) * 0x10; // each row is 16 bytes (4 floats)
        float* rotRow = (float*)((int)this->somePtr + rowOffset + matrixBase); // +0x08

        // Dot product with that row (likely for directional attenuation)
        float dot = rotRow[0] * dx + rotRow[1] * dy + rotRow[2] * dz;
        float dist = sqrtf(dx*dx + dy*dy + dz*dz) + (float)PTR_SQRT; // PTR_FUN likely a constant offset
        float normalizedDot = dot / dist; // actually: dot / (dist + something)

        // Compute occlusion based on angle/distance
        float occlusionFactor2 = (fZero - normalizedDot - params->threshold) / (fOne - params->threshold);
        if (occlusionFactor2 > 0.0f) {
            if (occlusionFactor2 > fOne) occlusionFactor2 = fOne;
        } else {
            occlusionFactor2 = 0.0f;
        }

        // Final volume: blend between farVolume and a custom factor
        float invOcclusion = fOne - occlusionFactor2;
        float volume = (fOne - invOcclusion * invOcclusion * invOcclusion * invOcclusion) * params->farVolume
                     + (fOne - invOcclusion) * (fOne - params->farVolume);
        this->finalVolume = volume;

        return (uint)(this->somePtr + rowOffset + matrixBase); // return pointer to the rotation row? weird
    }

    // If no special flags, final volume = 1.0
    this->finalVolume = fOne;
    return flags; // return the flags
}