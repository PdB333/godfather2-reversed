// FUNC_NAME: Sentient::handleHitReaction
// Function address: 0x0078bb50
// Role: Handles reaction to being hit/damaged, including sound/event playback.

#include <cstdint>

// Forward declarations for engine types
class AudioManager;
class EventData;
class CameraInfo;
class SomeObject;

// Known function prototypes (inferred from decompilation)
AudioManager* getAudioManager(); // FUN_0043b870
void setHitEffectChannel(int channel); // FUN_0078b270
void setHitEffectVolume(float volume, int someFlag1, int someFlag2); // FUN_0078b4b0
bool canPlayDialogue(); // FUN_00732380
uint32_t startAudioEvent(int unk0, int unk1); // FUN_006fbc40
void playDialogueEvent(uint32_t hash, int priority, uint32_t audioHandle, int extra); // FUN_007f96a0
void stopAudioEvent(); // FUN_006fbc70
CameraInfo* getCameraInfo(); // FUN_00471610
void pushEvent(EventData* event, int unk); // FUN_00408a00
bool isDead(); // FUN_007f7b90
float computeCombatFactor(uint32_t param1, uint32_t param2); // FUN_0078ad10
SomeObject* getPlayerObject(); // FUN_007fd740
SomeObject* getObjectByHash(SomeObject* obj, uint32_t hash); // FUN_006c9470

// Global data references (from .data section)
extern float g_globalDamageThreshold; // DAT_00e44598
extern float g_globalCameraFOV; // _DAT_00d5c458
extern uint32_t g_unkGlobalHash; // DAT_0112afd8

