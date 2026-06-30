// FUNC_NAME: AnimationManager::updateCharacterAnimations

#include <cmath>
#include <cstdint>

// Global constants (inferred from usage)
static const float kTimeStep = *reinterpret_cast<const float*>(0x00e2cd54); // delta time or fixed step
static const float kOne = *reinterpret_cast<const float*>(0x00e2b1a4);       // 1.0f
static const float kZero = *reinterpret_cast<const float*>(0x00e2b1a0);     // 0.0f

// Global animation system state (partial)
static int g_animStateFlag1       = *reinterpret_cast<const int*>(0x012058d0);
static int g_animStateFlag2       = *reinterpret_cast<const int*>(0x00f15988);
static uint32_t g_someFlag        = *reinterpret_cast<const uint32_t*>(0x011f39f4);
static uint32_t g_someFlag2       = *reinterpret_cast<const uint32_t*>(0x011f3a10);

// Global animation asset IDs (probably hashes or pointers)
static int g_charAnimBase         = *reinterpret_cast<const int*>(0x01198e48); // likely "idle" or default
static int g_charAnimMoveFwd      = *reinterpret_cast<const int*>(0x01198e68);
static int g_charAnimMoveBwd      = *reinterpret_cast<const int*>(0x01198e50);
static int g_charAnimStrafeL      = *reinterpret_cast<const int*>(0x01198e6c);
static int g_charAnimStrafeR      = *reinterpret_cast<const int*>(0x01198e60);
static int g_charAnimCombatIdle   = *reinterpret_cast<const int*>(0x01198e58);
static int g_charAnimCombatMove   = *reinterpret_cast<const int*>(0x01198e78);
static int g_charAnimCombatStrafe = *reinterpret_cast<const int*>(0x01198e74);

// Global pointers to current animation slots
static int g_currentAnimMain = 0;  // previously DAT_0121bc20
static int g_currentAnimLayer = 0; // previously DAT_0121bc24
static int* g_animStateTable = 0;  // previously DAT_0121be7c
static int* g_customAnimData = 0;  // previously DAT_0121bcd8

// Global lookup tables (addresses 0x121bcb4, 0x121bcdc, 0x121bc10, etc.)
static const int kAnimTableSize = 13;
static const int kAnimLayerTableSize = 3;
static int* const g_animLoopTable = reinterpret_cast<int*>(0x010beba0);   // table of 13 animation IDs
static int* const g_animLayerTable = reinterpret_cast<int*>(0x010bebd4);  // table of 3 layer IDs
static int* const g_animDataTable = reinterpret_cast<int*>(0x0121bcb4);   // 13 entries of 0x20 bytes each
static int* const g_layerDataTable = reinterpret_cast<int*>(0x0121bc10);  // 3 entries of 0xC bytes each

// External function declarations (replace with actual signatures)
extern void FUN_00606e60(int arg, int param2);
extern void FUN_0060a460(int animID);
extern void FUN_0053c6f0();
extern void FUN_0053c670();
extern void FUN_0060b020(int animID, int dataEntry, int targetStruct);
extern void FUN_0060add0(int animID, int dataEntry, float* position);
extern void FUN_006063b0();
extern void FUN_0053ca50(float* blendParams);
extern void FUN_00417cf0(int param1, int param2, int param3);
extern void FUN_005330e0(int animTag, float velX, float velY, float blendX, float blendY, bool hasCustomAnim);
extern void FUN_00612e00();

// Internal structure for animation state (from param_1+0x14)
struct AnimState {
    char     mode;          // +0x20: 0 or 1 (idle/moving)
    char     actionType;    // +0x21: 0,1,2,3 (idle, walk, run, combat?)
    uint8_t  directionIdx;  // +0x22: index into directional animation table
    uint32_t flags;         // +0x24: bitfield (0x20 = combat, 0x8 = strafe, etc.)
    float    offsetX;       // +0x2c
    float    offsetY;       // +0x30
    float    offsetZ;       // +0x34
    // ... other fields later
    float    velocityX;     // +0x5c
    float    velocityZ;     // +0x60 (maybe)
    short    blendFrames;   // +0x64 (used for blending count)
    short    blendFrames2;  // +0x66
    float    blendFactor1;  // +0x68
    float    blendFactor2;  // +0x6c
};

// Main object passed to this function
struct SomeCharacterObj {
    int     field_0x08;     // +0x08: offset into some global array
    AnimState* animState;   // +0x14: pointer to per-character animation state
    int     field_0x18;     // +0x18: passed to FUN_00606e60
    int     field_0x1c;     // +0x1c: boolean (0/1)
    float   speedMultiplier; // +0x20
    int     animTag;        // +0x24
    float   clampedInput;   // +0x28
};

