// FUNC_NAME: WeaponAimBlend::updateBlend

#include <cstdint>

// Global constants (inferred from usage)
extern float g_fOne;          // DAT_00e2b1a4 = 1.0f
extern float g_fZero;         // DAT_00e2b1a0 = 0.0f
extern int g_limitLow;        // DAT_012058d0
extern int g_limitHigh;       // DAT_00f15988
extern int g_flagVar1;        // DAT_011f39f4
extern int g_flagVar2;        // DAT_011f3a10

// Animation resource globals
extern int g_resourceA;       // DAT_01198e48
extern int g_resourceB;       // DAT_01198e68
extern int g_resourceC;       // DAT_01198e50
extern int g_resourceD;       // DAT_01198e6c
extern int g_resourceE;       // DAT_01198e60
extern int g_resourceF;       // DAT_01198e58
extern int g_resourceG;       // DAT_01198e78
extern int g_resourceH;       // DAT_01198e74

// Resource handle globals (set in this function)
extern int g_hResource1;      // DAT_0121bc20
extern int g_hResource2;      // DAT_0121bc24
extern int* g_pResourceTable; // DAT_0121be7c (pointer to a table)
extern int* g_pConfigTable;   // DAT_0121bcd8 (pointer to a config block)
extern int* g_pAltConfig;     // DAT_0121bcd8? (actually used as temporary)
extern int g_externalHandle;  // DAT_012058e8 (compared to g_resourceTablePtr)
extern int g_resourceTablePtr; // DAT_0121bc10 (some base pointer)

// Lookup tables (13 entries and 3 entries)
extern int g_lookupTableA[13]; // PTR_DAT_010beba0
extern int g_lookupTableB[3];  // PTR_DAT_010bebd4

// Additional animation data arrays
extern float g_animData1[];   // DAT_01128170 (8-byte stride)
extern float g_animData2[];   // DAT_00e2cd54 (a constant)
extern float g_someVec1[3];   // DAT_00e44874
extern float g_someVec2[3];   // DAT_00e44640
extern float g_someVec3[3];   // DAT_00e2eff4

struct StateData {
    char unk0;          // +0x20
    char unk1;          // +0x21
    unsigned char idx;  // +0x22
    uint32_t flags;     // +0x24
    float offsetX;      // +0x2c
    float offsetY;      // +0x30
    float offsetZ;      // +0x34
    float param5C;      // +0x5c
    float param60;      // +0x60
    short param66;      // +0x66
    float param68;      // +0x68
    float param6C;      // +0x6c
    short param100;     // +0x64? Actually offset 100 = 0x64
    // Note: param100 is at offset 100 from iVar5, which is state pointer
};

struct Context {
    int field8;          // +0x08
    StateData* state;    // +0x14
    int field18;         // +0x18
    int field1C;         // +0x1c
    float field20;       // +0x20 (multiplier)
    int field24;         // +0x24 (handle)
    float speedScale;    // +0x28
};

// Forward declarations of external functions (renamed)
void funcStopAnimation(int handle);                // FUN_00606e60
void funcReleaseResource(int handle);              // FUN_0060a460
void funcBeginResourceSetup();                     // FUN_0053c6f0
void funcEndResourceSetup();                       // FUN_0053c670
void funcSetResourceValue(int resHandle, int param, float* vec); // FUN_0060add0
void funcSetResourceData(int resHandle, int data, float* extra); // FUN_0060b020
void funcUpdateResource(int handle);               // FUN_006063b0
void funcBlendVectors(float* a, float* b, float t); // FUN_0053ca50
void funcPlayEffect(int a, int b, int c);          // FUN_00417cf0
void funcApplyBlend(int handle, float a, float b, float c, float d, bool flag); // FUN_005330e0
void funcEndFrame();                                // FUN_00612e00

