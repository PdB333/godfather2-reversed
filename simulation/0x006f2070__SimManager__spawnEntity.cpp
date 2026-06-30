// FUNC_NAME: SimManager::spawnEntity
// Address: 0x006f2070
// Role: Attempts to spawn an entity from data, with two possible spawn paths (immediate or deferred).
//       If successful, may additionally perform multiplayer-specific physics cleanup.

// Known offsets in this:
// +0x10: EntityData* m_entityData (non-zero if data is loaded)
// +0x14: bool   m_playerFlag (controls bit-4 of flags)

// Local references need to be cast appropriately.

#include <cstdint>

// Forward declarations of called functions (stubs – replace with actual)
extern bool isStreamingActive();                                           // FUN_00842880
extern bool isLoadingComplete();                                          // FUN_006f08e0
extern bool prepareEntityForSpawn(void* entityData);                      // FUN_006f7330
extern bool spawnEntityImmediate(void* world, void* entityData, uint32_t param2, uint32_t retaddr, uint32_t flags, int, int); // FUN_006f77a0
extern void* getCurrentWorld(void* world);                                // FUN_006eafe0
extern bool createEntityInstance(void* entityData);                       // FUN_006f3b30
extern bool addEntityToWorld(void* entityData, uint32_t param2, bool flag, uint32_t retaddr, uint32_t flags, int, int, int); // FUN_006f3e10
extern bool isNetworkSession();                                           // FUN_00445250
extern bool hasAuthority();                                               // FUN_004209a0
extern void* findComponentByHash(void* obj, uint32_t hash);              // FUN_006bc8d0
extern void* getComponentByType(void* obj, int type);                    // FUN_00446100
extern void addReference(void* comp);                                    // FUN_00732190
extern void releaseReference();                                          // FUN_007f6480

bool __thiscall SimManager::spawnEntity(void* world,                // unaff_EBP – likely a World* or SimManager*
                                        uint32_t param_2,           // unknown – possibly a user ID or transform
                                        uint32_t param_3,           // unknown – used only in multiplayer branch
                                        uint32_t param_4)           // flags (bit-4 ORed from m_playerFlag)
{
    uint32_t dummyLocal;
    uint32_t securityCookie = DAT_01223410; // stack cookie – ignore

    // Obtain a manager from this (e.g., ResourceManager)
    void* resourceManager = getComponentByType(this, 0);
    if (resourceManager == nullptr) {
        return false;
    }

    // Check if a specific resource (hash 0x55859efa) is available
    dummyLocal = 0;
    bool resourceOk = (*(bool(__thiscall**)(void*, uint32_t, uint32_t*))(*(uint32_t*)resourceManager + 0x10))
                     (resourceManager, 0x55859efa, &dummyLocal);
    if (!resourceOk) {
        return false;
    }

    if (world == nullptr) {
        return false;
    }

    // Only proceed if streaming is not busy and loading is complete,
    // and we have valid entity data at this+0x10.
    if (!isStreamingActive() && !isLoadingComplete() && (*(void**)((uint8_t*)this + 0x10) != nullptr))
    {
        void* entityData = *(void**)((uint8_t*)this + 0x10);

        // First spawn path: immediate
        bool firstSuccess = prepareEntityForSpawn(entityData);
        bool firstSpawnResult = false;
        if (firstSuccess)
        {
            // Build flags: combine param_4 with bit-4 from m_playerFlag
            bool playerFlag = *(bool*)((uint8_t*)this + 0x14);
            uint32_t combinedFlags = param_4 | ((playerFlag ? 0 : 1) & 4); // -(uint)(playerFlag != 0) & 4 | param_4
            firstSpawnResult = spawnEntityImmediate(world, entityData, param_2, 0, combinedFlags, 0, 0);
        }

        if (!firstSuccess || !firstSpawnResult)
        {
            // First path failed – try deferred spawn
            void* scene = getCurrentWorld(world);  // local_4 reassigned
            bool secondInit = createEntityInstance(entityData);
            if (secondInit)
            {
                bool playerFlag = *(bool*)((uint8_t*)this + 0x14);
                uint32_t combinedFlags = param_4 | ((playerFlag ? 0 : 1) & 4);
                bool secondSpawnResult = addEntityToWorld(entityData, param_2, playerFlag, 0, combinedFlags, 0, 0, 0);
                if (!secondSpawnResult)
                    goto fail;
            }
            else
            {
                goto fail;
            }
        }

        // If we reach here, one of the spawn paths succeeded.
        // Multiplayer-specific cleanup: if network session and we are the host,
        // find physics components and adjust reference counts.
        if (isNetworkSession() && !hasAuthority())  // note: condition means "is network but we aren't host"?
        {
            void* physicsWorld1 = findComponentByHash(world, 0x369ac561);
            void* physicsWorld2 = nullptr;
            void* component = getComponentByType(param_3, 0);
            if (component != nullptr)
            {
                physicsWorld2 = findComponentByHash(component, 0x369ac561);
            }

            if (physicsWorld1 != nullptr && physicsWorld2 != nullptr)
            {
                addReference(physicsWorld2);
                releaseReference();
                addReference(physicsWorld1);
                releaseReference();
                return true;
            }
        }
        return true;
    }
    else
    {
fail:
        return false;
    }
}