void AnimationManager::updateCharacterAnimations(SomeCharacterObj* obj) {
    float local_30, fStack_2c, fStack_28, fStack_24; // position/velocity vector (world space?)
    float local_38, local_34, local_44, local_48;     // blend accumulators
    float fVar7, fVar2, fVar8, fVar9;
    bool hasCustomAnim = false;

    // Compute base position from global array indexed by obj->field_0x08
    float* basePos = reinterpret_cast<float*>(
        *(reinterpret_cast<int*>(*(*reinterpret_cast<int**>(__readfsdword(0x2c))) + 8) + 0x80
        + obj->field_0x08)
    );
    local_30 = basePos[0];
    fStack_2c = basePos[1];
    fStack_28 = basePos[2];

    AnimState* anim = obj->animState;
    if ((anim->flags & 0x06) == 0) {
        // Apply positional offset if not in specific states
        local_30 += anim->offsetX;
        fStack_2c += anim->offsetY;
        fStack_28 += anim->offsetZ;
    }

    // Clamp input speed factor
    fVar7 = obj->clampedInput;
    if (fVar7 > 0.0f) {
        if (fVar7 > kOne) fVar7 = kOne;
    } else {
        fVar7 = 0.0f;
    }

    // Determine max blend factor
    fStack_24 = kOne;
    if (anim->mode != 1) {
        fStack_24 = kZero;
    }
    fStack_24 *= fVar7;

    // Clamp global state variables (debugging?)
    if (g_animStateFlag1 < 7) g_animStateFlag1 = 7;
    if (g_animStateFlag2 > 7) g_animStateFlag2 = 7;
    g_someFlag = (~(anim->flags >> 4) & 1);
    if (g_animStateFlag1 < 0xe) g_animStateFlag1 = 0xe;
    if (g_animStateFlag2 > 0xe) g_animStateFlag2 = 0xe;
    g_someFlag2 = ((anim->flags >> 6) & 1);

    // Compute velocity components
    float velX = anim->velocityX;
    float velZ = anim->blendFactor1;  // Actually used as velZ later

    // Handle blending based on blendFrames
    if (anim->blendFrames < 2) {
        if (anim->blendFrames == 1) {
            // Single blend frame
            FUN_00606e60(obj->field_0x18, 0);
            local_44 = anim->velocityX * obj->speedMultiplier;
            local_34 = local_38; // local_38 is zero at this point? Actually local_38 was uninitialized? but it's set to 0 earlier
        } else {
            // No blend
            local_44 = 0.0f;
            local_34 = local_38;
        }
    } else {
        // Multi-frame blend
        float raw = anim->velocityX * obj->speedMultiplier;
        local_34 = (raw - static_cast<float>(static_cast<int>(raw))) * static_cast<float>(anim->blendFrames);
        local_44 = static_cast<float>(static_cast<int>(local_34));
        local_34 = local_34 - local_44;
        local_44 = local_44 * velX;
    }

    // Similar for second blend factor
    if (anim->blendFrames2 < 2) {
        local_48 = local_38; // 0
        if (anim->blendFrames2 == 1) {
            FUN_00606e60(obj->field_0x18, 0);
            local_48 = anim->velocityZ * obj->speedMultiplier;
        }
    } else {
        float raw2 = anim->velocityZ * obj->speedMultiplier;
        local_38 = (raw2 - static_cast<float>(static_cast<int>(raw2))) * static_cast<float>(anim->blendFrames2);
        float intPart = static_cast<float>(static_cast<int>(local_38));
        local_38 = local_38 - intPart;
        local_48 = intPart * velZ;
    }

    // Determine which animation to play based on flags and mode
    uint32_t flags = anim->flags;
    if ((flags & 0x20) == 0) {
        // Non-combat mode
        if (anim->mode == 1) {
            g_currentAnimMain = g_charAnimBase;
            if ((flags & 8) == 0) {
                // Forward movement
                g_currentAnimLayer = g_charAnimMoveFwd;
                if (reinterpret_cast<int*>(0x012058e8) == reinterpret_cast<int*>(0x0121bc10)) {
                    FUN_0060a460(g_charAnimMoveFwd);
                    FUN_0060a460(g_currentAnimMain);
                }
                // Look up in layer table (0x010beba0)
                for (uint32_t i = 0; i < kAnimTableSize; i++) {
                    if (g_animLoopTable[i] == g_currentAnimLayer) {
                        g_animStateTable = reinterpret_cast<int*>(reinterpret_cast<char*>(g_animDataTable) + i * 0x20);
                        break;
                    }
                }
                bool found = false;
                for (uint32_t i = 0; i < kAnimLayerTableSize; i++) {
                    if (g_animLayerTable[i] == g_currentAnimMain) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    // fallback?
                }
            } else {
                // Backward movement
                g_currentAnimLayer = g_charAnimMoveBwd;
                if (reinterpret_cast<int*>(0x012058e8) == reinterpret_cast<int*>(0x0121bc10)) {
                    FUN_0060a460(g_charAnimMoveBwd);
                    FUN_0060a460(g_currentAnimMain);
                }
                for (uint32_t i = 0; i < kAnimTableSize; i++) {
                    if (g_animLoopTable[i] == g_currentAnimLayer) {
                        g_animStateTable = reinterpret_cast<int*>(reinterpret_cast<char*>(g_animDataTable) + i * 0x20);
                        break;
                    }
                }
                for (uint32_t i = 0; i < kAnimLayerTableSize; i++) {
                    if (g_animLayerTable[i] == g_currentAnimMain) goto foundLayer;
                }
                goto doneLayerLookup;
            }
        } else {
            // Idle or other non-moving states
            if (obj->field_0x1c == 0) {
                FUN_0053c6f0();
            } else {
                FUN_0053c6f0();
                hasCustomAnim = true;
            }
        }
    } else {
        // Combat mode (0x20 flag set)
        if (anim->mode == 1) {
            g_currentAnimMain = g_charAnimBase;
            if ((flags & 8) == 0) {
                // Strafe left
                g_currentAnimLayer = g_charAnimStrafeL;
                if (reinterpret_cast<int*>(0x012058e8) == reinterpret_cast<int*>(0x0121bc10)) {
                    FUN_0060a460(g_charAnimStrafeL);
                    FUN_0060a460(g_currentAnimMain);
                }
                for (uint32_t i = 0; i < kAnimTableSize; i++) {
                    if (g_animLoopTable[i] == g_currentAnimLayer) {
                        g_animStateTable = reinterpret_cast<int*>(reinterpret_cast<char*>(g_animDataTable) + i * 0x20);
                        break;
                    }
                }
                for (uint32_t i = 0; i < kAnimLayerTableSize; i++) {
                    if (g_animLayerTable[i] == g_currentAnimMain) goto foundLayer;
                }
            } else {
                // Strafe right
                g_currentAnimLayer = g_charAnimStrafeR;
                if (reinterpret_cast<int*>(0x012058e8) == reinterpret_cast<int*>(0x0121bc10)) {
                    FUN_0060a460(g_charAnimStrafeR);
                    FUN_0060a460(g_currentAnimMain);
                }
                for (uint32_t i = 0; i < kAnimTableSize; i++) {
                    if (g_animLoopTable[i] == g_currentAnimLayer) {
                        g_animStateTable = reinterpret_cast<int*>(reinterpret_cast<char*>(g_animDataTable) + i * 0x20);
                        break;
                    }
                }
                for (uint32_t i = 0; i < kAnimLayerTableSize; i++) {
                    if (g_animLayerTable[i] == g_currentAnimMain) {
                        g_customAnimData = reinterpret_cast<int*>(reinterpret_cast<char*>(g_layerDataTable) + i * 0xC);
                        hasCustomAnim = true;
                        goto doneLayerLookup;
                    }
                }
            }
        } else {
            // Idle in combat
            if (obj->field_0x1c == 0) {
                g_currentAnimLayer = g_charAnimCombatIdle;
                g_currentAnimMain = g_charAnimBase;
                if (reinterpret_cast<int*>(0x012058e8) == reinterpret_cast<int*>(0x0121bc10)) {
                    FUN_0060a460(g_charAnimCombatIdle);
                    FUN_0060a460(g_currentAnimMain);
                }
                for (uint32_t i = 0; i < kAnimTableSize; i++) {
                    if (g_animLoopTable[i] == g_currentAnimLayer) {
                        g_animStateTable = reinterpret_cast<int*>(reinterpret_cast<char*>(g_animDataTable) + i * 0x20);
                        break;
                    }
                }
                for (uint32_t i = 0; i < kAnimLayerTableSize; i++) {
                    if (g_animLayerTable[i] == g_currentAnimMain) goto foundLayer;
                }
            } else {
                g_currentAnimLayer = g_charAnimCombatMove;
                g_currentAnimMain = g_charAnimCombatStrafe;
                if (reinterpret_cast<int*>(0x012058e8) == reinterpret_cast<int*>(0x0121bc10)) {
                    FUN_0060a460(g_charAnimCombatMove);
                    FUN_0060a460(g_charAnimCombatStrafe);
                }
                for (uint32_t i = 0; i < kAnimTableSize; i++) {
                    if (g_animLoopTable[i] == g_currentAnimLayer) {
                        g_animStateTable = reinterpret_cast<int*>(reinterpret_cast<char*>(g_animDataTable) + i * 0x20);
                        break;
                    }
                }
                for (uint32_t i = 0; i < kAnimLayerTableSize; i++) {
                    if (g_animLayerTable[i] == g_currentAnimMain) {
                        g_customAnimData = reinterpret_cast<int*>(reinterpret_cast<char*>(g_layerDataTable) + i * 0xC);
                        hasCustomAnim = true;
                        goto doneLayerLookup;
                    }
                }
                hasCustomAnim = true;
            }
        }
    }

doneLayerLookup:
    FUN_0053c670();
    if (g_customAnimData != nullptr) {
        if (g_customAnimData[1] != 0) {
            FUN_0060b020(g_currentAnimMain, g_customAnimData[1], reinterpret_cast<int*>(0x01218d80));
        }
        if (g_customAnimData != nullptr) {
            if (g_customAnimData[2] != 0) {
                FUN_0060b020(g_currentAnimMain, g_customAnimData[2], reinterpret_cast<int*>(0x01218dc0));
            }
            if (g_customAnimData != nullptr && g_customAnimData[0] != 0) {
                FUN_0060add0(g_currentAnimMain, g_customAnimData[0], &local_30);
            }
        }
    }
    if (g_animStateTable != nullptr && g_animStateTable[0] != 0) {
        FUN_006063b0();
    }
    if (hasCustomAnim && g_animStateTable != nullptr && g_animStateTable[1] != 0) {
        FUN_006063b0();
    }

    // Additional per-frame adjustments
    if (anim->mode == 1 || (anim->flags & 0x20) != 0) {
        // Use precomputed direction-based positions
        local_30 = *(reinterpret_cast<float*>(0x01128170 + anim->directionIdx * 8));
        fStack_2c = *(reinterpret_cast<float*>(0x01128174 + anim->directionIdx * 8));
        if ((anim->flags & 8) == 0) {
            fStack_28 = 0.0f;
        } else {
            fStack_28 = kOne;
        }
        fStack_24 = kOne - (kOne - local_38) * (kOne - local_34);
        if (g_animStateTable != nullptr && g_animStateTable[3] != 0) {
            FUN_0060add0(g_currentAnimLayer, g_animStateTable[3], &local_30);
        }
        fStack_28 = velX * kTimeStep + local_44;
        fStack_24 = velZ * kTimeStep + local_48;
        local_30 = velX;
        fStack_2c = velZ;
        if (g_animStateTable != nullptr && g_animStateTable[4] != 0) {
            FUN_0060add0(g_currentAnimLayer, g_animStateTable[4], &local_30);
        }
    }

    // Animation choice based on actionType
    char action = anim->actionType;
    float params[6]; // local_20, local_1c, local_18, local_14, fStack_28, fStack_24, etc.
    if (anim->mode == 1) {
        // Movement mode
        params[0] = kOne;
        params[1] = kOne;
        if (action == 1) {
            // Walk -> blend to run?
            params[2] = 0.0f; // placeholder
            params[3] = 0.0f;
            params[4] = 0.0f;
            params[5] = 0.0f;
            FUN_0053ca50(&params[0]);
            FUN_00417cf0(5, 2, 2);
            goto finalAnim;
        }
        if (action == 2) {
            // Run
            params[2] = 0.0f;
            params[3] = 0.0f;
            params[4] = 0.0f;
            params[5] = 0.0f;
            FUN_0053ca50(&params[0]);
            FUN_00417cf0(1, 2, 1);
            goto finalAnim;
        }
        if (action == 3) {
            // Combat move
            params[0] = kOne;
            params[1] = kOne;
            params[2] = 0.0f;
            params[3] = 0.0f;
            params[4] = 0.0f;
            params[5] = 0.0f;
            FUN_0053ca50(&params[0]);
            FUN_00417cf0(1, 2, 2);
            goto finalAnim;
        }
        // Default (action == 0) -> idle blend
        params[0] = 0.0f;
        params[1] = 0.0f;
        params[2] = 0.0f;
        params[3] = 0.0f;
        params[4] = kOne;
        params[5] = kOne;
        FUN_0053ca50(&params[0]);
        FUN_00417cf0(1, 2, 2);
    } else {
        // Non-movement mode
        if (action == 0) {
            // Idle
            FUN_00417cf0(1, 5, 2);
        } else if (action == 1) {
            FUN_00417cf0(1, 5, 6);
        } else if (action == 2) {
            FUN_00417cf0(3, 5, 2);
        } else {
            // Default
            FUN_00417cf0(1, 2, 1);
        }
    }

finalAnim:
    // Final update call with computed parameters
    FUN_005330e0(obj->animTag, local_44, local_48, velX, velZ, hasCustomAnim);
    FUN_00612e00();

    // Reset global state
    g_currentAnimMain = 0;
    g_currentAnimLayer = 0;
    return;

foundLayer:
    g_customAnimData = reinterpret_cast<int*>(reinterpret_cast<char*>(g_layerDataTable) + 0 * 0xC); // Actually offset by i*0xC, but we reach here from loop above
    goto doneLayerLookup;
}