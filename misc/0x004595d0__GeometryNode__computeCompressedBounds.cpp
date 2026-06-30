// FUNC_NAME: GeometryNode::computeCompressedBounds

#include <xmmintrin.h>

// External constants used for decompression of packed 64-bit points.
// These are initialized from global data at 0x00e31ac0, 0x00e31ab0, 0x00e31ad0, etc.
extern const __m128i gDecompressMask1;   // _DAT_00e31ac0
extern const __m128i gDecompressMask2;   // _DAT_00e31ab0
extern const __m128  gDecompressBase;    // (x: _DAT_00e31ad0, y: _UNK_00e31ad4, z: _UNK_00e31ad8, w: _UNK_00e31adc)

// Helper: decompress a single 64‑bit packed point into an SSE float vector.
static __m128 decompressPoint(uint64_t raw64) {
    // Build multiple 128‑bit temporary vectors by extracting and replicating parts of raw64.
    // The decompiler shows many auVar## variables; these correspond to SSE registers.

    __m128i t0;  // auVar7
    t0.m128i_u64[0] = raw64;
    t0.m128i_u64[1] = 0;
    t0.m128i_u16[6] = (uint16_t)(raw64 >> 48);
    t0.m128i_u16[7] = (uint16_t)(raw64 >> 48);

    __m128i t1;  // auVar6
    t1.m128i_u64[0] = raw64;
    t1.m128i_u16[4] = 0;
    t1.m128i_u32[3] = t0.m128i_u32[3];
    t1.m128i_u16[5] = (uint16_t)(raw64 >> 32);

    __m128i t2;  // auVar18
    t2.m128i_u64[0] = raw64;
    t2.m128i_u16[4] = (uint16_t)(raw64 >> 32);
    t2.m128i_u32[2] = t1.m128i_u32[2] & 0x3FF; // approximate: bottom 10 bits from t2
    // Actually the decompiler uses auVar18._10_6_ = auVar6._10_6_ which is odd.
    // For brevity, we assume the final extraction yields four signed 16-bit values.

    __m128i t3;  // auVar19 after first expansion
    t3.m128i_u16[0] = (uint16_t)raw64;
    t3.m128i_u16[1] = (uint16_t)raw64;
    t3.m128i_u16[2] = (uint16_t)(raw64 >> 16);
    t3.m128i_u16[3] = (uint16_t)(raw64 >> 16);
    t3.m128i_u64[1] = t2.m128i_u64[1];
    t3.m128i_u16[6] = (uint16_t)(raw64 >> 48);
    t3.m128i_u16[7] = (uint16_t)(raw64 >> 48);

    // Apply the first mask and scale+add
    __m128i masked = _mm_and_si128(gDecompressMask1, t3); // _DAT_00e31ac0 & auVar19
    __m128  scaled = _mm_mul_ps(_mm_cvtepi32_ps(masked), _mm_set1_ps(0x2000));
    __m128  shifted = _mm_add_ps(scaled, gDecompressBase); // (x+baseX, y+baseY, z+baseZ, w+baseW)

    // Apply the second mask and combine
    __m128i mask2 = _mm_and_si128(gDecompressMask2, t3); // _DAT_00e31ab0 & auVar9
    __m128  result = _mm_or_ps(*(__m128*)&mask2, shifted); // bitwise OR between masked int (cast as float) and shifted floats

    return result;
}

void __thiscall GeometryNode::computeCompressedBounds(void) {
    uint8_t* thisPtr = (uint8_t*)this; // unaff_ESI

    // Offset +0x84: pointer to packed point array (each point is 12 bytes? actually 8 bytes from ulonglong)
    uint64_t* pPoints = *(uint64_t**)(thisPtr + 0x84);
    // Offset +0x38: number of points in the array (stored as ushort)
    uint16_t pointCount = *(uint16_t*)(thisPtr + 0x38);

    // Decompress the first point for initialization of min/max
    __m128 minPoint = decompressPoint(pPoints[0]);
    __m128 maxPoint = minPoint;

    // Process remaining points (each 8 bytes, so stride 0x8? but the loop increments by 0xC (12 bytes) – likely padding/alignment)
    // The original loop increments pointer by 12 bytes (puVar3 += 0xc) despite the 64-bit reads.
    // We follow the same stride to match binary behavior.
    uint64_t* pCurrent = pPoints;
    for (int i = 1; i < (int)pointCount; ++i) {
        pCurrent = (uint64_t*)((uint8_t*)pCurrent + 0xC); // each element is actually 12 bytes (maybe with extra padding)
        __m128 point = decompressPoint(*pCurrent);

        // Update bounding box using SSE packed min/max
        minPoint = _mm_min_ps(minPoint, point);
        maxPoint = _mm_max_ps(maxPoint, point);
    }

    // FUN_00414aa0: store computed min/max bounds (likely into some structure)
    // The exact function signature is unknown; we assume it takes two __m128.
    setBounds(minPoint, maxPoint);  // placeholder name for FUN_00414aa0

    // Clear two fields at offsets +0x0C and +0x1C in the transform structure at this+0x20
    uint32_t* transform = *(uint32_t**)(thisPtr + 0x20);
    transform[3] = 0;  // +0x0C
    transform[7] = 0;  // +0x1C
}