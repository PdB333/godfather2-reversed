// FUNC_NAME: ToneMapHelperFunction
// Address: 0x007223d0

#include <cmath>
#include <cstdint>

// Global constants (unknown actual values, used as defaults)
extern const float g_colorScaleR;  // 0x00d62058
extern const float g_colorScaleG;  // 0x00d62054
extern const float g_threshold;    // 0x00d62050
extern const float g_lowBound;     // 0x00d5780c
extern const float g_highBound;    // 0x00d5ccf8
extern const uint32_t g_absMask;   // 0x00e44680 (likely 0x7FFFFFFF)
extern const float g_constE44720;  // 0x00e44720
extern const float g_constE44564;  // 0x00e44564
extern const float g_scaleFactor;  // 0x00d5ef9c
extern const float g_constE448F0;  // 0x00e448f0
extern const float g_constE448F4;  // 0x00e448f4
extern const float g_maxClamp;     // 0x00d5f4b4

struct ToneMapData {
    float inputB;   // +0x10
    float inputA;   // +0x14
    float outputX;  // +0x18
    float outputY;  // +0x1c
    float outputZ;  // +0x20
};

int __fastcall ToneMapHelperFunction(ToneMapData* data) {
    float fVar10 = g_highBound;
    float fVar7 = g_lowBound;
    float local_c[3];
    
    // Process second input (offset +0x14)
    local_c[0] = data->inputB * g_colorScaleR;  // +0x14 * g_colorScaleR
    local_c[1] = g_lowBound;
    local_c[2] = g_highBound;
    
    float* pfVar4;
    if (local_c[0] <= g_lowBound) {
        pfVar4 = local_c + 2;  // point to high bound
        if (g_highBound <= local_c[0]) {
            pfVar4 = local_c;  // actually inside range, point to itself
        }
    } else {
        pfVar4 = local_c + 1;  // point to low bound
    }
    float fVar1 = *pfVar4;  // selected clamped value
    data->outputZ = fVar1;   // store at +0x20

    // Process first input (offset +0x10)
    local_c[0] = data->inputA * g_colorScaleG; // +0x10 * g_colorScaleG
    float fVar3 = g_threshold;
    local_c[2] = g_lowBound;   // swapped order
    local_c[1] = g_highBound;

    if (local_c[0] <= g_lowBound) {
        pfVar4 = local_c + 1;  // point to high bound
        if (g_highBound <= local_c[0]) {
            pfVar4 = local_c;  // inside range
        }
    } else {
        pfVar4 = local_c + 2;  // point to low bound
    }
    float fVar7_new = *pfVar4;  // selected clamped value
    bool bVar2 = (local_c[0] == fVar7_new);  // equality flag

    // Compute absolute-value-like quantities
    float fVar9 = reinterpret_cast<float>(reinterpret_cast<uint32_t>(fVar1) & g_absMask);
    float fVar8 = reinterpret_cast<float>(reinterpret_cast<uint32_t>(fVar7_new) & g_absMask);
    float fVar10_2 = fVar8;
    if (fVar8 <= fVar9) {
        fVar10_2 = fVar9;
    }
    data->outputX = fVar10_2;  // store at +0x18

    if (fVar10_2 <= fVar3) {
        // Below threshold, simple assignment
        data->outputY = g_constE44720;
        // Pack return flags
        int ret = 2U; // bit1 set
        ret |= (local_c[0] < fVar7_new) ? 1 : 0;
        ret |= (std::isnan(local_c[0]) || std::isnan(fVar7_new)) ? 4 : 0;
        ret |= bVar2 ? 0x40 : 0;
        return ret;
    }

    // Above threshold, compute outputY using piecewise formula
    if (fVar1 < fVar8) {
        if (g_constE44564 - fVar8 < fVar1) {
            if (fVar9 <= fVar7_new) {
                data->outputY = (fVar1 / fVar10_2) * g_scaleFactor + g_constE448F0;
                goto clamp;
            }
            fVar7_new = g_scaleFactor - (fVar1 / fVar10_2) * g_scaleFactor;
        } else {
            fVar7_new = (fVar7_new / fVar10_2) * g_scaleFactor + g_constE44720;
        }
        data->outputY = fVar7_new;
    } else {
        data->outputY = g_constE448F4 - (fVar7_new / fVar10_2) * g_scaleFactor;
    }

clamp:
    // Clamp outputY to [0, g_maxClamp]
    if (g_maxClamp < data->outputY) {
        data->outputY = g_maxClamp;
    } else if (0.0f > data->outputY) {
        data->outputY = 0.0f;
    }

    // Pack return flags
    int ret = 2U;
    ret |= (local_c[0] < fVar7_new) ? 1 : 0;
    ret |= (std::isnan(local_c[0]) || std::isnan(fVar7_new)) ? 4 : 0;
    ret |= bVar2 ? 0x40 : 0;
    return ret;
}