// FUNC_NAME: SimManager::updateDeadEntities

#include <cstdint>

// Forward declarations
struct Entity;
struct GameTimeInfo;
enum GameState : int;

// Function prototypes (from other modules)
extern void getGameTimeInfo(GameTimeInfo& out); // FUN_0083e300
extern GameState getGameState(); // FUN_00806440
extern bool shouldKeepAlive(Entity* entity, const GameTimeInfo&); // FUN_0083c4c0
extern void destroyEntity(Entity* entity); // FUN_0083f190
extern void removeFromWorld(Entity* entity); // FUN_004088c0
extern void processDeletionQueue(); // FUN_006bccd0
extern void* getGlobalGameManager(); // FUN_007351c0
extern class IGameScript* getScriptManager(uint32_t globalData); // FUN_0043b870

// Virtual table offset for script active check
const uint32_t SCRIPT_ACTIVE_FUNC_OFFSET = 0x1C;
const uint32_t SCRIPT_FLAG_ARG = 0x100;

// Object offsets
const int32_t ENTITY_BASE_OFFSET = -0x48;   // +0x00 -> base Entity class
const int32_t REMOVAL_OFFSET = -0x0C;       // for removeFromWorld (another base?)
const int32_t FLAGS_OFFSET = 0x1F10;        // bitfield flags
const int32_t FUNC_TABLE_OFFSET = 0x110;    // function table pointer
const int32_t OBJECT_LIST_OFFSET = 0x74;    // pointer to array of object pointers
const int32_t OBJECT_COUNT_OFFSET = 0x78;   // number of objects in list
const uint32_t DESTROYED_FLAG = 0x02000000; // bit 25

void __fastcall SimManager::updateDeadEntities(int thisPtr)
{
    GameTimeInfo timeInfo;
    getGameTimeInfo(&timeInfo);

    uint32_t count = *(uint32_t*)(thisPtr + OBJECT_COUNT_OFFSET);
    if (count == 0) {
        return;
    }

    uint32_t* objectPtrArray = *(uint32_t**)(thisPtr + OBJECT_LIST_OFFSET);

    for (uint32_t i = 0; i < count; ++i) {
        uint32_t* objPtr = objectPtrArray + i * 2; // each slot is 8 bytes (two dwords?)
        // Actually the loop uses uVar6 * 8 offset, but reads a 4-byte pointer at that address.
        // So it's an array of 8-byte structures, but only first dword is used as pointer.
        Entity* entity = (Entity*)(*objPtr);
        if (entity == nullptr) {
            continue;
        }

        Entity* baseEntity = (Entity*)((char*)entity + ENTITY_BASE_OFFSET); // iVar1 = entity - 0x48
        if (baseEntity == nullptr) {
            continue;
        }

        uint32_t flags = *(uint32_t*)((char*)entity + FLAGS_OFFSET);
        bool isDestroyed = (flags >> 25) & 1; // bit 25

        if (!isDestroyed) {
            // Not destroyed – check game state and script conditions
            GameState state = getGameState();
            if (state == GAME_STATE_MISSION || state == GAME_STATE_FREEROAM) {
                // In mission or free roam: ensure function table pointer exists
                if (*(uint32_t*)((char*)entity + FUNC_TABLE_OFFSET) == 0) {
                    *(uint32_t*)((char*)entity + FUNC_TABLE_OFFSET) = (uint32_t)&FUNC_TABLE_DEFAULT; // LAB_006bcba0
                }
            } else {
                // Not in gameplay state – check if entity should be kept alive
                if (shouldKeepAlive(baseEntity, timeInfo)) {
                    // Entity is still needed – skip removal
                    goto RemoveEntity;
                }
            }

            // Check global script manager
            void* gameManager = getGlobalGameManager(); // FUN_007351c0
            if (gameManager == nullptr) {
                // fallback: destroy
                destroyEntity(baseEntity);
                continue;
            }

            bool isScriptActive = false;
            IGameScript* scriptMgr = getScriptManager(*(uint32_t*)0x01131040); // DAT_01131040
            if (scriptMgr != nullptr) {
                // Call virtual function at offset 0x1c with argument 0x100
                isScriptActive = (*reinterpret_cast<bool (__thiscall **)(IGameScript*, uint32_t)>(
                    *(uint32_t*)scriptMgr + SCRIPT_ACTIVE_FUNC_OFFSET))(scriptMgr, SCRIPT_FLAG_ARG);
            }

            if (isScriptActive) {
                // Script active – do not destroy
                continue;
            }

            // Script not active – destroy the entity
            destroyEntity(baseEntity);
            continue;
        }
        else {
            // Entity is destroyed – remove from world
RemoveEntity:
            Entity* removalBase = (Entity*)((char*)entity + REMOVAL_OFFSET);
            removeFromWorld(removalBase);
        }
    }

    // Process any pending deletion queue after the loop
    processDeletionQueue();
}

// Constants for game state
const GameState GAME_STATE_MISSION = 3;
const GameState GAME_STATE_FREEROAM = 2;

// Placeholder for the function table default (from LAB_006bcba0)
extern const uint8_t FUNC_TABLE_DEFAULT[]; // would be defined elsewhere