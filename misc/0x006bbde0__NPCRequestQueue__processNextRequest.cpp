// FUNC_NAME: NPCRequestQueue::processNextRequest
#pragma pack(push, 1)
struct NPCRequestList {
    void**    items;    // +0x00: array of pointers to NPC data
    uint32_t  count;    // +0x04: number of elements in array
};

class NPCRequestQueue {
public:
    void*           m_manager;          // +0x00: pointer to spawn manager (e.g., EventScheduler?)
    NPCRequestList* m_pRequestList;     // +0x04: pointer to list of pending NPC request data
    uint32_t        m_maxPerFrame;      // +0x08: maximum successful activations per frame
    uint32_t        m_currentIndex;     // +0x0C: current index in the request list (for iteration)
    uint32_t        m_successCount;     // +0x10: count of successful activations in this frame

    // Returns true if a request was processed, false if none available or budget exhausted.
    bool __thiscall processNextRequest(int* remainingBudget);
};
#pragma pack(pop)

// External helper functions (likely from the engine)
extern bool IsGamePaused();                                 // FUN_007912e0
extern void* GetActivePlayer();                              // FUN_00791540 (returns player or game state pointer)
extern bool IsNpcAlreadyActive(void* npcData);               // FUN_006bbcf0
extern void ScheduleSpawnEvent(void* manager, int eventID); // FUN_00791250

bool NPCRequestQueue::processNextRequest(int* remainingBudget) {
    // If we already reached the per‑frame limit, return false
    if (m_maxPerFrame <= m_successCount) {
        return false;
    }

    char result = 0;
    // Iterate through remaining requests until we either succeed or hit the limit
    while (m_currentIndex < m_pRequestList->count) {
        // Re‑check limit early (might have been reached by an intermediate success)
        if (m_maxPerFrame <= m_successCount) {
            return result; // 0 (false) or 1 (true) depending on previous success
        }
        // If we already processed a request this call, return immediately
        if (result != 0) {
            return result;
        }

        // Get the next pending NPC data pointer
        void* npcData = m_pRequestList->items[m_currentIndex];
        m_currentIndex++;

        // Check if the game is paused
        bool gamePaused = IsGamePaused();
        if (gamePaused) {
            continue;
        }

        // Read NPC state flags at offset 0x5C
        uint32_t npcFlags = *(uint32_t*)((char*)npcData + 0x5C);
        // Must not have flags 0x20000 or 0x40000 set (e.g., dead, inactive)
        if ((npcFlags & 0x60000) != 0) {
            continue;
        }
        // Bit 0x100000 (maybe "already processed") must not be set
        if ((npcFlags >> 0x14) & 1) {
            continue;
        }
        // Bit 0x4000000 (another blocking flag) must not be set
        if ((npcFlags >> 0x1A) & 1) {
            continue;
        }

        // Check the active player / game state
        void* activePlayer = GetActivePlayer();
        if (activePlayer == nullptr) {
            continue;
        }
        // Bit 5 of the player's state at offset 0x84 must not be set (e.g., "in combat")
        uint32_t playerFlags = *(uint32_t*)((char*)activePlayer + 0x84);
        if ((playerFlags & (1 << 5)) != 0) {
            continue;
        }

        // Ask the request‐specific check: is this NPC already active?
        bool alreadyActive = IsNpcAlreadyActive(npcData);
        if (!alreadyActive) {
            // NPC is not active, we can spawn it (if we have budget)
            if (*remainingBudget != 0) {
                m_successCount++;
                (*remainingBudget)--;
                result = 1;   // success
                // Schedule the actual spawn event via the manager
                ScheduleSpawnEvent(m_manager, 0xFFFFFFFF);
            }
        } else {
            // NPC is already active – count it as a success (but no budget consumption)
            m_successCount++;
            result = 1;   // success
        }
    }
    return result;
}