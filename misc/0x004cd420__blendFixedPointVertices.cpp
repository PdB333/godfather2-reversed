// FUNC_NAME: blendFixedPointVertices
// Address: 0x004cd420
// Role: Unpacks a batch of 64-bit packed vertex data, applies a fixed-point transform (with 13-bit fractional precision) scaled by a floating-point weight, and accumulates the result into a float4 output buffer (pointed to by ESI). Uses global constants for base offsets and bit masks, likely for skinning or morphing.

#include <cstdint>

// Global constants (from address references in decompiled code)
extern const int32_t g_baseX;      // _DAT_00e31ad0
extern const int32_t g_baseY;      // _UNK_00e31ad4
extern const int32_t g_baseZ;      // _UNK_00e31ad8
extern const int32_t g_baseW;      // _UNK_00e31adc
extern const __m128i g_maskLo;     // _DAT_00e31ab0 (mask for low bits)
extern const __m128i g_maskHi;     // _DAT_00e31ac0 (mask for high bits)

// __fastcall: first arg in ECX (packedData), second in EDX (count), ESI set by caller to output buffer
void __fastcall blendFixedPointVertices(const uint64_t *packedData, int count)
{
    // ESI register is assumed to point to the output float4 array (each 16 bytes)
    float *outVerts = reinterpret_cast<float *>(_ESI);

    while (count > 0)
    {
        uint64_t raw = *packedData;

        // Extract bitfields from the packed 64-bit value
        uint16_t bitsHigh = static_cast<uint16_t>(raw >> 48);   // bits 48-63
        uint16_t bitsMid  = static_cast<uint16_t>(raw >> 32);   // bits 32-47
        uint16_t bitsLow  = static_cast<uint16_t>(raw >> 16);   // bits 16-31

        // Build 16-byte vectors for bit manipulation (Intel SSE __m128i)
        __m128i vec1 = _mm_set_epi16(bitsHigh, bitsHigh, 0, 0, 0, 0, 0, 0); // not exact, but for illustration
        // Actually we follow the exact decomposition from decompiled code:
        // auVar11: low 8 bytes = raw, bytes8-11=0, bytes12-13=bitsHigh, bytes14-15=bitsHigh
        __m128i v11 = _mm_set_epi64x(0, raw); // set low 64 bits
        v11 = _mm_insert_epi16(v11, bitsHigh, 6); // insert at offset 12/13? (word index 6)
        v11 = _mm_insert_epi16(v11, bitsHigh, 7); // offset 14/15

        // auVar10: low 8 bytes = raw, bytes8-9=0, bytes10-11=bitsMid, bytes12-15=v11's 12-15
        __m128i v10 = _mm_set_epi64x(0, raw);
        v10 = _mm_insert_epi16(v10, bitsMid, 5); // offset 10/11
        // copy bytes12-15 from v11
        v10 = _mm_insert_epi32(v10, _mm_extract_epi32(v11, 3), 3); // copy the high 32 bits of v11

        // auVar14: low 8 bytes = raw, bytes8-9=bitsMid, bytes10-15 = v10 bytes10-15
        __m128i v14 = _mm_set_epi64x(0, raw);
        v14 = _mm_insert_epi16(v14, bitsMid, 4); // offset 8/9
        // copy bytes10-15 from v10
        v14 = _mm_insert_epi64(v14, _mm_extract_epi64(v10, 1), 1); // copy high 64 bits of v10

        // auVar9: bytes0-1=low16 bits, bytes2-3=low16 bits, bytes4-5=bitsLow, bytes6-7=bitsLow, bytes8-15=v14 bytes8-15
        __m128i v9 = _mm_set_epi64x(0, raw); // low 64 bits
        v9 = _mm_insert_epi16(v9, static_cast<uint16_t>(raw), 0);
        v9 = _mm_insert_epi16(v9, static_cast<uint16_t>(raw), 1);
        v9 = _mm_insert_epi16(v9, bitsLow, 2);
        v9 = _mm_insert_epi16(v9, bitsLow, 3);
        // copy bytes8-15 from v14
        v9 = _mm_insert_epi64(v9, _mm_extract_epi64(v14, 1), 1);

        // Apply masks and compute transformed values
        __m128i vMasked = _mm_and_si128(g_maskHi, v9);    // auVar14 = g_maskHi & v9
        // vMasked components are 32-bit integers

        // Compute auVar13 = (vMasked * 0x2000) + base offsets
        __m128i scaled = _mm_mullo_epi32(vMasked, _mm_set1_epi32(0x2000));
        __m128i offsets = _mm_setr_epi32(g_baseX, g_baseY, g_baseZ, g_baseW);
        __m128i resultInt = _mm_or_si128(_mm_and_si128(g_maskLo, v9), _mm_add_epi32(scaled, offsets));
        // Note: the decompiled shows auVar13 = (g_maskLo & v9) | (scaled + offsets)

        // Extract the four 32-bit components (as integers to be converted to float)
        int32_t comp0 = _mm_cvtsi128_si32(resultInt);
        int32_t comp1 = _mm_extract_epi32(resultInt, 1);
        int32_t comp2 = _mm_extract_epi32(resultInt, 2);
        int32_t comp3 = _mm_extract_epi32(resultInt, 3);

        // Compute output index from the high 16 bits of the packed value
        int index = (bitsHigh) * 4; // each float4 is 16 bytes, so index of float slot = bitsHigh * 4
        float *dst = &outVerts[index];

        // Accumulate with weight (in_XMM0_Da is a float passed in XMM0)
        float weight = _XMM0; // This is passed in XMM0 register (MSVC __fastcall with floating point)
        dst[0] += weight * static_cast<float>(comp0);
        dst[1] += weight * static_cast<float>(comp1);
        dst[2] += weight * static_cast<float>(comp2);
        dst[3] += 0.0f * static_cast<float>(comp3) + dst[3]; // equivalent to dst[3] untouched

        packedData++;
        count--;
    }
}