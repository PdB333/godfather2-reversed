// FUNC_NAME: GlowRenderer::renderGlow
// Address: 0x0052a8a0
// Purpose: Renders a glow/light effect (likely for billboard sprites or light maps).
// Uses projection math to compute screen-space bounding box, then iterates over pixels
// to accumulate a weighted glow contribution into a global buffer (DAT_01197da0).
// Supports various falloff types: None(0), Linear(1), Quadratic(2), Exponential(3), Random(4).

#include <cstdint>

// Forward declarations
extern float gMatrix4x4[16];          // DAT_01218e00-0x3c (row-major 4x4 matrix)
extern float gFalloffWeightsX[32];    // DAT_01198da0 (lookup table, size 32)
extern float gFalloffWeightsY[32];    // DAT_01198da0 (same array? indexed by y)
extern float gGlowBuffer[32*32];      // DAT_01197da0 (output glow accumulation buffer)
extern float kOne;                    // DAT_00e2b1a4 (1.0f)
extern float kPixelScale;             // DAT_00e446f0 (scales to integer pixel coords)
extern float kInvPixelSize;           // DAT_00e2d848 (1/32 or similar)
extern float kFalloffConstant1;       // DAT_00e2b04c
extern float kFalloffConstant2;       // DAT_00e2cd54
extern float kFalloffConstant3;       // DAT_00e44718
extern float kMinThreshold;           // DAT_00e2e210
extern float kOffset1;                // DAT_00e2cd54 (same as above but used differently)
extern float kOffset2;                // DAT_00e44718

// Unknown math function (likely sin/cos or exp)
void __fastcall mathFunc();  // FUN_00b99fcb (probabilistic / trig)

// Random number generator returning a float (bitshifted)
uint32_t __fastcall getRandomUint(); // FUN_004e9200

// Post-processing function (maybe blit or downscale)
void __fastcall applyGlow(uint32_t param); // FUN_0052b390

enum FalloffType {
    kFalloffNone      = 0,
    kFalloffLinear    = 1,
    kFalloffQuadratic = 2,
    kFalloffExponential = 3,
    kFalloffRandom    = 4
};

struct GlowParams {
    uint32_t flags;       // +0x04 (bits 0:?, 1:?, 2:?, 3:? 0x8: no attenuation, 0x10: use size, 0x20: post-process)
    float posX;           // +0x14
    float posY;           // +0x18
    float posZ;           // +0x1C
    float attenuation;    // +0x44
    float intensity;      // +0x48
    float radius;         // +0x4C
    float exponent;       // +0x50
};

struct RenderState {
    // 0x00: some pointer
    // 0x50: matrix row 0
    // 0x54: matrix row 1
    // 0x58: matrix row 2
    // 0x5C: matrix row 3
    // 0x60: modelview row 0
    // 0x64: modelview row 1
    // 0x68: modelview row 2
    // 0x6C: modelview row 3
    // 0x70: projection row 0
    // 0x74: projection row 1
    // 0x78: projection row 2
    // 0x7C: projection row 3
    // 0x80: viewport x0
    // 0x84: viewport y0
    // 0x88: viewport x1
    // 0x8C: viewport y1
    // 0x90: near plane
    // 0x94: far plane
};

struct CameraInfo {
    // +0x144: near cut (zNear)
    // +0x148: far cut (zFar)
    float zNear;
    float zFar;
};

