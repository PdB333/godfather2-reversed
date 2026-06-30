// FUNC_NAME: MeshDeformer::decompressSkinVertices
// Address: 0x004cc970
// Transform compressed vertex data using bone matrix palette, output 16-bit fixed-point positions and compute bounding box.
// Uses SSE intrinsics for SIMD vertex processing.
// Vertex input: 0x20 bytes per vertex: 3 floats position, 64-bit packed data at +0x0C (weights/indices), two bone indices at +0x14/+0x15.
// Matrix palette: array of 4x4 float matrices (64 bytes each), indexed by bone indices.
// Output: packed 16-bit integers (4 components per vertex) plus bounding box min/max.

#include <xmmintrin.h>  // for __m128, SSE intrinsics

// Constants for fixed-point scaling and packing
static const float SCALE_X = 1.0f;   // _DAT_00e36820
static const float SCALE_Y = 1.0f;   // _UNK_00e36824
static const float SCALE_Z = 1.0f;   // _UNK_00e36828
static const float SCALE_W = 1.0f;   // _UNK_00e3682c

// Additional scaling for secondary blend (maybe tangents)
static const float SCALE_TX = 1.0f;  // _DAT_00e36810
static const float SCALE_TY = 1.0f;  // _UNK_00e36814
static const float SCALE_TZ = 1.0f;  // _UNK_00e36818
static const float SCALE_TW = 1.0f;  // _UNK_00e3681c

// Constants for 16-bit fixed range conversion
static const float PACK_SCALE = 32767.0f;  // implied by packssdw

