// Xbox PDB: EARS_Modules_HitMission_AddMinimapMarker
// FUNC_NAME: EffectManager::spawnEffect
// Address: 0x008fe5e0
// This function creates visual effects (e.g., hit decals, impact particles) for the Godfather 2 game.
// It handles two types: 1 = decal/impact, 2 = hit target effect.
// The function uses a global color (DAT_0112a680) and a zero constant (DAT_00d5780c).

#include <cstdint>

// Forward declarations of called functions (assumed from context)
uint32_t getCurrentEntityID(); // FUN_008fe1e0
void* getEntityByID(uint32_t id); // FUN_006b0ee0
void* refCountedGet(void* ptr); // FUN_006b4d50
int32_t createEffect(int32_t type, void* params, int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t* outArray, int32_t f, int32_t g, void* extra, int32_t h); // FUN_0094ca20
uint32_t getSomeGlobal(); // FUN_007914e0
void setEffectColor(void* colorBytes, uint32_t entityID); // FUN_008c76a0
void applyEffectColor(int32_t effectHandle, uint32_t color, uint32_t color2, uint32_t color3); // FUN_0094ac00
void debugPrint(const char* str, int32_t val); // FUN_008fdb40
void getColorFromGlobal(void* outColor); // FUN_008fe280
void playHitSound(); // FUN_008fdd80
void setEffectParameter(int32_t effectHandle, int32_t param, float val1, float val2); // FUN_00949d50
void releaseMemory(void* ptr); // FUN_009c8f10

// Global constants
extern uint32_t DAT_0112a680; // Color for effects (RGBA?)
extern uint32_t DAT_00d5780c; // Zero constant (identity quaternion or zero vector)

// Effect creation parameter structure (size 0x40 = 64 bytes)
struct EffectCreateParams {
    uint32_t field_00; // +0x00: usually DAT_00d5780c
    uint32_t field_04; // +0x04: zero
    uint32_t field_08; // +0x08: zero
    uint32_t field_0C; // +0x0C: zero
    uint32_t field_10; // +0x10: zero
    uint32_t field_14; // +0x14: DAT_00d5780c
    uint32_t field_18; // +0x18: zero
    void* functionPtr; // +0x1C: function pointer (pcStack_74)
    uint32_t field_20; // +0x20: zero
    uint32_t field_24; // +0x24: zero
    uint32_t field_28; // +0x28: DAT_00d5780c
    uint32_t field_2C; // +0x2C: zero
    float posX; // +0x30: position X
    float posY; // +0x34: position Y
    float posZ; // +0x38: position Z
    uint32_t field_3C; // +0x3C: DAT_00d5780c
};

// Class definition (based on offsets used)
class EffectManager {
public:
    // Offsets:
    // +0x00: vtable? (not used here)
    // +0xD8: effect handle (int32_t)
    // +0xDC: effect type (uint32_t)
    // +0xE0: some entity reference (uint32_t)
    // +0xC8 (200): some flag/pointer (int32_t)

    int32_t m_effectHandle; // +0xD8
    uint32_t m_effectType;   // +0xDC
    uint32_t m_entityRef;    // +0xE0
    int32_t m_flag;          // +0xC8

    void spawnEffect(uint32_t type);
};

