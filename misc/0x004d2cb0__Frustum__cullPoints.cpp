// FUNC_NAME: Frustum::cullPoints
// Address: 0x004d2cb0
// Role: Frustum culling - tests an array of points against all 6 frustum planes and outputs a byte mask per point.
// The frustum data is stored as 24 floats (6 planes * 4 components) at this+0x00,
// and a byte flag at this+0x60 (used as default result if any plane test fails).
// Points are 4-component (x,y,z,w). The global DAT_00e2b1a4 is a scaling factor.
// The loop count is passed in EDI register (pointCount). EAX is 'this', param_1 = point array, param_2 = output buffer.

#include <cstdint>

// Global constant from game data
extern float g_frustumScale; // DAT_00e2b1a4

struct Frustum {
    float planes[6][4];  // +0x00: 24 floats (a,b,c,d for each plane)
    uint8_t defaultMask; // +0x60: byte used as result if point is outside any plane
};

void Frustum::cullPoints(const float* points, char* outResults, int pointCount) {
    float fGlobal = g_frustumScale;
    uint8_t bDefault = *(uint8_t*)((uintptr_t)this + 0x60);

    // Load all 24 plane coefficients from the frustum structure
    float fPlane[24];
    for (int i = 0; i < 24; i++) {
        fPlane[i] = this->planes[0][i]; // actually need to index linearly - assume planes[0][i] spans the 24 floats
    }

    // Aliases for clarity (matching decompiled variable names)
    float f8 = fPlane[0];   float f9 = fPlane[1];   float f10 = fPlane[2];  float f11 = fPlane[3];
    float f12 = fPlane[4];  float f13 = fPlane[5];  float f14 = fPlane[6];  float f15 = fPlane[7];
    float f16 = fPlane[8];  float f17 = fPlane[9];  float f18 = fPlane[10]; float f19 = fPlane[11];
    float f20 = fPlane[12]; float f21 = fPlane[13]; float f22 = fPlane[14]; float f23 = fPlane[15];
    float f24 = fPlane[16]; float f25 = fPlane[17]; float f26 = fPlane[18]; float f27 = fPlane[19];
    float f28 = fPlane[20]; float f29 = fPlane[21]; float f30 = fPlane[22]; float f31 = fPlane[23];

    // Point array is at param_1, we treat it as a flat array of 4-component points.
    float* pointBase = (float*)points;
    float* outBase = (float*)outResults; // only used for temporary pointer, later cast to char

    for (int i = 0; i < pointCount; i++) {
        float* pfPoint = pointBase + i * 4;
        float fX = pfPoint[0];     // fVar1
        float fY = pfPoint[1];     // fVar3
        float fZ = pfPoint[2];     // fVar4
        float fW = pfPoint[3];     // fVar2

        // Compute two plane test results using f24..f27 and f28..f31 (planes 4 and 5)
        float fTemp38 = f27 * fGlobal + f26 * fZ;
        float fTemp39 = f25 * fY + f24 * fX;
        float fTemp40 = f31 * fGlobal + f30 * fZ;
        float fTemp41 = f29 * fY + f28 * fX;

        // Build 4-bit masks (only two distinct comparisons, replicated)
        uint32_t maskA_0 = (fW < fTemp39 + fTemp38) ? 0xFFFFFFFF : 0;
        uint32_t maskA_1 = (fW < fTemp41 + fTemp40) ? 0xFFFFFFFF : 0;
        // Replicate to fill 4 lanes (SSE style)
        uint32_t maskA_lo = maskA_0 | (maskA_1 << 8) | (maskA_1 << 16) | (maskA_0 << 24); // auVar6: first two lanes from maskA_0, next two from maskA_1? Actually decompiled pattern: [0]=maskA_1, [4]=maskA_0, [8]=maskA_1, [12]=maskA_0. So: 
        // Simplify: auVar6 = {maskA_1, maskA_0, maskA_1, maskA_0}
        // We'll just compute the movmskps result directly:
        uint32_t uMask6 = 0;
        if (maskA_0) uMask6 |= 0x2; // bit1 from lane4? Actually movmskps extracts sign bits of all four lanes; sign bits correspond to the most significant bit of each float. But here we have uint32_t masks. Since mask is all ones if true, the sign bit is set. So we can emulate by ORing 1<<lane for each true lane.
        // The order of lanes in MOVMSKPS: bits 0-3 for lanes 0-3. Lane order as per auVar6 layout: lanes = [maskA_1, maskA_0, maskA_1, maskA_0] (indices 0,1,2,3).
        if (maskA_1) uMask6 |= 0x1; // lane0
        if (maskA_0) uMask6 |= 0x2; // lane1
        if (maskA_1) uMask6 |= 0x4; // lane2
        if (maskA_0) uMask6 |= 0x8; // lane3
        // Actually easier: use decompiled's (uint)movmskps(result) which yields a 4-bit mask.

        // For simplicity, we compute the mask as done in the decompiled:
        // The decompiled constructs auVar6 as 4 uint32 and then calls movmskps. We'll just set bits directly.
        // Since auVar6._0_4_ = -(uint)(fW < fTemp41+fTemp40) etc., the sign bits are set. So we can compute maskA as:
        uint32_t uMaskA = 0;
        if (maskA_1) uMaskA |= 1; // lane0
        if (maskA_0) uMaskA |= 2; // lane1
        if (maskA_1) uMaskA |= 4; // lane2
        if (maskA_0) uMaskA |= 8; // lane3

        // Now compute four plane test results using f8..f23 (planes 0-3)
        float val0 = f9 * fY + f8 * fX + f11 * fGlobal + f10 * fZ;
        float val1 = f13 * fY + f12 * fX + f15 * fGlobal + f14 * fZ;
        float val2 = f21 * fY + f20 * fX + f23 * fGlobal + f22 * fZ;
        float val3 = f17 * fY + f16 * fX + f19 * fGlobal + f18 * fZ;

        // Build mask for these four planes
        uint32_t maskB_0 = (fW < val0) ? 0xFFFFFFFF : 0;
        uint32_t maskB_1 = (fW < val1) ? 0xFFFFFFFF : 0;
        uint32_t maskB_2 = (fW < val2) ? 0xFFFFFFFF : 0;
        uint32_t maskB_3 = (fW < val3) ? 0xFFFFFFFF : 0;

        // Construct auVar7 as [maskB_0, maskB_1, maskB_2, maskB_3]? Actually decompiled order: _0_4_ = maskB_1? Wait, check:
        // auVar7._0_4_ = -(uint)(fW < val1?) The decompiled has:
        // auVar7._0_4_ = -(uint)(fW < val for second plane? Actually looks like: first assign: f9*fY + f8*fX + f11*fGlobal + f10*fZ corresponds to plane0, but its mask is placed at offset 0 of auVar7? The decompiled shows:
        // auVar7._0_4_ = -(uint)(fW < f13*fY + f12*fX + f15*fGlobal + f14*fZ) -> plane1 mask at offset0.
        // auVar7._4_4_ = -(uint)(fW < f9*fY + f8*fX + f11*fGlobal + f10*fZ) -> plane0 mask at offset4.
        // auVar7._8_4_ = -(uint)(fW < f21*fY + f20*fX + f23*fGlobal + f22*fZ) -> plane3 mask at offset8? Actually third line uses f21,f20,f23,f22.
        // auVar7._12_4_ = -(uint)(fW < f17*fY + f16*fX + f19*fGlobal + f18*fZ) -> plane2 mask at offset12.
        // So the order of planes in auVar7 lanes: lane0 = plane1, lane1 = plane0, lane2 = plane3, lane3 = plane2.
        // We'll replicate that permutation.
        uint32_t uMaskB = 0;
        if (maskB_1) uMaskB |= 1; // lane0: plane1
        if (maskB_0) uMaskB |= 2; // lane1: plane0
        if (maskB_3) uMaskB |= 4; // lane2: plane3
        if (maskB_2) uMaskB |= 8; // lane3: plane2

        // Combine masks from both groups (OR them)
        uint32_t combinedMask = uMaskA | uMaskB;

        // Determine result byte: if any plane test failed (combined non-zero), use defaultMask; else 0.
        uint8_t resultByte = (combinedMask != 0) ? bDefault : 0;

        // Write to output buffer
        outResults[i] = (char)resultByte;
    }
}