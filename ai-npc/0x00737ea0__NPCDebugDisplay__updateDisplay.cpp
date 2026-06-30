// FUNC_NAME: NPCDebugDisplay::updateDisplay
#include <cstdint>

// Forward declarations based on callee analysis
class NPC; // param_2 (entity)
class AudioInstance;
enum PlayerIndex;

// External functions (conceptual)
float getPlayerPositionDiff(PlayerIndex a, PlayerIndex b); // from FUN_00471610
void handleProximityTrigger(NPC* entity); // FUN_007918e0
bool isMultiplayerGame(); // FUN_007ff880
void debugListAddEntry(DebugList* list, void* owner, int flags); // FUN_00408bf0
void debugListRemoveEntry(DebugList* list); // FUN_004daf90
float getGameTime(); // FUN_00806440
void setSoundParameter(AudioInstance* instance, float param, int index); // FUN_008d3840
bool isGamePaused(); // FUN_00800c10
AudioInstance* acquireSoundInstance(PlayerIndex player, int group); // FUN_006fbc40
void playSoundByHash(uint32_t hash, int priority, AudioInstance* instance, bool loop); // FUN_007f96a0
void releaseSoundInstance(); // FUN_006fbc70
void updateEntityAnimation(NPC* entity, uint8_t animState); // FUN_00730060
void updateEntityAI(NPC* entity); // FUN_00734a40
bool isPausedGlobal(); // FUN_007f7b90
void resetTimer(Timer* timer); // FUN_007fff40
void stopAllSounds(); // FUN_007f6460

// Constants / signatures
static const uint32_t SOUND_HASH_ACTIVATE = 0x3841ce34;
static const uint32_t SOUND_HASH_DEACTIVATE = 0x5ed9130f;
static const uint32_t SOUND_HASH_SPECIAL = 0x3a85b789;

// Debug list structures (from memory)
struct DebugListEntry {
    void* vtable; // PTR_FUN_00d5dbbc
    int unk1;
    // ...
};