void __thiscall Sentient::handleHitReaction(void* thisPtr, void* eventDataPtr) {
    // Cast pointers to structures based on offsets
    uint8_t* thisPtrBytes = static_cast<uint8_t*>(thisPtr);
    uint8_t* eventBytes = static_cast<uint8_t*>(eventDataPtr);

    float local_30 = 0.0f;
    uint32_t uVar8 = 0;
    AudioManager* audioMgr = nullptr;
    int* piVar6 = nullptr;
    int* piVar7 = nullptr;

    // Check source object pointer in event (+0x0c)
    if (*(int*)(eventBytes + 0x0c) != 0) {
        piVar6 = *(int**)(eventBytes + 0x0c) - 0x48; // Adjust pointer by -0x48
        if (piVar6 != nullptr) {
            // Call virtual function at vtable+0x10 to get some value (e.g., hit chance/force)
            // Hash 0x383225a1 could be a field identifier
            char result = (*(char(__thiscall**)(int*, float*))(*(int*)piVar6 + 0x10))(piVar6, &local_30);
            if (result != 0) {
                uVar8 = static_cast<uint32_t>(local_30);
            }
            audioMgr = getAudioManager();
        }
    }

    // Check damage threshold and bit flag (maybe "critical hit"?)
    if (g_globalDamageThreshold < *(float*)(eventBytes + 0x2c) && (*(uint32_t*)(eventBytes + 0x44) & 0x20) != 0) {
        int animData = *(int*)(thisPtrBytes + 0x0c);
        if (animData != 0 && animData != 0x3c) {
            local_30 = *(float*)(animData + 0xd8);
            setHitEffectChannel(4);
            setHitEffectVolume(local_30, 1, 1);
            if (canPlayDialogue()) {
                if (uVar8 != 0) {
                    // Play audio event via audio manager vtable (hash 0x2e0c930f)
                    (*(void(__thiscall**)(AudioManager*, uint32_t, int, int, int))(*(int*)audioMgr + 0x28))
                        (audioMgr, 0x2e0c930f, 0, 0xffffffff, 0);
                }
                uint32_t audioHandle = startAudioEvent(0, 0);
                playDialogueEvent(0xf6fd2e8d, 0x74, audioHandle, 0);
                stopAudioEvent();
            }
        }
        uint32_t audioHandle2 = startAudioEvent(0, 0);
        playDialogueEvent(0, 0, audioHandle2, 0);
        stopAudioEvent();
    }

    // If we have a valid hit source (uVar8 != 0)
    if (uVar8 == 0) goto checkFinalBit;

    // Check camera facing and a flag in stateData
    float fVar9 = (*(float(__thiscall**)(void*))(**(int**)(thisPtrBytes + 0x50) + 0x30))();
    if (fVar9 <= g_globalCameraFOV && (*(uint8_t*)(*(int*)(thisPtrBytes + 0x4c) + 0x1b96) & 1) == 0) {
        CameraInfo* cam = getCameraInfo();
        // Build an event structure on the stack
        struct TempEvent {
            uint32_t field_0;
            uint8_t field_4;
            uint32_t field_8;
            uint64_t field_10;
            uint32_t field_18;
            uint32_t field_1c;
            uint32_t field_20;
            uint32_t field_24;
            uint8_t field_28;
        } event;
        // Fill event from camera and state data
        event.field_0 = g_unkGlobalHash;
        event.field_4 = 0;
        event.field_8 = 1;
        event.field_10 = *(uint64_t*)(cam + 0x30);
        event.field_18 = *(uint32_t*)(cam + 0x38);
        event.field_1c = *(uint32_t*)(thisPtrBytes + 0x4c);
        event.field_20 = 1;
        // event.field_24 and field_28 set by the function call
        // Call pushEvent with a pointer to the event structure
        pushEvent(&event, 0);
        // Set a flag on stateData at +0x1b94 (e.g., "hasSpokenRecently")
        uint32_t* flagPtr = (uint32_t*)(*(int*)(thisPtrBytes + 0x4c) + 0x1b94);
        *flagPtr |= 0x10000;
    }

    // Handle two hit types based on eventData+0x30
    if (*(int*)(eventBytes + 0x30) == 1 && (*(uint32_t*)(eventBytes + 0x44) & 0x08) == 0) {
        // Hit type 1: e.g., melee/gun
        int animData2 = *(int*)(thisPtrBytes + 0x0c);
        local_30 = 0.0f;
        if (animData2 != 0 && animData2 != 0x3c) {
            local_30 = *(float*)(animData2 + 8) * *(float*)(eventBytes + 0x2c);
        }
        setHitEffectChannel(2);
        setHitEffectVolume(local_30, 1, 1);
        if (isDead()) goto checkFinalBit;
        if (canPlayDialogue()) {
            uint32_t audioHandle3 = startAudioEvent(0, 0);
            playDialogueEvent(0xc1846493, 100, audioHandle3, 0);
            stopAudioEvent();
            // Play audio event with hash 0x57025a91
            (*(void(__thiscall**)(AudioManager*, uint32_t, int, int, int))(*(int*)audioMgr + 0x28))
                (audioMgr, 0x57025a91, 0, 0xffffffff, 0);
        }
    } else if (*(int*)(eventBytes + 0x30) == 2) {
        // Hit type 2: e.g., explosive/fire
        int pointerCheck = *(int*)(eventBytes + 0x04);
        if (pointerCheck == 0 || *(int*)(eventBytes + 0x04) == 0x48) goto checkFinalBit;
        if (pointerCheck == 0) {
            piVar6 = nullptr;
        } else {
            piVar6 = (int*)(*(int*)(eventBytes + 0x04) - 0x48);
        }
        local_30 = 0.0f;
        char result2 = (*(char(__thiscall**)(int*, float*))(*(int*)piVar6 + 0x10))(piVar6, &local_30);
        float fVar1 = local_30;
        if (result2 == 0 || local_30 == 0.0f) goto checkFinalBit;
        float fVar9b = (float)computeCombatFactor(*(uint32_t*)(eventBytes + 0x3c), *(uint32_t*)(thisPtrBytes + 0x4c));
        local_30 = (float)(fVar9b * (float)*(float*)((int)fVar1 + 0x1d8));
        setHitEffectChannel(7);
        setHitEffectVolume(local_30, 1, 1);
        if (canPlayDialogue()) {
            uint32_t audioHandle4 = startAudioEvent(0, 0);
            playDialogueEvent(0xe75f82ab, 100, audioHandle4, 0);
            stopAudioEvent();
            // Play audio event with hash 0x873c4a2d
            (*(void(__thiscall**)(AudioManager*, uint32_t, int, int, int))(*(int*)audioMgr + 0x28))
                (audioMgr, 0x873c4a2d, 0, 0xffffffff, 0);
        }
    }

checkFinalBit:
    // Check additional state flag and player's gaze
    if ((*(uint32_t*)(*(int*)(thisPtrBytes + 0x4c) + 0x8e8) & 0x400000) != 0) {
        float fVar9c = (*(float(__thiscall**)(void*))(**(int**)(thisPtrBytes + 0x4c) + 0xc0))();
        if (0.0f < fVar9c) {
            SomeObject* playerObj = getPlayerObject();
            if (playerObj != nullptr) {
                float playerGaze = (*(float(__thiscall**)(SomeObject*))(*(int*)playerObj + 0xc0))();
                if (0.0f < playerGaze) {
                    int objHit = getObjectByHash(playerObj, 0x383225a1);
                    if (objHit != 0) {
                        int animData3 = *(int*)(thisPtrBytes + 0x0c);
                        local_30 = 0.0f;
                        if (animData3 != 0 && animData3 != 0x3c) {
                            local_30 = *(float*)(animData3 + 8) * *(float*)(eventBytes + 0x2c);
                        }
                        setHitEffectVolume(local_30, 1, 1);
                    }
                }
            }
        }
    }
    return;
}