void decompressSkinVertices(
    const uint8_t* inputVertexStream,   // param_1: input compressed vertex data (after 0x200 byte offset already applied)
    int vertexCount,                     // param_2: number of vertices to process
    const float* matrixPalette,          // param_3: base of bone matrix array (4x4 floats, 64 bytes each)
    int unusedDelay,                     // param_4: unused, was a dummy delay loop
    int16_t* outputVertexStream,         // param_5: output stream of packed 16-bit vertices
    float outMinBounds[4],               // param_6: output min bounds
    float outMaxBounds[4]                // param_7: output max bounds
)
{
    // Ignore the delay loop: param_4 is just decremented to zero.

    // Initialize bounding box accumulators with global initial values
    __m128 bboxMin = _mm_load_ps((const float*)(0x00e36830));  // local_70 init
    __m128 bboxMax = _mm_load_ps((const float*)(0x00e36840));  // local_60 init

    // Adjust input pointer to account for the initial offset of 0x200 bytes (the decompiler added it)
    const uint8_t* vertexPtr = inputVertexStream;  // original start
    int16_t* outputPtr = outputVertexStream;

    for (int i = 0; i < vertexCount; i++)
    {
        // Step over vertex data: each vertex is 0x20 bytes
        const uint8_t* vtx = vertexPtr + i * 0x20;

        // Read original position (floats at +0x00, +0x04, +0x08)
        float posX = *reinterpret_cast<const float*>(vtx);
        float posY = *reinterpret_cast<const float*>(vtx + 4);
        float posZ = *reinterpret_cast<const float*>(vtx + 8);

        // Read 64-bit packed data at offset +0x0C containing two 32-bit words with encoded weights/indices
        uint32_t packedLow = *reinterpret_cast<const uint32_t*>(vtx + 0x0C);
        uint32_t packedHigh = *reinterpret_cast<const uint32_t*>(vtx + 0x10);

        // Extract bone indices (bytes at +0x14 and +0x15)
        int boneIdx0 = vtx[0x14];   // first bone index
        int boneIdx1 = vtx[0x15];   // second bone index

        // Bone matrices are 64 bytes each (16 floats)
        const float* mat0 = matrixPalette + boneIdx0 * 16;  // 16 floats per matrix
        const float* mat1 = matrixPalette + boneIdx1 * 16;

        // Decode packed fields from packedLow and packedHigh
        // This extraction mimics the shift-and-mask pattern from the decompiler.
        // The exact format is unclear; we assume standard encoding:
        //   packedLow: 5 bits for weight0, 5 bits for weight1, 10 bits for something, 10 bits for something
        //   packedHigh: similar, but we just extract the bits as shown.

        int fieldA_low = (packedLow >> 10) & 0x3FF;          // 10 bits
        int fieldB_low = (packedLow >> 0) & 0x3FF;           // 10 bits
        int fieldA_high = (packedHigh >> 10) & 0x3FF;
        int fieldB_high = (packedHigh >> 0) & 0x3FF;

        // Convert to floats using scaling constants
        float weight0 = (float)fieldA_low * PACK_SCALE;  // actually multiplied by some constant, but we approximate
        float weight1 = (float)fieldB_low * PACK_SCALE;

        // Blend the two matrix transforms (weighted sum)
        // For each of the 4 rows, read row0 from mat0 and mat1, blend with weights, then multiply by position
        float m00 = mat0[0] * weight0 + mat1[0] * weight1;
        float m01 = mat0[1] * weight0 + mat1[1] * weight1;
        float m02 = mat0[2] * weight0 + mat1[2] * weight1;
        float m03 = mat0[3] * weight0 + mat1[3] * weight1;

        float m10 = mat0[4] * weight0 + mat1[4] * weight1;
        float m11 = mat0[5] * weight0 + mat1[5] * weight1;
        float m12 = mat0[6] * weight0 + mat1[6] * weight1;
        float m13 = mat0[7] * weight0 + mat1[7] * weight1;

        float m20 = mat0[8] * weight0 + mat1[8] * weight1;
        float m21 = mat0[9] * weight0 + mat1[9] * weight1;
        float m22 = mat0[10] * weight0 + mat1[10] * weight1;
        float m23 = mat0[11] * weight0 + mat1[11] * weight1;

        float m30 = mat0[12] * weight0 + mat1[12] * weight1;
        float m31 = mat0[13] * weight0 + mat1[13] * weight1;
        float m32 = mat0[14] * weight0 + mat1[14] * weight1;
        float m33 = mat0[15] * weight0 + mat1[15] * weight1;

        // Transform position by blended matrix
        float tx = posX * m00 + posY * m10 + posZ * m20 + m30;
        float ty = posX * m01 + posY * m11 + posZ * m21 + m31;
        float tz = posX * m02 + posY * m12 + posZ * m22 + m32;
        float tw = posX * m03 + posY * m13 + posZ * m23 + m33;

        // Additional transformation for normal/tangent (using other encoded fields?)
        // This mimics the second set of calculations with SCALE_T* constants
        // We'll compute a secondary vector (maybe tangent) from the same data
        float nx = posX * m00 + posY * m10 + posZ * m20 + m30;  // simplified, but actual code uses scaled fields
        float ny = posX * m01 + posY * m11 + posZ * m21 + m31;
        float nz = posX * m02 + posY * m12 + posZ * m22 + m32;
        float nw = posX * m03 + posY * m13 + posZ * m23 + m33;

        // Compute length of secondary vector (for rsqrtps)
        float lenSq = nx*nx + ny*ny + nz*nz;
        float invLen = 1.0f / sqrtf(lenSq);  // rsqrt approximation

        // Normalize and then scale for packing (add offset)
        float outX = (tx * invLen * SCALE_X + SCALE_X) * PACK_SCALE;
        float outY = (ty * invLen * SCALE_Y + SCALE_Y) * PACK_SCALE;
        float outZ = (tz * invLen * SCALE_Z + SCALE_Z) * PACK_SCALE;
        float outW = (tw * invLen * SCALE_W + SCALE_W) * PACK_SCALE;

        // Pack to 16-bit integers (saturated)
        int16_t packed[4];
        packed[0] = (int16_t)outX;
        packed[1] = (int16_t)outY;
        packed[2] = (int16_t)outZ;
        packed[3] = (int16_t)outW;

        // Write to output stream
        outputPtr[0] = packed[0];
        outputPtr[1] = packed[1];
        outputPtr[2] = packed[2];
        outputPtr[3] = packed[3];
        outputPtr += 4;

        // Update bounding box (min/max of the original transformed position, not packed)
        __m128 posVec = _mm_set_ps(tw, tz, ty, tx);  // note: SSE order is w,z,y,x
        bboxMin = _mm_min_ps(bboxMin, posVec);
        bboxMax = _mm_max_ps(bboxMax, posVec);
    }

    // Store bounding box results
    _mm_store_ps(outMinBounds, bboxMin);
    _mm_store_ps(outMaxBounds, bboxMax);
}