void __thiscall GlowRenderer::renderGlow(int param_1, int param_2) {
    // param_1 = this (offset layout below)
    // param_2 = CameraInfo pointer

    // Get TLS pointer to render state (via FS:[0x2C] -> pointer -> +8 -> +0x8)
    // This yields a RenderState struct pointer
    uint8_t* statePtr = *(uint8_t**)(**(uint32_t**)(__readfsdword(0x2C) + 8) + 8) + *(uint32_t*)(param_1 + 8);

    // Early discard if the first bit of statePtr is set and data type is 4 (some flag)
    if ((*statePtr & 1) == 0 || *(**(char***)(param_1 + 0x10)) != 4) {
        // Pointer to GlowParams (param_1+0x10)
        uint32_t glowParamsPtr = *(uint32_t*)(param_1 + 0x10);
        float* glowPos = (float*)(glowParamsPtr + 0x14); // +0x14 (posX, posY, posZ)

        // Load position from glowParams
        float posX = glowPos[0];  // +0x14
        float posY = glowPos[1];  // +0x18
        float posZ = glowPos[2];  // +0x1C

        // Project point to screen-space using modelview-projection matrix from statePtr
        // statePtr + 0x50/0x54/0x58/0x5C are rows of modelview matrix?
        // Actually, the code uses statePtr+0x50,0x54,0x58,0x5C and +0x60,0x64,0x68,0x6C
        // and +0x70,0x74,0x78,0x7C; we'll compute clip-space coordinates.
        float* projRow0 = (float*)(statePtr + 0x50);
        float* projRow1 = (float*)(statePtr + 0x54);
        float* projRow2 = (float*)(statePtr + 0x58);
        float* projRow3 = (float*)(statePtr + 0x5C);

        float clipX = posX * projRow0[0] + posY * projRow0[1] + posZ * projRow0[2] + kOne * projRow0[3];
        float clipY = posX * projRow1[0] + posY * projRow1[1] + posZ * projRow1[2] + kOne * projRow1[3];
        float clipZ = posX * projRow2[0] + posY * projRow2[1] + posZ * projRow2[2] + kOne * projRow2[3];
        float clipW = posX * projRow3[0] + posY * projRow3[1] + posZ * projRow3[2] + kOne * projRow3[3];

        // Calculate depth (clipW? actually it's used as depth for z-check)
        float depth = clipX * gMatrix4x4[ 4] + clipY * gMatrix4x4[ 5] + clipZ * gMatrix4x4[ 6] + clipW * gMatrix4x4[ 7];
        // depth might be in some space, compare with zNear/zFar from CameraInfo
        CameraInfo* cam = (CameraInfo*)param_2;
        if (cam->zNear <= depth && (depth < cam->zFar || depth == cam->zFar)) {
            // Compute scale factor (1/clipW? but stored as kOne/clipW)
            float invW = kOne / (clipX * gMatrix4x4[12] + clipY * gMatrix4x4[13] + clipZ * gMatrix4x4[14] + clipW * gMatrix4x4[15]);

            // Compute screen-space coordinates (with offsets)
            float screenX = invW * (clipX * gMatrix4x4[ 8] + clipY * gMatrix4x4[ 9] + clipZ * gMatrix4x4[10] + clipW * gMatrix4x4[11]) * kFalloffConstant3 + kOffset1;
            float screenY = invW * (clipX * gMatrix4x4[ 0] + clipY * gMatrix4x4[ 1] + clipZ * gMatrix4x4[ 2] + clipW * gMatrix4x4[ 3]) * kOffset1 + kOffset1;

            // Determine depth factor (attenuation)
            float depthFactor;
            if ((*(uint32_t*)(glowParamsPtr + 0x4) & 0x8) == 0) {
                depthFactor = kOne / depth; // default: inverse depth
            } else {
                depth = kOne;
                depthFactor = kOne;
            }

            // Compute screen-space size (radius * depthFactor)
            float radiusSS = *(float*)(param_1 + 0x20) * depthFactor; // maybe size multiplier

            // Check bounding: screen coordinates must be within [0,1] after adding/subtracting radius
            if ( screenX + radiusSS > 0.0f && screenY + radiusSS > 0.0f &&
                 screenX - radiusSS < kOne && screenY - radiusSS < kOne ) {
                // Pre-compute squared radius (radiusSS^2 * 2? Actually fVar23 = fVar20*fVar20*2)
                float sqRadius = radiusSS * radiusSS * 2.0f; // fVar23 = 2*r^2

                // sizeMultiplier (optional scaling from glowParams)
                float sizeMult = *(float*)(param_1 + 0x18); // +0x18
                if ((*(uint32_t*)(glowParamsPtr + 0x4) & 0x10) == 0) {
                    sizeMult = *(float*)(param_1 + 0x24) * sizeMult * depthFactor;
                }

                // Threshold check
                if (kMinThreshold < sizeMult && kMinThreshold < sqRadius) {
                    // Compute integer bounding box in pixel coordinates (32x32 tile)
                    int left   = (int)(((screenX - radiusSS) - kOne) * kPixelScale);
                    int right  = (int)(( screenX + radiusSS + kOne ) * kPixelScale);
                    int bottom = (int)(((screenY - radiusSS) - kOne) * kPixelScale);
                    int top    = (int)(( screenY + radiusSS + kOne ) * kPixelScale);

                    // Clamp to [0,31] and compute loop bounds
                    int iBottom = ((int)(bottom >> 31) & bottom) ? bottom : 0; // max(0, bottom)
                    iBottom = ~((int)bottom >> 31) & bottom; // actually: if negative, use 0 else use bottom
                    // Wait, the decompiled code uses complex clamping:
                    // iVar12 = (~((int)uVar2 >> 0x1f) & uVar2) + 1;
                    // uVar2 = left? Actually, let's re-index.
                    // In decompiled: uVar2 = left, uVar5 = right, uVar8 = bottom, uVar10 = top
                    // iVar12 = max(0, left) + 1; iVar13 = min(31, right-1) ??? 
                    // The code uses bit tricks:
                    // iVar12 = (uVar2 & ~(uVar2>>31)) + 1   // max(0, left) + 1
                    // iVar13 = (uVar3 & uVar5 | ~uVar3 & 0x1f) - 1
                    // where uVar3 = (uVar5 - 0x20)>>31   // if right >= 32 then uVar3 = 0 else -1
                    // So iVar13 = (right & (right>=32?0:0x1f) ) - 1? Actually it's min(31, right) - 1
                    // Similarly iVar9 = min(31, top) - 1, iVar6 = max(0, bottom)

                    // For simplicity, we'll write a cleaner version using min/max.
                    int xStart = max(0, left);
                    int xEnd   = min(31, right - 1);
                    int yStart = max(0, bottom);
                    int yEnd   = min(31, top - 1);

                    // Glow attenuation from glowParams
                    float atten = *(float*)(glowParamsPtr + 0x44); // +0x44
                    if ((*(uint8_t*)(glowParamsPtr + 4) & 4) == 0) {
                        atten = atten * depthFactor; // depth-scaled
                    }

                    float invSqRadiusMinAtten = sqRadius - atten * atten * kFalloffConstant1; // fVar14

                    // Loop over pixels in bounding box
                    for (int iy = yStart; iy <= yEnd; iy++) {
                        float dy = (float)iy * kInvPixelSize - screenY; // negative offset from center
                        for (int ix = xStart; ix <= xEnd; ix++) {
                            float dx = (float)ix * kInvPixelSize - screenX;
                            float distSq = dx*dx + dy*dy;

                            if (distSq < sqRadius) {
                                float falloff = distSq / sqRadius; // normalized distance squared
                                float weight = 0.0f;

                                uint32_t type = *(uint8_t*)(glowParamsPtr); // falloff type
                                switch (type) {
                                case kFalloffNone:
                                    // Use no falloff if current distSq > invSqRadiusMinAtten (i.e., outside a certain range)
                                    if (invSqRadiusMinAtten < distSq) {
                                        float t = kOne - falloff; // 1 - d^2/r^2
                                        // mix with some intensity from glowParams+0x48 and +0x50
                                        double intensity = (double)( (*(float*)(glowParamsPtr+0x48) * *(float*)(param_1+0x14)) + 
                                                                     (*(float*)(glowParamsPtr+0x50) * t) );
                                        mathFunc(); // some math (maybe exp or sin)
                                        weight = (float)intensity * t;
                                    }
                                    break;
                                case kFalloffLinear:
                                    weight = kOne - (kFalloffConstant2 - falloff * kFalloffConstant1) * falloff * falloff;
                                    break;
                                case kFalloffQuadratic:
                                    if (invSqRadiusMinAtten < distSq) {
                                        float t2 = (kOne - (kOne - falloff)) * (kOne - falloff) * kFalloffConstant3;
                                        weight = t2 * t2;
                                    }
                                    break;
                                case kFalloffExponential:
                                    {   // Exponential falloff with intensity and radius
                                        float intensity1 = *(float*)(param_1+0x14);
                                        double expArg = (double)( (*(float*)(glowParamsPtr+0x50) * dx * depth) +
                                                                  (*(float*)(glowParamsPtr+0x48) * intensity1) );
                                        mathFunc(); // maybe exp
                                        double expRes = (double)( (float)expArg * (*(float*)(glowParamsPtr+0x44)) +
                                                                   (dy * depth + intensity1) * (*(float*)(glowParamsPtr+0x4C)) );
                                        mathFunc(); // wrap
                                        weight = (float)expRes * (kOne - falloff);
                                    }
                                    break;
                                case kFalloffRandom:
                                    if (invSqRadiusMinAtten < distSq) {
                                        uint32_t rnd = getRandomUint(); // random bits
                                        // Construct float: upper bits OR with 0x3f800000 -> 1.0f
                                        float rndFloat = *(float*)&((rnd >> 8) | 0x3f800000);
                                        weight = (rndFloat - kOne) * (kOne - falloff);
                                    }
                                    break;
                                }

                                // Accumulate into buffer with spatial weights from lookup table
                                // gFalloffWeightsX[ix] and gFalloffWeightsY[iy]
                                int idx = iy * 32 + ix;
                                gGlowBuffer[idx] += weight * sizeMult * gFalloffWeightsX[ix] * gFalloffWeightsY[iy];
                            }
                        }
                    }

                    // If flag 0x20 is set, call post-process function
                    if ((*(uint8_t*)(glowParamsPtr + 4) & 0x20) != 0) {
                        applyGlow(*(uint32_t*)(param_1 + 0x1c));
                    }
                }
            }
        }
    }
}