void EffectManager::spawnEffect(uint32_t type) {
    // Extract color bytes from global
    uint8_t colorBytes[4];
    colorBytes[0] = (uint8_t)(DAT_0112a680 & 0xFF);
    colorBytes[1] = (uint8_t)((DAT_0112a680 >> 8) & 0xFF);
    colorBytes[2] = (uint8_t)((DAT_0112a680 >> 16) & 0xFF);
    colorBytes[3] = (uint8_t)((DAT_0112a680 >> 24) & 0xFF);

    int32_t outArray[3] = {0, 0, 0}; // For potential allocation tracking

    if (type == 1) {
        // Type 1: Decal/impact effect
        uint32_t entityID = getCurrentEntityID();
        void* entity = getEntityByID(entityID);
        if (entity == nullptr) goto cleanup;

        // Copy entity reference to this object
        m_entityRef = *(uint32_t*)((uint8_t*)entity + 0x48);
        void* refPtr = refCountedGet(&m_entityRef);
        if (refPtr != nullptr) {
            *(uint32_t*)refPtr = m_entityRef;
        }

        // Build effect creation parameters
        EffectCreateParams params;
        params.field_00 = DAT_00d5780c;
        params.field_04 = 0;
        params.field_08 = 0;
        params.field_0C = 0;
        params.field_10 = 0;
        params.field_14 = DAT_00d5780c;
        params.field_18 = 0;
        params.functionPtr = nullptr;
        params.field_20 = 0;
        params.field_24 = 0;
        params.field_28 = DAT_00d5780c;
        params.field_2C = 0;
        // Position from entity
        params.posX = *(float*)((uint8_t*)entity + 0x10);
        params.posY = *(float*)((uint8_t*)entity + 0x14);
        params.posZ = *(float*)((uint8_t*)entity + 0x18);
        params.field_3C = DAT_00d5780c;

        // Create effect (type 8)
        int32_t handle = createEffect(8, &params, 0, 5, 0, 0, 1, outArray, 0, 0, 0, 0);
        m_effectHandle = handle;

        // If effect created and flag allows, set color
        if (m_flag != 0 && m_flag != 0x48 && handle != 0) {
            uint32_t someGlobal = getSomeGlobal();
            setEffectColor(colorBytes, someGlobal);
            applyEffectColor(handle,
                             (uint32_t)colorBytes[0] | ((uint32_t)colorBytes[1] << 8) | ((uint32_t)colorBytes[2] << 16) | ((uint32_t)colorBytes[3] << 24),
                             (uint32_t)colorBytes[0] | ((uint32_t)colorBytes[1] << 8) | ((uint32_t)colorBytes[2] << 16) | ((uint32_t)colorBytes[3] << 24),
                             (uint32_t)colorBytes[0] | ((uint32_t)colorBytes[1] << 8) | ((uint32_t)colorBytes[2] << 16) | ((uint32_t)colorBytes[3] << 24));
        }
    } else if (type == 2) {
        // Type 2: Hit target effect
        outArray[0] = 0;
        outArray[1] = 0;
        outArray[2] = 0;

        uint32_t entityID = getCurrentEntityID();
        void* entity = getEntityByID(entityID);
        uint32_t entityRef;
        if (entity == nullptr) {
            entityRef = 0;
        } else {
            entityRef = *(uint32_t*)((uint8_t*)entity + 0x48);
        }

        m_entityRef = entityRef;
        void* refPtr = refCountedGet(&m_entityRef);
        if (refPtr != nullptr) {
            *(uint32_t*)refPtr = m_entityRef;
        }

        debugPrint("dv_hit_target", 9);

        // Build effect creation parameters (different layout)
        // This structure is 64 bytes as well, but fields are reused differently
        struct EffectCreateParams2 {
            uint32_t field_00; // +0x00: DAT_00d5780c
            uint32_t field_04; // +0x04: 0
            uint32_t field_08; // +0x08: 0
            uint32_t field_0C; // +0x0C: 0
            uint32_t field_10; // +0x10: 0
            uint32_t field_14; // +0x14: DAT_00d5780c
            uint32_t field_18; // +0x18: 0
            uint32_t field_1C; // +0x1C: 0
            uint32_t field_20; // +0x20: 0
            uint32_t field_24; // +0x24: 0
            uint32_t field_28; // +0x28: DAT_00d5780c
            uint32_t field_2C; // +0x2C: 0
            uint32_t colorLow; // +0x30: color bytes from global
            uint32_t colorHigh; // +0x34: more color? (local_94)
            uint32_t field_38; // +0x38: 0
            uint32_t field_3C; // +0x3C: DAT_00d5780c
        };

        EffectCreateParams2 params2;
        params2.field_00 = DAT_00d5780c;
        params2.field_04 = 0;
        params2.field_08 = 0;
        params2.field_0C = 0;
        params2.field_10 = 0;
        params2.field_14 = DAT_00d5780c;
        params2.field_18 = 0;
        params2.field_1C = 0;
        params2.field_20 = 0;
        params2.field_24 = 0;
        params2.field_28 = DAT_00d5780c;
        params2.field_2C = 0;

        // Get color from global (fills colorBytes again)
        getColorFromGlobal(colorBytes);
        params2.colorLow = (uint32_t)colorBytes[0] | ((uint32_t)colorBytes[1] << 8) | ((uint32_t)colorBytes[2] << 16) | ((uint32_t)colorBytes[3] << 24);
        // local_94 is from the stack frame; it might be part of the previous structure? 
        // In the original code, local_94 is at offset +0x04 from local_90, but in this branch it's used.
        // Since we don't have its value, we assume it's zero or from previous call.
        // For reconstruction, we set it to 0 (likely safe).
        params2.colorHigh = 0; // local_94
        params2.field_38 = 0;
        params2.field_3C = DAT_00d5780c;

        // Create effect (type 9)
        int32_t handle = createEffect(9, &params2, 0, 5, 3, 1, 2, outArray, 0, 0, &params2, 0);
        m_effectHandle = handle;

        if (handle != 0) {
            playHitSound();
            setEffectParameter(handle, 2, DAT_00d5eee4, DAT_00e446c0);
        }

        // Cleanup function pointer if present (from the first branch's stack? Actually it's from the same stack frame)
        // In the original code, there is a check for local_80 and pcStack_74, but those are from the first branch's stack.
        // Since we are in the second branch, those are uninitialized. We'll skip that check.
    }

cleanup:
    if (outArray[0] != 0) {
        releaseMemory((void*)outArray[0]);
    }

    // Store effect type if handle is non-zero
    m_effectType = (m_effectHandle != 0) ? type : 0;
}