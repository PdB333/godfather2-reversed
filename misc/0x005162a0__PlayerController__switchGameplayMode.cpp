// FUNC_NAME: PlayerController::switchGameplayMode
// Function address: 0x005162a0
// Role: Switches the game into a new gameplay mode (e.g., free roam, mission). Adjusts camera, control flags, entity states, and resets various systems.

#include <cstdint>

// Global variables (inferred from decompilation)
extern uint32_t g_currentModeId;            // DAT_01218e50
extern uint32_t g_previousModeId;           // DAT_011f38f0
extern uint32_t g_modeTransitionFlags;      // DAT_011f38f4 (bitfield)
extern uint32_t g_cameraMinZoom;            // DAT_012058d0 (clamped)
extern uint32_t g_cameraMaxZoom;            // DAT_00f15988 (clamped)
extern uint32_t g_entitySlotCount;          // DAT_012058a4 (max index)
extern uint32_t g_entityArrayBase;          // DAT_012054dc (base pointer for some entity stuff)
extern uint8_t  g_entitySlotTable[0x1000][0x38]; // DAT_011a0f28, stride 0x38
extern uint32_t g_statePairTable[0x14][2];  // DAT_01218e50 and DAT_01218e54 (array of pairs)
extern uint32_t g_colorParam1;              // DAT_00e2eff4
extern uint32_t g_colorParam2;              // DAT_00e2b1a4
extern uint32_t g_someFlag1;                // DAT_011f3a30
extern uint32_t g_someFlag2;                // DAT_011f39f4
extern uint32_t g_someFlag3;                // DAT_011f3a10
extern uint32_t g_someFlag4;                // DAT_011f3a3c
extern uint32_t g_someFlag5;                // DAT_011f3a38
extern uint32_t g_someFlag6;                // DAT_011f3a14
extern uint32_t g_someFlag7;                // DAT_011f3a44
extern uint32_t g_postProcessBuffer[16];    // allocated dynamically
extern uint32_t g_unknown0;                 // DAT_01219950
extern uint32_t g_unknown1;                 // DAT_01219954
extern uint32_t g_unknown2;                 // DAT_012199e4
extern uint32_t g_unknown3;                 // DAT_012199e8

// Forward declarations of subroutines (renamed based on likely purpose)
void setGameModeFlag(int32_t flag);                        // FUN_00609890
void setModeFade(uint32_t modeId);                         // FUN_0060df60
void setCameraMode(int32_t a, int32_t b, int32_t c);       // FUN_00417cf0
void freeMemory(void* ptr, uint32_t flags);                // FUN_00606e60
void invalidateCache();                                     // FUN_006189c0
void switchPlayerCamera(uint32_t a, uint32_t b, uint32_t c);// FUN_00609340
void setupFade(int32_t a, int32_t b, int32_t c, float d, float e); // FUN_0060db60
void resetCamera1();                                        // FUN_00530c90
void resetCamera2();                                        // FUN_00530a60
void resetCamera3();                                        // FUN_00530df0
void resetCamera4();                                        // FUN_00530ff0
void* allocateMemory(int32_t type, int32_t size, int32_t a, int32_t b, int32_t c); // FUN_0060cd00
void initAllocatedMemory();                                 // FUN_0060cde0
void initializePostProcess();                               // FUN_00612e00

// Helper macro/function to clamp a value between min and max based on global comparisons
inline void clampCameraLimits(uint32_t minLimit, uint32_t maxLimit) {
    if (g_cameraMinZoom < minLimit) g_cameraMinZoom = minLimit;
    if (g_cameraMaxZoom > maxLimit) g_cameraMaxZoom = maxLimit;
}

