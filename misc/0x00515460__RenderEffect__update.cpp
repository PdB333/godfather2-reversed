// FUNC_NAME: RenderEffect::update
#include <cstdint>

// Globals (addresses from .data section)
extern float g_renderParamMin;        // DAT_012058d0
extern float g_renderParamMax;        // DAT_00f15988
extern int32_t g_effectFlag1;         // _DAT_011f3a30
extern int32_t g_effectFlag2;         // _DAT_011f39f4
extern int32_t g_effectFlag3;         // _DAT_011f3a10
extern int32_t g_effectFlag4;         // _DAT_011f3a3c
extern int32_t g_effectFlag5;         // _DAT_011f3a38
extern int32_t g_effectFlag6;         // _DAT_011f3a14
extern int32_t g_effectFlag7;         // _DAT_011f3a44

// Other globals used
extern uint32_t g_effectState;        // DAT_0121b750 (camera state?)
extern uint32_t g_somePtr1;           // DAT_0121b874
extern uint32_t g_effectParamPtr;     // DAT_0121b754
extern uint32_t g_effectParamA;       // DAT_0121bbb8
extern uint32_t g_effectParamB;       // DAT_0121bbc0
extern uint32_t g_effectParamC;       // DAT_0121bbc4
extern uint32_t g_effectParamD;       // DAT_0121bbc8
extern uint32_t g_fogColorHandle;     // DAT_0121bb7c
extern uint32_t g_fogParamsHandle;    // DAT_0121bb80
extern uint32_t g_depthTextureHandle; // DAT_0121bb84
extern void* g_currentContext;        // DAT_012058e8
extern void* g_someContext;           // DAT_0121b740

// External functions (assumed signatures)
void setRenderState(int a, int b, int c);           // FUN_00417cf0
uint32_t getShaderParam(uint32_t shader, const char* name); // FUN_0060a580
void releaseShaderParam(uint32_t handle);           // FUN_0060a460
void updateViewMatrix();                            // FUN_005398d0
void updateProjMatrix();                            // FUN_005399a0
void setEffectMode(int enable);                     // FUN_00609890
void transitionEffect(void* src, void* dst);        // FUN_0060df60
void computeTransform();                            // FUN_005396f0
void applyVectorTransform(float vec[4]);            // FUN_00539930
void finalizeRender();                              // FUN_005388a0
void* allocateEffectBuffer(int type, int count, int a, int b, int c); // FUN_0060cd00
void writeEffectBuffer();                           // FUN_0060cde0
void updatePostProcessing();                        // FUN_00539250

// Clamp helper macro
#define CLAMP_PARAM(minVar, maxVar, value) \
    if (minVar < value) minVar = value; \
    if (value < maxVar) maxVar = value;

