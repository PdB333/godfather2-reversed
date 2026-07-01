// FUNC_NAME: AnimBlendNode::evaluate
void __thiscall AnimBlendNode::evaluate(int thisPtr, BlendInput* input)
{
    // Global cache pointer - holds the last used transform data address
    static TransformData* g_lastCachedTransform = DAT_0112dba0;  // +0x00: pointer
    static float g_currentTime = _DAT_00d5780c;                  // global time

    int* cachedPtr = g_lastCachedTransform;
    // Copy the 6 floats (position + orientation?) from this+0x34 to cache if needed
    if ((float*)(cachedPtr + 4) != (float*)(thisPtr + 0x34)) {
        // Copy 6 floats: this+0x34 through this+0x48
        *(float*)(cachedPtr + 4) = *(float*)(thisPtr + 0x34);    // +0x04
        *(float*)(cachedPtr + 8) = *(float*)(thisPtr + 0x38);    // +0x08
        *(float*)(cachedPtr + 0xc) = *(float*)(thisPtr + 0x3c);  // +0x0c
        *(float*)(cachedPtr + 0x10) = *(float*)(thisPtr + 0x40); // +0x10
        *(float*)(cachedPtr + 0x14) = *(float*)(thisPtr + 0x44); // +0x14
        *(float*)(cachedPtr + 0x18) = *(float*)(thisPtr + 0x48); // +0x18
    }

    if (input == nullptr) {
        // Just compute final blend from stored matrices (no blending weight)
        computeBlendedMatrix(
            (Matrix44*)(thisPtr + 0x80),   // matrix A at +0x80
            (Matrix44*)(thisPtr + 0xc0),   // matrix B at +0xc0
            (Matrix44*)(thisPtr + 0x100)   // matrix C at +0x100
        );
        return;
    }

    // Prepare blending: update internal state
    initBlending();
    calculateWeights();

    float evalTime = g_currentTime - (float)input->time; // input time offset

    // Apply weight to the input source transform
    applyWeightToTransform(
        (TransformData*)(input->sourcePtr + 0x30),  // source object's transform
        input->time                                  // weight as float
    );

    // Apply weight to this object's internal transform (at +0x30)
    applyWeightToTransform(
        (TransformData*)(thisPtr + 0x30),
        evalTime
    );

    // Compute final blend from local temporary matrices
    Matrix44 tempA;   // local_d0[64]
    Matrix44 tempB;   // local_90[64]
    Matrix44 tempC;   // local_50[64] (76 bytes but used as 64?)
    computeBlendedMatrix(&tempA, &tempB, &tempC);
}

// Supporting structures (not declared in this function)
struct TransformData {
    float data[6]; // 6 floats (at +0x04 to +0x18 as used above)
};

struct BlendInput {
    int* sourcePtr; // pointer to source object
    float time;     // time offset or weight
};

typedef float Matrix44[16]; // 4x4 matrix (64 bytes)

// External functions (callees)
void computeBlendedMatrix(Matrix44* a, Matrix44* b, Matrix44* c);
void initBlending();
void calculateWeights();
void applyWeightToTransform(TransformData* transform, float weight);