// The main function
void __fastcall PlayerController::switchGameplayMode(uint32_t newModeId) {
    // newModeId passed in EAX
    if (newModeId == g_currentModeId) {
        // Already in this mode - handle immediate transition
        if (g_previousModeId == newModeId && g_modeTransitionFlags == 0) {
            setGameModeFlag(1);
            return;
        }
        setModeFade(g_previousModeId);
        return;
    }

    // --- First camera/control flags configuration (phase 1) ---
    clampCameraLimits(0x16, 0x16);
    g_someFlag1 = 1;

    clampCameraLimits(7, 7);
    g_someFlag2 = 0;

    clampCameraLimits(0xe, 0xe);
    g_someFlag3 = 0;

    clampCameraLimits(0x19, 0x19);
    g_someFlag4 = 5;

    clampCameraLimits(0x18, 0x18);
    g_someFlag5 = 0;

    clampCameraLimits(0xf, 0xf);
    g_someFlag6 = 0;

    clampCameraLimits(0x1b, 0x1b);
    g_someFlag7 = 0;

    setCameraMode(1, 2, 1);

    // --- Destroy/release entity associated with newModeId ---
    if ((newModeId != 0xffffffff) && (newModeId < 0x1000)) {
        uint32_t slotIndex = newModeId * 0x38;
        uint8_t* slotBase = (uint8_t*)&g_entitySlotTable[0][0] + slotIndex;
        if ((slotBase != nullptr) && ((*slotBase) < 4)) {
            void* ptr = *(void**)(slotBase + 0x1c);
            if (ptr != nullptr) {
                freeMemory(ptr, 0x100000);
            }
            uint32_t flags = *(uint32_t*)(slotBase + 0xc);
            flags = (flags & 0xfc9c8fff) | 0x100000;
            *(uint32_t*)(slotBase + 0xc) = flags;
            invalidateCache();
        }
    }

    // --- Destroy/release entity associated with current mode's global ID ---
    uint32_t currentEntityIndex = g_entitySlotCount;
    if (g_entityArrayBase != 0) {
        currentEntityIndex = *(uint32_t*)(g_entityArrayBase + 0x16c);
    }
    if ((currentEntityIndex != 0xffffffff) && (currentEntityIndex < 0x1000)) {
        uint32_t slotIndex = currentEntityIndex * 0x38;
        uint8_t* slotBase = (uint8_t*)&g_entitySlotTable[0][0] + slotIndex;
        if ((slotBase != nullptr) && ((*slotBase) < 4)) {
            void* ptr = *(void**)(slotBase + 0x1c);
            if (ptr != nullptr) {
                freeMemory(ptr, 0x100000);
            }
            uint32_t flags = *(uint32_t*)(slotBase + 0xc);
            flags = (flags & 0xfc9c8fff) | 0x100000;
            *(uint32_t*)(slotBase + 0xc) = flags;
            invalidateCache();
        }
    }

    setGameModeFlag(1);

    // --- Clear old mode from state pair table ---
    for (uint32_t i = 0; i < 0x14; i++) {
        if (g_statePairTable[i][0] == newModeId) {
            g_statePairTable[i][1] &= 0xfffffffc;
            break;
        }
    }

    // --- Transfer to new mode ---
    uint32_t oldFlags = g_modeTransitionFlags;
    g_modeTransitionFlags = 0;
    uint32_t oldModeId = g_previousModeId;
    switchPlayerCamera(0, oldModeId, oldFlags);
    g_previousModeId = newModeId;

    // --- Setup fade/camera and reset all cameras ---
    setupFade(0, 0, 0, 1.0f, 1.0f);
    resetCamera1();
    resetCamera2();
    resetCamera3();
    resetCamera4();

    // --- Allocate and initialize post-processing effect buffer ---
    uint32_t* ppBuffer = (uint32_t*)allocateMemory(0xd, 4, 0, 1, 0);
    if (ppBuffer != nullptr) {
        uint32_t val1 = g_colorParam1;
        uint32_t val2 = g_colorParam2;
        ppBuffer[0]  = val1;
        ppBuffer[1]  = val2;
        ppBuffer[2]  = 0;
        ppBuffer[3]  = 0;
        ppBuffer[4]  = val2;
        ppBuffer[5]  = val2;
        ppBuffer[6]  = val2;
        ppBuffer[7]  = 0;
        ppBuffer[8]  = val2;
        ppBuffer[9]  = val1;
        ppBuffer[10] = val2;
        ppBuffer[11] = val2;
        ppBuffer[12] = val1;
        ppBuffer[13] = val1;
        ppBuffer[14] = 0;
        ppBuffer[15] = val2;
        initAllocatedMemory();
    }
    initializePostProcess();

    g_unknown0 = 0;
    g_unknown1 = 0;
    g_unknown2 = 0;
    g_unknown3 = 0;

    setGameModeFlag(1);

    // --- Second mode ID transition (mirrored) ---
    currentEntityIndex = g_entitySlotCount;
    if (g_entityArrayBase != 0) {
        currentEntityIndex = *(uint32_t*)(g_entityArrayBase + 0x16c);
    }

    // Clear same table for this index
    for (uint32_t i = 0; i < 0x14; i++) {
        if (g_statePairTable[i][0] == currentEntityIndex) {
            g_statePairTable[i][1] &= 0xfffffffc;
            break;
        }
    }

    oldFlags = g_modeTransitionFlags;
    oldModeId = g_previousModeId;
    g_modeTransitionFlags = 0;
    g_previousModeId = currentEntityIndex;
    switchPlayerCamera(0, oldModeId, oldFlags);
    setupFade(0, 0, 0, 1.0f, 1.0f);

    // --- Second camera/control flags configuration (phase 2) ---
    clampCameraLimits(0x16, 0x16);
    g_someFlag1 = 1;

    clampCameraLimits(7, 7);
    g_someFlag2 = 1;

    clampCameraLimits(0xe, 0xe);
    g_someFlag3 = 1;

    clampCameraLimits(0x19, 0x19);
    g_someFlag4 = 7;

    clampCameraLimits(0x18, 0x18);
    g_someFlag5 = 0;

    clampCameraLimits(0xf, 0xf);
    g_someFlag6 = 0;

    clampCameraLimits(0x1b, 0x1b);
    g_someFlag7 = 0;

    setCameraMode(1, 5, 6);
}