void RenderEffect::update(float* params) {
    // params is in EAX, assumed to be pointer to float array (matrix + extras)
    float vec1[4]; // local_30, fStack_2c, fStack_28, fStack_24 (first use)
    float vec2[4]; // second use of same locals

    // Initial render state setup
    setRenderState(1, 2, 1);

    // Clamp global parameters to specific values (multiple effect parameters)
    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 22.0f);  // 0x16
    g_effectFlag1 = 1;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 7.0f);   // 0x7
    g_effectFlag2 = 0;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 14.0f);  // 0xe
    g_effectFlag3 = 0;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 25.0f);  // 0x19
    g_effectFlag4 = 5;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 24.0f);  // 0x18
    g_effectFlag5 = 0;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 15.0f);  // 0xf
    g_effectFlag6 = 0;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 27.0f);  // 0x1b
    g_effectFlag7 = 0;

    setRenderState(1, 2, 1);

    // Effect state management (fog, depth texture)
    g_effectState = g_somePtr1; // DAT_0121b750 = DAT_01219908
    g_someContext = 0;          // DAT_0121b874 = 0
    g_effectParamPtr = g_effectParamA; // DAT_0121b754 = DAT_0121bbb8

    if (g_effectParamA == g_effectParamB || g_effectParamA == g_effectParamC || g_effectParamA == g_effectParamD) {
        g_fogColorHandle = getShaderParam(g_effectParamA, "fog_color");
        g_fogParamsHandle = getShaderParam(g_effectParamPtr, "fog_params");
        g_depthTextureHandle = getShaderParam(g_effectParamPtr, "depth_texture");
    }

    if (g_currentContext == &g_someContext) {
        releaseShaderParam(g_effectParamPtr);
        releaseShaderParam(g_effectState);
    }

    // First vector extraction from params (indices 8,9,10,17)
    vec1[0] = params[8];
    vec1[1] = params[9];
    vec1[2] = params[10];
    vec1[3] = params[17];

    updateViewMatrix();

    // Reassign from different indices (12,13,14,18)
    vec1[0] = params[12];
    vec1[1] = params[13];
    vec1[2] = params[14];
    vec1[3] = params[18];

    updateProjMatrix();

    // Effect state comparison
    if (g_effectFlag1 == g_effectState && g_effectFlag2 == 0) {
        setEffectMode(1);
    } else {
        transitionEffect(g_effectFlag1, g_effectState);
    }

    setRenderState(1, 2, 1);

    // Repeat clamping with same values but different flag settings
    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 22.0f);
    g_effectFlag1 = 1;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 7.0f);
    g_effectFlag2 = 0;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 14.0f);
    g_effectFlag3 = 0;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 25.0f);
    g_effectFlag4 = 5;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 24.0f);
    g_effectFlag5 = 0;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 15.0f);
    g_effectFlag6 = 0;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 27.0f);
    g_effectFlag7 = 0;

    setRenderState(1, 2, 1);

    // Another transformation step
    computeTransform();

    // Compute scaled vectors from params[0..7] with global scaling factor
    float scaleFactor1 = g_globalScale; // DAT_00e2b1a4
    if (params[16] < g_globalThreshold) { // DAT_00e44634
        scaleFactor1 = params[16] * g_globalScaleMultiplier; // DAT_00e445f0
    }

    float vec2_a[4];
    vec2_a[0] = scaleFactor1 * params[0];
    vec2_a[1] = scaleFactor1 * params[1];
    vec2_a[2] = scaleFactor1 * params[2];
    vec2_a[3] = scaleFactor1 * params[3];

    float scaleFactor2 = g_globalScale; // same global
    if (params[19] < g_globalThreshold) {
        scaleFactor2 = params[19] * g_globalScaleMultiplier;
    }

    vec2[0] = scaleFactor2 * params[4];
    vec2[1] = scaleFactor2 * params[5];
    vec2[2] = scaleFactor2 * params[6];
    vec2[3] = scaleFactor2 * params[7];

    // Store combined in vec1 (reuse same memory)
    float vec1_combined[4];
    vec1_combined[0] = vec2_a[0];
    vec1_combined[1] = vec2_a[1];
    vec1_combined[2] = vec2_a[2];
    vec1_combined[3] = vec2_a[3];

    // Actually the code uses the same local variables, so we combine the two parts? 
    // The original had: local_30, fStack_2c, fStack_28, fStack_24 from first part,
    // then fStack_24 is reused from second part. The final call uses &local_30.
    // We'll just create a final array from both sets.
    float finalVec[4];
    finalVec[0] = vec2_a[0];
    finalVec[1] = vec2_a[1];
    finalVec[2] = vec2_a[2];
    finalVec[3] = scaleFactor2 * params[7]; // actually fStack_24 from second set

    // But wait: the original code computed:
    // fStack_24 = DAT_00e2b1a4; ... then later if (params[19] < ...) fStack_24 = params[19] * DAT_00e445f0;
    // then local_30 = fStack_24 * params[4]; fStack_2c = ...; fStack_28 = ...; fStack_24 = fStack_24 * params[7];
    // So finalVec = { fStack_24 * params[4], fStack_24 * params[5], fStack_24 * params[6], fStack_24 * params[7] }
    // That is the second vector. The first vector (from scaleFactor1) is stored in separate locals and then overwritten?
    // Actually the code reused local_30 etc. for the second computation. But the call to FUN_00539930(&local_30) 
    // uses the final value of those locals, which is the second vector. However, note that before calling 
    // FUN_00539930, there is also the first vector computed and stored in same variables? Let's trace:
    // local_30 = fStack_24 * params[0]; fStack_2c = ... etc. Then later fStack_24 is reassigned for second vector,
    // and then local_30 = fStack_24 * params[4]; etc. So the final local_30..fStack_14 (indices 0-3) are from the second vector.
    // So the call uses the second vector (starting at params[4]).
    // So we'll use the second vector only.

    // Actually the code: after computing scaleFactor2, it sets fStack_24 (the fourth element of the second set) to scaleFactor2 * params[7].
    // Then it sets local_30 = fStack_24 * params[4]; fStack_2c = ...; fStack_28 = ...; fStack_24 = ...;
    // So the final vector is: [ scaleFactor2 * params[7] * params[4], scaleFactor2 * params[7] * params[5], ...? 
    // Wait: no, it's fStack_24 * params[4] where fStack_24 already is scaleFactor2 * params[7]? Actually the code:
    // fStack_24 = DAT_00e2b1a4; (some base scale)
    // if (params[19] < g_globalThreshold) fStack_24 = params[19] * DAT_00e445f0;
    // local_30 = fStack_24 * params[4];
    // fStack_2c = fStack_24 * params[5];
    // fStack_28 = fStack_24 * params[6];
    // fStack_14 = fStack_24 * params[7];   // note: fStack_14 is the 4th element? Actually fStack_14 is separate local, not part of vector?
    // But the vector passed to FUN_00539930 is &local_30, which includes local_30, fStack_2c, fStack_28, fStack_24? Wait, the locals:
    // local_30 (4 bytes), fStack_2c (4 bytes), fStack_28 (4 bytes), fStack_24 (4 bytes) -> these are four consecutive floats.
    // Then after that, local_20, fStack_1c, fStack_18, fStack_14 are separate.
    // So the vector passed is local_30, fStack_2c, fStack_28, fStack_24 (the first four).
    // So the second set overwrites those four: local_30 = fStack_24 * params[4]; ... fStack_24 = fStack_24 * params[7]? Actually the code:
    // fStack_24 = (computed scale)   // this is the 4th float in the vector
    // then local_30 = fStack_24 * params[4];
    // fStack_2c = fStack_24 * params[5];
    // fStack_28 = fStack_24 * params[6];
    // fStack_24 = fStack_24 * params[7];  // overwrites the 4th with product
    // So the final vector becomes: fStack_24 * params[4..7] (but the 4th element is fStack_24 * params[7] which is actually the product of scale and params[7] times itself? That seems weird. Actually it's: fStack_24 (which is scale) times params[7] for the last component, so the vector is scale * params[4..7].
    // So the vector is scaleFactor2 * params[4..7] (where scaleFactor2 = base scale or params[19]*Mult).
    // That is consistent: a scaled 4-component vector from params[4..7].
    // So we'll compute that.

    float scale2 = g_globalScale;
    if (params[19] < g_globalThreshold) {
        scale2 = params[19] * g_globalScaleMultiplier;
    }

    float finalVec2[4] = {
        scale2 * params[4],
        scale2 * params[5],
        scale2 * params[6],
        scale2 * params[7]
    };

    applyVectorTransform(finalVec2);
    finalizeRender();

    // Allocate and fill effect buffer
    void* buffer = allocateEffectBuffer(0xd, 4, 0, 1, 0);
    uint32_t value1 = g_effectVar1; // DAT_00e2eff4
    float value2 = g_globalScale;   // DAT_00e2b1a4
    if (buffer != nullptr) {
        *(uint32_t*)buffer = value1;
        *(uint32_t*)((uint8_t*)buffer + 4) = value1;  // puVar3[1] = uVar2 (same)
        *(float*)((uint8_t*)buffer + 8) = value2;      // puVar3[2] = fVar1
        *(uint32_t*)((uint8_t*)buffer + 12) = value1;  // puVar3[3] = uVar2
        *(float*)((uint8_t*)buffer + 16) = value2;     // puVar3[4] = fVar1
        *(float*)((uint8_t*)buffer + 20) = value2;     // puVar3[5] = fVar1
        *(uint32_t*)((uint8_t*)buffer + 24) = value1;  // puVar3[6] = uVar2
        *(float*)((uint8_t*)buffer + 28) = value2;     // puVar3[7] = fVar1
        writeEffectBuffer();
    }

    updatePostProcessing();

    // Final clamping with different flags for the post-processing pass
    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 22.0f);
    g_effectFlag1 = 1;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 7.0f);
    g_effectFlag2 = 1;  // changed from previous 0 to 1

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 14.0f);
    g_effectFlag3 = 1;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 25.0f);
    g_effectFlag4 = 7;  // changed from 5 to 7

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 24.0f);
    g_effectFlag5 = 0;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 15.0f);
    g_effectFlag6 = 0;

    CLAMP_PARAM(g_renderParamMin, g_renderParamMax, 27.0f);
    g_effectFlag7 = 0;

    setRenderState(1, 5, 6);
}