void WeaponAimBlend::updateBlend(Context* ctx) {
    StateData* state;
    float* timeStepPtr;
    float vecX, vecY, vecZ;
    float fVar7, fVar8, fVar9;
    float blend1, blend2, blend3, blend4;
    float vec2[3];
    bool flag2 = false;

    // Get time step from game state
    timeStepPtr = (float*)(**(int**)(*(int*)(0x2c + (int)__readfsdword(0)) + 8) + 0x80 + ctx->field8);
    vecX = timeStepPtr[0];
    vecY = timeStepPtr[1];
    vecZ = timeStepPtr[2];

    state = ctx->state;
    if ((state->flags & 6) == 0) {
        vecX += state->offsetX;
        vecY += state->offsetY;
        vecZ += state->offsetZ;
    }

    // Speed scaling
    fVar7 = ctx->speedScale;
    if (fVar7 > 0.0f) {
        if (fVar7 > g_fOne) fVar7 = g_fOne;
    } else {
        fVar7 = 0.0f;
    }
    float speedFactor = g_fOne;
    if (state->unk0 != 1) {
        speedFactor = g_fZero;
    }
    speedFactor *= fVar7;

    // Clamp global limits (weird logic)
    if (g_limitLow < 7) g_limitLow = 7;
    if (g_limitHigh > 7) g_limitHigh = 7;
    g_flagVar1 = ((state->flags >> 4) & 1) ^ 1;
    if (g_limitLow < 14) g_limitLow = 14;
    if (g_limitHigh > 14) g_limitHigh = 14;
    g_flagVar2 = ((state->flags >> 6) & 1);

    // Compute blend values for two axes
    fVar7 = state->param68;
    fVar9 = state->param6C;

    if (state->param100 < 2) {
        if (state->param100 == 1) {
            funcStopAnimation(ctx->field18, 0);
            blend1 = state->param5C * ctx->field20;
            blend2 = 0.0f;
        } else {
            blend1 = 0.0f;
            blend2 = 0.0f;
        }
    } else {
        float raw = state->param5C * ctx->field20;
        blend2 = (raw - (float)(int)raw) * (float)(int)state->param100;
        blend1 = (float)(int)blend2;
        blend2 -= blend1;
        blend1 *= fVar7;
    }

    if (state->param66 < 2) {
        blend3 = 0.0f;
        if (state->param66 == 1) {
            funcStopAnimation(ctx->field18, 0);
            blend3 = state->param60 * ctx->field20;
        }
    } else {
        float raw = state->param60 * ctx->field20;
        blend4 = (raw - (float)(int)raw) * (float)(int)state->param66;
        float whole = (float)(int)blend4;
        float frac = blend4 - whole;
        blend3 = whole * fVar9;
        // Note: blend4 is reused later, original code had local_38 reused
    }

    // Determine resource handles based on flags
    bool flagBit20 = (state->flags & 0x20) != 0;
    bool flagBit08 = (state->flags & 8) != 0;

    if (!flagBit20) {
        if (state->unk0 == 1) {
            g_hResource1 = g_resourceA;
            if (!flagBit08) {
                g_hResource2 = g_resourceB;
                if (g_externalHandle == g_resourceTablePtr) {
                    funcReleaseResource(g_resourceB);
                    funcReleaseResource(g_hResource1);
                }
                // Lookup for resource table from PTR_DAT_010beba0
                for (int i = 0; i < 13; i++) {
                    if (g_lookupTableA[i] == g_hResource2) {
                        g_pResourceTable = (int*)((int)&g_lookupTableA + i * 0x20); // approximate
                        break;
                    }
                }
                // Lookup for alternate table from PTR_DAT_010bebd4
                for (int i = 0; i < 3; i++) {
                    if (g_lookupTableB[i] == g_hResource1) {
                        goto foundConfig;
                    }
                }
            } else {
                g_hResource2 = g_resourceC;
                if (g_externalHandle == g_resourceTablePtr) {
                    funcReleaseResource(g_resourceC);
                    funcReleaseResource(g_hResource1);
                }
                // Similar lookups...
                for (int i = 0; i < 13; i++) {
                    if (g_lookupTableA[i] == g_hResource2) {
                        g_pResourceTable = (int*)((int)&g_lookupTableA + i * 0x20);
                        break;
                    }
                }
                for (int i = 0; i < 3; i++) {
                    if (g_lookupTableB[i] == g_hResource1) {
                        goto foundConfig;
                    }
                }
            }
        } else {
            if (ctx->field1C == 0) {
                funcBeginResourceSetup();
            } else {
                funcBeginResourceSetup();
                flag2 = true;
            }
        }
    } else {
        if (state->unk0 == 1) {
            g_hResource1 = g_resourceA;
            if (!flagBit08) {
                g_hResource2 = g_resourceD;
                if (g_externalHandle == g_resourceTablePtr) {
                    funcReleaseResource(g_resourceD);
                    funcReleaseResource(g_hResource1);
                }
                // Similar loops...
                for (int i = 0; i < 13; i++) {
                    if (g_lookupTableA[i] == g_hResource2) {
                        g_pResourceTable = (int*)((int)&g_lookupTableA + i * 0x20);
                        break;
                    }
                }
                for (int i = 0; i < 3; i++) {
                    if (g_lookupTableB[i] == g_hResource1) {
                        goto foundConfig;
                    }
                }
            } else {
                g_hResource2 = g_resourceE;
                if (g_externalHandle == g_resourceTablePtr) {
                    funcReleaseResource(g_resourceE);
                    funcReleaseResource(g_hResource1);
                }
                // Similar loops...
                for (int i = 0; i < 13; i++) {
                    if (g_lookupTableA[i] == g_hResource2) {
                        g_pResourceTable = (int*)((int)&g_lookupTableA + i * 0x20);
                        break;
                    }
                }
                for (int i = 0; i < 3; i++) {
                    if (g_lookupTableB[i] == g_hResource1) {
                        goto foundConfig;
                    }
                }
            }
        } else {
            if (ctx->field1C == 0) {
                g_hResource2 = g_resourceF;
                g_hResource1 = g_resourceA;
                if (g_externalHandle == g_resourceTablePtr) {
                    funcReleaseResource(g_resourceF);
                    funcReleaseResource(g_hResource1);
                }
                for (int i = 0; i < 13; i++) {
                    if (g_lookupTableA[i] == g_hResource2) {
                        g_pResourceTable = (int*)((int)&g_lookupTableA + i * 0x20);
                        break;
                    }
                }
                for (int i = 0; i < 3; i++) {
                    if (g_lookupTableB[i] == g_hResource1) {
                        goto foundConfig;
                    }
                }
            } else {
                g_hResource2 = g_resourceG;
                g_hResource1 = g_resourceH;
                if (g_externalHandle == g_resourceTablePtr) {
                    funcReleaseResource(g_resourceG);
                    funcReleaseResource(g_hResource1);
                }
                for (int i = 0; i < 13; i++) {
                    if (g_lookupTableA[i] == g_hResource2) {
                        g_pResourceTable = (int*)((int)&g_lookupTableA + i * 0x20);
                        break;
                    }
                }
                for (int i = 0; i < 3; i++) {
                    if (g_lookupTableB[i] == g_hResource1) {
                        g_pAltConfig = (int*)(i * 12 + 0x121bcb4); // fixed address
                        flag2 = true;
                        goto resourceDone;
                    }
                }
                flag2 = true;
            }
        }
    }

foundConfig:
    g_pAltConfig = (int*)(/* computed from loop index */ 0); // actually computed, but we reuse label
    // Note: The original flow goes to LAB_00532ca7

resourceDone:
    funcEndResourceSetup();

    if (g_pAltConfig != nullptr) {
        if (g_pAltConfig[1] != 0) {
            funcSetResourceData(g_hResource1, g_pAltConfig[1], (float*)0x1218d80); // fixed address
        }
        if (g_pAltConfig != nullptr && g_pAltConfig[2] != 0) {
            funcSetResourceData(g_hResource1, g_pAltConfig[2], (float*)0x1218dc0);
        }
        if (g_pAltConfig != nullptr && *g_pAltConfig != 0) {
            funcSetResourceValue(g_hResource1, *g_pAltConfig, (float*)&vecX);
        }
    }

    if (*g_pResourceTable != 0) {
        funcUpdateResource(0);
    }
    if (flag2 && g_pResourceTable[1] != 0) {
        funcUpdateResource(0);
    }

    state = ctx->state;
    if (state->unk0 == 1 || (state->flags & 0x20) != 0) {
        // Override vector from animation data table
        vecX = g_animData1[state->idx * 2];
        vecY = g_animData1[state->idx * 2 + 1];
        if (!(state->flags & 8)) {
            vecZ = 0.0f;
        } else {
            vecZ = g_fOne;
        }
        float factor = g_fOne - (g_fOne - blend2) * (g_fOne - blend1);
        if (g_pResourceTable[3] != 0) {
            float localVec[3] = {vecX, vecY, factor};
            funcSetResourceValue(g_hResource2, g_pResourceTable[3], localVec);
        }
        vecZ = fVar7 * 0.0f + blend1; // DAT_00e2cd54 is likely 0.0f
        float temp = fVar9 * 0.0f + blend3;
        vecX = fVar7;
        vecY = fVar9;
        if (g_pResourceTable[4] != 0) {
            float localVec[3] = {vecX, vecY, temp};
            funcSetResourceValue(g_hResource2, g_pResourceTable[4], localVec);
        }
    }

    char unk1 = state->unk1;
    if (state->unk0 == 1) {
        // Based on unk1, call blend and effect functions with different parameters
        if (unk1 == 1) {
            float u = g_someVec1[0], v = g_someVec1[1], w = g_someVec1[2];
            float x = g_someVec2[0], y = g_someVec2[1], z = g_someVec2[2];
            float a = g_someVec3[0], b = g_someVec3[1], c = g_someVec3[2];
            float blendData[3] = {u, v, w};
            funcBlendVectors(blendData, blendData);
            funcPlayEffect(5, 2, 2);
            goto finalize;
        }
        if (unk1 == 2) {
            // Similar with different constants
        } else if (unk1 == 3) {
            // Another set
        } else {
            // Default case
        }
    } else {
        if (unk1 == 0) {
            funcPlayEffect(1, 5, 2);
        } else if (unk1 == 1) {
            funcPlayEffect(1, 5, 6);
        } else if (unk1 == 2) {
            funcPlayEffect(3, 5, 2);
        } else {
            funcPlayEffect(1, 2, 1);
        }
    }

finalize:
    funcApplyBlend(ctx->field24, blend1, blend3, fVar7, fVar9, flag2);
    funcEndFrame();
    g_hResource1 = 0;
    g_hResource2 = 0;
}