// -------------------------------------------------------------------
// NPCDebugDisplay::updateDisplay
// param_1: this (NPCDebugDisplay*)
// param_2: entity (NPC*)
// param_3: showExtraDebug (bool)
// @ 0x00737ea0
// -------------------------------------------------------------------
void NPCDebugDisplay::updateDisplay(NPC* entity, bool showExtra) {
    // Local debug list entry stack variables
    DebugListEntry listEntry1;
    DebugListEntry listEntry2; // only used when showExtra is true

    // Check if we have a valid target and it is not null/0x48
    int* target = *(int**)(this + 0x2178); // +0x2178: currentTarget pointer
    if (target && target != (int*)0x48 && (*(uint32_t*)(target + 0x14) & 0xff00) != 0) {
        float radius = *(float*)(this + 0x1F40); // +0x1F40: proximity radius
        PlayerIndex player1 = getPlayerPositionDiff(0, 0); // FUN_00471610 (index trick?)
        PlayerIndex player2 = getPlayerPositionDiff(0, 0);
        float dx = *(float*)(player2 + 0x30) - *(float*)(player1 + 0x30);
        float dy = *(float*)(player2 + 0x34) - *(float*)(player1 + 0x34);
        float dz = *(float*)(player2 + 0x38) - *(float*)(player1 + 0x38);
        float distSq = dx*dx + dy*dy + dz*dz;
        if (distSq < radius * radius) {
            handleProximityTrigger(entity); // FUN_007918e0
        }
    }

    // Determine flag based on whether we are in multiplayer
    bool isMulti = isMultiplayerGame(); // FUN_007ff880
    uint32_t flagVal;
    if (showExtra) {
        flagVal = (isMulti ? 0x7c32da16 : 0x55de7cd);
    } else {
        flagVal = (isMulti ? 0x46974d50 : 0xa18cf3cd);
    }

    // Prepare first debug list entry
    listEntry1.vtable = PTR_FUN_00d5dbbc; // from global
    listEntry1.unk1 = 0; // initialised to 0
    // ... other fields
    // Actually reconstruct the struct initialization from decompiled code:
    // local_30, local_34, local_38 = 0; local_40 = 0; local_3c = 0; local_2c = 0; local_28 = DAT_01205228
    // We'll represent as a struct.
    struct DebugListData {
        uint32_t unk0; // local_64
        DebugListEntry* listPtr; // local_60 (points to listEntry1)
        uint8_t unk1; // local_5c
        uint32_t unk2; // local_58
        DebugListEntry* listPtr2; // local_54 (points to listEntry2 if used)
        uint8_t unk3; // local_50
        DebugListEntry entry; // local_48
        int val; // local_44 (holds the flagVal)
        int val2; // local_40
        uint32_t val3; // local_3c
        // ... fields from decompiled local variables aligned accordingly
    } data;
    // Actually, we need to mimic the original layout. Simplified:
    DebugListData listData;
    listData.unk0 = DAT_0112ad8c; // global debug list?
    listData.listPtr = &listEntry1;
    listData.unk1 = 0;
    listData.unk2 = DAT_0112ad8c;
    listData.listPtr2 = &listEntry1; // initially same
    listData.unk3 = 0;
    listData.entry.vtable = PTR_FUN_00d5dbbc;
    listData.val = flagVal; // local_44
    listData.val2 = 0;
    listData.val3 = 0;
    // etc.

    // Insert first debug list entry
    void* owner = (this != 0) ? (this + 0x3C) : 0; // +0x3C: some sub-object
    debugListAddEntry(&listData.unk0, owner, 0); // FUN_00408bf0

    // If showExtra, insert a second entry
    if (showExtra) {
        listEntry2.vtable = PTR_FUN_00d5dbbc;
        listEntry2.unk1 = 0;
        // Reinitialize the struct for second entry
        DebugListData data2;
        data2.unk0 = DAT_0112ad8c;
        data2.listPtr = &listEntry2;
        data2.unk1 = 0;
        data2.unk2 = DAT_0112ad8c;
        data2.listPtr2 = &listEntry2;
        data2.unk3 = 0;
        data2.entry.vtable = PTR_FUN_00d5dbbc;
        data2.val = 0x5ed9130f; // local_20
        data2.val2 = 0; // local_1c
        data2.val3 = 0; // local_18
        // Insert
        debugListAddEntry(&data2.unk0, owner, 0); // FUN_00408bf0
        // Cleanup if needed
        if (data2.val2 != 0) {
            debugListRemoveEntry(&data2.val2); // FUN_004daf90
        }
    }

    // Check for special debug condition based on current action
    int* currentAction = *(int**)(this + 0x2584); // +0x2584: current action pointer
    if (currentAction && currentAction != (int*)0x48 && showExtra) {
        int actionType = *(int*)(currentAction + 0xC); // +0xC: action type ID
        if (actionType > 0x13 && (actionType < 0x16 || actionType == 0x24)) {
            // Insert another debug list entry
            DebugListData data3;
            data3.unk0 = DAT_0112ad8c;
            data3.listPtr = &listEntry1; // reuse listEntry1
            data3.unk1 = 0;
            data3.unk2 = DAT_0112ad8c;
            data3.listPtr2 = &listEntry1;
            data3.unk3 = 0;
            data3.entry.vtable = PTR_FUN_00d5dbbc;
            data3.val = SOUND_HASH_SPECIAL; // 0x3a85b789
            // ... other fields zero
            debugListAddEntry(&data3.unk0, owner, 0);
        }
    }

    // Audio parameter update if global flag set
    if (DAT_011299a4 != 0) {
        AudioInstance* audioInst = (AudioInstance*)getGameTime(); // ? FUN_00806440 returns something
        float paramVal = 1.0f; // uVar10
        float time = getGameTime(); // uVar5 from FUN_00806440? Actually decompiled: uVar5 = FUN_00806440(1) returns float? Wait: calls with arg 1. Let's assume it returns a float time.
        setSoundParameter(*(AudioInstance**)(this + 0x1ED4), time, paramVal); // FUN_008d3840
    }

    // Handle entity state machine / audio triggers
    int* entityAI = *(int**)(entity + 0x74C); // +0x74C: AI component pointer
    if (entityAI == 0 || entityAI == (int*)0x48) goto skipAIUpdate;
    uint32_t flags = *(uint32_t*)(entity + 0x8E0); // +0x8E0: flags
    if ((flags >> 10 & 1) == 0 || isGamePaused()) goto skipAIUpdate;

    uint8_t aiState = *(uint8_t*)(entityAI + 0x160); // +0x160: current AI state
    if (aiState == 0x01) {
        // Activate sound/effect
        if ((*(uint32_t*)(this + 0x1F5C) >> 1 & 1) == 0) {
            *(uint32_t*)(this + 0x1F5C) |= 2;
            AudioInstance* inst = acquireSoundInstance(0, 0); // FUN_006fbc40
            playSoundByHash(SOUND_HASH_ACTIVATE, 0, inst, false); // FUN_007f96a0
            releaseSoundInstance(); // FUN_006fbc70
        }
    } else if ((*(uint32_t*)(entityAI + 0x188) >> 2 & 1) != 0) {
        // Deactivate sound/effect
        if ((*(uint8_t*)(this + 0x1F5C) & 1) == 0) {
            *(uint32_t*)(this + 0x1F5C) |= 1;
            AudioInstance* inst = acquireSoundInstance(0, 0);
            playSoundByHash(0, 0, inst, false); // sound hash 0
            releaseSoundInstance();
        }
    }

    // Update animation and state for the entity
    updateEntityAnimation(entity, aiState); // FUN_00730060
    updateEntityAI(entity); // FUN_00734a40

skipAIUpdate:
    // Pause/timer handling
    if (*(int32_t*)(this + 0x1F58) >= 0 && !isPausedGlobal()) { // FUN_007f7b90
        resetTimer( (Timer*)(this + 0x1FF8) ); // FUN_007fff40
        *(uint32_t*)(this + 0x1F58) |= 0x80000000;
        if ((*(uint32_t*)(entity + 0x24A4) >> 8 & 1) == 0) {
            AudioInstance* inst = acquireSoundInstance(0, 0);
            playSoundByHash(0, 0, inst, false);
            releaseSoundInstance();
        }
        stopAllSounds(); // FUN_007f6460
    }

    // Cleanup first debug list entry (if it was inserted)
    if (listData.val2 != 0) { // local_40 might be non-zero if insertion happened via linked list? Actually check local_40
        debugListRemoveEntry(&listData.val2);
    }

    // Note: The decompiler shows local_40 being checked at the end. We stored it as listData.val2.
    // This cleanup is based on the linked list pattern: the variable that holds the pointer to the list node.
    return;
}