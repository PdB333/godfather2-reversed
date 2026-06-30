// FUNC_NAME: CombatPerception::updatePerception
// Address: 0x0051bc80
// Role: Processes perception targets for an AI entity, computes closest/farthest distances,
//       updates perception state, and notifies relevant systems.

#include <cstdint>

// Forward declarations of called functions (from same module)
extern int getTeamArrayIndex();
extern uint64_t getCurrentContextId(); // returns some 64-bit ID
extern bool getDistance(int entityId, float* outDistance); // returns true if valid
extern void updateClosestDistance(void* thisPtr, float distance);
extern void notifyPerception(void* thisPtr, int entityId, float distance);
extern void updateStateFlags(void* thisPtr);
extern void* validateTarget(void* ptr); // returns some validation object or null
extern float g_farDistance; // DAT_00e2e50c
extern float g_sentinelDistance; // DAT_00e44758
extern uint8_t g_globalFlag; // DAT_0120551d

// Context structure obtained from TLS (fs:[0x2c])
struct GameContext {
    char pad_0x00[0x10];
    uint16_t playerMask; // +0x10
    char pad_0x12[0x22];
    int32_t isMultiplayer; // +0x34 (non-zero if multiplayer)
};

// Array element for perception targets (size 0x10)
struct PerceptionEntry {
    int32_t entityId;     // +0x00
    int32_t someId;       // +0x04 (used for throwable validation)
    uint32_t flags;       // +0x08 (bitmask)
    int32_t unknown;      // +0x0C (padding?)
};

// Main function
void CombatPerception::updatePerception(CombatPerception* thisPtr) {
    uint32_t flags = *(uint32_t*)((uint8_t*)thisPtr + 0x0C);
    // Skip if certain mode flags are active
    if (flags & 0x20300000) {
        return;
    }

    float nearestDistance = 0.0f;            // farthest distance initialized to 0
    bool hasAnyTarget = false;
    float farthestDistance = g_farDistance;  // initial farthest

    int teamIndex = getTeamArrayIndex();
    GameContext* gameCtx = *(GameContext**)__readfsdword(0x2C);
    uint16_t playerMask = gameCtx->playerMask;                           // +0x10
    int32_t isMultiplayer = gameCtx->isMultiplayer;
    int arrayOffset = (isMultiplayer != 0) ? 0x98 : 0;                  // conditional offset

    int entryCount = *(int32_t*)((uint8_t*)gameCtx + arrayOffset + 4 + teamIndex);
    if (entryCount <= 0) {
        goto end_loop;
    }

    int entryIndex = 0;
    int byteOffset = 0;
    float distances[8]; // stored distances for later notification

    do {
        uint32_t dataFlags = *(uint32_t*)(*(uint32_t*)((uint8_t*)thisPtr + 0x10) + 0x14);
        PerceptionEntry* entry = (PerceptionEntry*)((uint8_t*)gameCtx + arrayOffset + 0x0C + teamIndex + byteOffset);
        distances[entryIndex] = g_sentinelDistance;

        if ((dataFlags & 0x800) == 0) {
            // Normal entity processing
            uint8_t bitmask = *(uint8_t*)(*(uint32_t*)((uint8_t*)thisPtr + 0x10) + 0x1D);
            bool maskCheck = (bitmask == 0) || (entry->flags == 0) || ((entry->flags & bitmask) != 0);
            if (maskCheck && ((*(uint32_t*)((uint8_t*)thisPtr + 0x84) & playerMask) == playerMask)) {
                uint64_t contextId = getCurrentContextId();
                int32_t lowPart = entry->entityId;
                // Condition: entityId matches contextId (with special sign check) or contextId has specific bits
                if (( (uint32_t)(lowPart == (int32_t)contextId) == (((uint32_t)(contextId >> 32) & 0xFF) >> 3 & 1) ) ||
                    ((contextId & 0xF700000000) != 0 && (lowPart != (int32_t)contextId))) {
                    float distance;
                    if (getDistance(entry->entityId, &distance)) {
                        distances[entryIndex] = distance;
                        hasAnyTarget = true;
                    }
                    // Update nearest (closest to 0) and farthest
                    if (nearestDistance <= distance) { // note: actual nearest logic likely reversed
                        nearestDistance = distance;
                    }
                    if (distance <= farthestDistance) {
                        farthestDistance = distance;
                    }
                }
            }
        } else {
            // Special processing for projectiles/throwables
            uint32_t* throwableList = *(uint32_t**)((uint8_t*)thisPtr + 0x20);
            if (throwableList) {
                (*throwableList)++; // ref count increment?
            }
            void* validationResult = validateTarget(throwableList);
            if (validationResult == nullptr) {
                goto LAB_0051bd6b;
            }
            uint32_t count = *(uint32_t*)((uint8_t*)validationResult + 0x18);
            if (count != 0) {
                for (uint32_t i = 0; i < count; i++) {
                    int32_t id = *(int32_t*)((uint8_t*)validationResult + 8 + i * 4);
                    if (id == entry->someId) {
                        if (i != 0xFFFFFFFF) {
                            goto LAB_0051bd6b;
                        }
                        break;
                    }
                }
            }
        }
        // Continue loop (fall through label)
        LAB_0051bd6b:
        byteOffset += 0x10;
        entryIndex++;
        arrayOffset = (isMultiplayer != 0) ? 0x98 : 0;
    } while (entryIndex < *(int32_t*)((uint8_t*)gameCtx + arrayOffset + 4 + teamIndex));

end_loop:
    // Update closest distance if global flag allows or flag is set
    if (g_globalFlag == 0 || (*(uint32_t*)((uint8_t*)thisPtr + 0x0C) & 0x400000) != 0) {
        updateClosestDistance(thisPtr, nearestDistance);
    }

    if (hasAnyTarget) {
        // Notify about perceived entities (second loop)
        for (int i = 0; i < entryCount; i++) {
            float dist = distances[i];
            if (dist != g_sentinelDistance) {
                uint64_t ctxId = getCurrentContextId();
                int32_t hiPart = *(int32_t*)((uint64_t)ctxId >> 32);
                uint8_t bitmask = *(uint8_t*)(*(uint32_t*)((uint8_t*)thisPtr + 0x10) + 0x1D);
                if ((hiPart == (int32_t)ctxId) == ((bitmask >> 3) & 1) ||
                    ((bitmask & 0xF7) != 0 && (hiPart != (int32_t)ctxId))) {
                    notifyPerception(thisPtr, hiPart, dist);
                }
            }
        }

        uint32_t oldFlags = *(uint32_t*)((uint8_t*)thisPtr + 0x0C);
        *(uint16_t*)((uint8_t*)thisPtr + 0x82) = 0; // clear short field

        if ((oldFlags & 0x40000) != 0 && (oldFlags & 1) != 0) {
            *(uint32_t*)((uint8_t*)thisPtr + 0x0C) = oldFlags & 0xFFFBFFFF; // clear bit 0x40000
            if (oldFlags & 0x80000) {
                *(uint32_t*)((uint8_t*)thisPtr + 0x0C) = oldFlags & 0xFFF3FFFF; // clear bits 0x80000 and 0x40000
                if ((oldFlags & 1) && (*(uint32_t*)(*(uint32_t*)((uint8_t*)thisPtr + 0x10) + 0x14) & 0x20000000)) {
                    *(uint32_t*)((uint8_t*)thisPtr + 0x0C) = (oldFlags & 0xFFF3FFFF) | 0x80000000; // set high bit
                }
                updateStateFlags(thisPtr);
            }
        }
    }
    return;
}