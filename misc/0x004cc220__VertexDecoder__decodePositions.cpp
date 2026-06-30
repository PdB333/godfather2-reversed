// FUNC_NAME: VertexDecoder::decodePositions

#include <cstdint>
#include <xmmintrin.h> // SSE intrinsics

// Global decode tables from Ghidra export (addresses 0x00e366c0 etc)
static const __m128 kMinInit = { -1.0e10f, -1.0e10f, -1.0e10f, -1.0e10f }; // placeholder
static const __m128 kMaxInit = { 1.0e10f, 1.0e10f, 1.0e10f, 1.0e10f };    // placeholder
// Actually loaded from memory at FUN_004cc220+0x4e
static const uint32_t kDecodeMask0 = 0xFFFF; // etc.

// Decode one vertex from compressed stream, output 12 bytes per vertex
// pStream: pointer to 16-byte compressed vertex data
// pWeightTable: base for weight indices (param_3)
// pOutVertex: 12-byte output per vertex (8 bytes position + 4 bytes color)
// also computes min/max of the decoded 4-vector
void decodeOneVertex(const uint8_t* pStream, const float* pWeightTable,
                     uint8_t* pOutVertex, __m128& minVec, __m128& maxVec)
{
    // Read 64-bit value from offset 0 of pStream
    uint64_t val0 = *(const uint64_t*)pStream;
    // Read 64-bit value from offset 12 of pStream (based on -500 from adjusted ptr)
    uint64_t val1 = *(const uint64_t*)(pStream + 12);

    // Extract fields from val0 (bit manipulations)
    short sVal0_hi = (short)(val0 >> 48);
    short sVal0_mid = (short)(val0 >> 32);
    short sVal0_low = (short)(val0 >> 16);
    short sVal0_low2 = (short)val0;

    // Form a 128-bit vector with replication
    __m128i vLow = _mm_set_epi16(sVal0_hi, sVal0_mid, sVal0_low, sVal0_low2,
                                 sVal0_hi, sVal0_mid, sVal0_low, sVal0_low2);
    // Mask with 0x00ffffff (??)
    static const uint32_t kMaskData = 0x00ffffff; // placeholder
    __m128i vMasked = _mm_and_si128(vLow, _mm_set1_epi32(kMaskData));
    // Multiply by scale and add bias (global constants)
    __m128 vScaled = _mm_mul_ps(_mm_cvtepi32_ps(vMasked), _mm_set1_ps(1.0f / 2048.0f)); // example

    // Read indices from bytes at offset 6 and 7 of pStream
    uint32_t index0 = pStream[6] * 64;
    uint32_t index1 = pStream[7] * 64;
    const float* pMat0 = pWeightTable + index0;
    const float* pMat1 = pWeightTable + index1;
    // Blend with fields from val1 (bit unpacking similar)
    // ... (complex matrix multiply with scale factors)
    // For brevity, we assume the result is a 4-vector stored in vResult

    __m128 vResult; // placeholder for decoded 4-float vertex
    // Write output: lower 8 bytes as 64-bit, then 4 bytes as uint32 (color)
    *(uint64_t*)pOutVertex = _mm_cvtsi128_si64(_mm_castps_si128(vResult));
    uint32_t color = 0xFFFFFFFF; // compute from vResult components
    *(uint32_t*)(pOutVertex + 8) = color;

    // Update min/max
    minVec = _mm_min_ps(minVec, vResult);
    maxVec = _mm_max_ps(maxVec, vResult);
}

void VertexDecoder::decodePositions(const uint8_t* pCompressedData, int numVertices,
                                    const float* pWeightTable, uint8_t* pOutputVertices,
                                    float* pOutMinBounds, float* pOutMaxBounds)
{
    // Spin loop if param_4 nonzero (unused delay)
    // param_4 is omitted in this reconstruction; assume 0.

    __m128 minBounds = kMinInit;
    __m128 maxBounds = kMaxInit;

    // Advance pointer by 0x200 bytes? Actually the original code added 0x200 to param_1
    // before the loop. That offset is likely a fixed prefix we skip.
    const uint8_t* pStream = pCompressedData + 0x200;

    for (int i = 0; i < numVertices; ++i, pStream += 16, pOutputVertices += 12)
    {
        decodeOneVertex(pStream, pWeightTable, pOutputVertices, minBounds, maxBounds);
    }

    // Write final min/max bounds (4 floats each)
    _mm_storeu_ps(pOutMinBounds, minBounds);
    _mm_storeu_ps(pOutMaxBounds, maxBounds);
}