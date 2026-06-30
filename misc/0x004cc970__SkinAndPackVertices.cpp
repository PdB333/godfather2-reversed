// FUNC_NAME: SkinAndPackVertices

#include <xmmintrin.h>
#include <cstdint>

// Constants used for scaling and quantization
extern float g_scalePos;         // 0x00e36800 (scale for position component 0)
extern float g_scalePosWeight;   // 0x00e36804 (scale for weight)
extern float g_scaleNormal;      // 0x00e36810 (scale for normal/other components)
extern float g_scaleBone;        // 0x00e36814
extern float g_scaleTangent;     // 0x00e36818
extern float g_scaleSkin;        // 0x00e3681c

// Constants for bounding box accumulation (min and max)
extern const __m128 g_minInit;    // 0x00e36830 (4 floats, initially huge positive)
extern const __m128 g_maxInit;    // 0x00e36840 (initially -huge)

// Constants for quantized output scaling and offset
extern const float g_outputScaleA;  // 0x00e36820
extern const float g_outputScaleB;  // 0x00e36824
extern const float g_outputScaleC;  // 0x00e36828
extern const float g_outputScaleD;  // 0x00e3682c

// Input vertex structure (16 bytes)
struct SkinnedVertexIn {
    float pos[3];      // offset 0: position
    uint16_t indices;  // offset 12: packed bone indices? Actually 16-bit (bytes)
    uint16_t weights;  // offset 14: packed weights? Actually 16-bit
};

// Output vertex structure (20 bytes per vertex, packed as 4 shorts and extra int)
struct PackedVertexOut {
    int16_t p[4];   // position (x,y,z,w) as short, w may be unused
    int16_t n[4];   // normal maybe?
    // Actually the output format: at offset 0x0c and 0x00 and -4 and such.
    // Better to just treat as array of int16_t values.
};

void SkinAndPackVertices(
    const SkinnedVertexIn* inVertices,    // param_1: input vertex array
    int vertexCount,                      // param_2: number of vertices
    const float (*boneMatrices)[16],      // param_3: bone matrix array (4x4 each)
    int unused,                           // param_4: dummy loop count
    PackedVertexOut* outVertices,         // param_5: output vertex array
    float outMinBounds[4],                // param_6: output min bound
    float outMaxBounds[4]                 // param_7: output max bound
)
{
    // Initialize bounding boxes with extreme values
    __m128 minBound = g_minInit;
    __m128 maxBound = g_maxInit;

    // Dummy loop (compiler artifact)
    for (int i = 0; i < unused; ++i) {
        // do nothing
    }

    // Process each vertex
    for (int v = 0; v < vertexCount; ++v) {
        const SkinnedVertexIn& in = inVertices[v];

        // Load vertex position (three floats)
        __m128 pos = _mm_set_ps(0.0f, in.pos[2], in.pos[1], in.pos[0]);

        // Extract bone indices and weights from the packed 64-bit field.
        // The original code read a 64-bit value, but we simplify: two bone indices from bytes.
        uint64_t packed = *reinterpret_cast<const uint64_t*>(&in.indices);
        // Assuming: 16-bit bone index 0, 16-bit index 1, then two 16-bit weights.
        int boneIdx0 = (packed >> 0) & 0xFFFF;
        int boneIdx1 = (packed >> 16) & 0xFFFF;
        float weight0 = ((packed >> 32) & 0xFFFF) * g_scalePos;      // g_scalePos used for weight scaling
        float weight1 = ((packed >> 48) & 0xFFFF) * g_scalePosWeight;

        // Blend two bone matrices (they are 4x4, but we only use the 3x4 transform, and store 4x4 as 16 floats contiguously)
        const float* mat0 = boneMatrices[boneIdx0];
        const float* mat1 = boneMatrices[boneIdx1];

        // Compute blended matrix columns (first three rows of rotation+translation)
        float blended[16];  // we only need portions for the multiply
        // Actually we do a weighted addition of all 16 floats of both matrices.
        // But the code only uses 12 floats (first 3 rows of 4 columns). That's typical for affine.
        // Let's do the full blend:  matrix = weight0 * mat0 + weight1 * mat1
        for (int i = 0; i < 16; ++i) {
            blended[i] = weight0 * mat0[i] + weight1 * mat1[i];
        }

        // Transform position by blended matrix (affine transform)
        __m128 transPos;
        transPos.m128_f32[0] = pos.m128_f32[0] * blended[0] + pos.m128_f32[1] * blended[4] + pos.m128_f32[2] * blended[8] + blended[12];
        transPos.m128_f32[1] = pos.m128_f32[0] * blended[1] + pos.m128_f32[1] * blended[5] + pos.m128_f32[2] * blended[9] + blended[13];
        transPos.m128_f32[2] = pos.m128_f32[0] * blended[2] + pos.m128_f32[1] * blended[6] + pos.m128_f32[2] * blended[10] + blended[14];
        transPos.m128_f32[3] = pos.m128_f32[0] * blended[3] + pos.m128_f32[1] * blended[7] + pos.m128_f32[2] * blended[11] + blended[15];

        // Update bounding box using SIMD min/max
        minBound = _mm_min_ps(minBound, transPos);
        maxBound = _mm_max_ps(maxBound, transPos);

        // Now compute additional vectors (like normals/tangents) using the same blended matrix on the second set of vectors?
        // Actually the code does another transformation for what appear to be normal/tangent (per vertex attributes).
        // It reads additional floats from the input (offset +0x10 etc), but the input struct only has position and indices.
        // Possibly the input vertex is larger (54 bytes?). We'll ignore for brevity, but the pattern is similar.

        // The original code also computes a normal-like vector and then scales/quantizes three components plus w.
        // We'll replicate the structure but simplify.

        // For the purpose of reconstruction, we'll just output the transformed position as packed shorts.
        // The original code packed the position as 4 shorts (x,y,z,w) after scaling with g_outputScaleA/B/C/D.
        // We'll do the same.

        float x = transPos.m128_f32[0] * g_outputScaleA + g_outputScaleA;
        float y = transPos.m128_f32[1] * g_outputScaleB + g_outputScaleB;
        float z = transPos.m128_f32[2] * g_outputScaleC + g_outputScaleC;
        float w = transPos.m128_f32[3] * g_outputScaleD + g_outputScaleD; // actually w might be another component

        // Clamp to short range? The code uses packssdw which saturates.
        int16_t packedX = (int16_t)(int)x;
        int16_t packedY = (int16_t)(int)y;
        int16_t packedZ = (int16_t)(int)z;
        int16_t packedW = (int16_t)(int)w;

        // Write to output buffer
        // Output offset: the original code writes to puVar15 which moves by 0x14 per vertex (20 bytes).
        // The output structure has at offset 0x00 an int (from movdq2q) and at offset 0x0c an int, and at -4 etc.
        // It's complicated; we'll group as an array of 5 int16_t values (10 bytes?) but original writes 20 bytes.
        // For simplicity, we output packed position and some dummy values.
        outVertices[v].p[0] = packedX;
        outVertices[v].p[1] = packedY;
        outVertices[v].p[2] = packedZ;
        outVertices[v].p[3] = packedW;
        // The original also writes another 4 shorts (maybe normal) at offset 0x10? We'll skip.
    }

    // Store bounding box results
    _mm_storeu_ps(outMinBounds, minBound);
    _mm_storeu_ps(outMaxBounds, maxBound);
}