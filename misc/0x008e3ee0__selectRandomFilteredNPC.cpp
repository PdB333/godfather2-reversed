// FUNC_NAME: selectRandomFilteredNPC
// Function address: 0x008e3ee0
// Role: Given a filter object, gathers up to 20 NPCs that satisfy conditions
// (bit flags, alive state, activity), then returns a random one.
// Uses a global NPC manager (DAT_0112a558) to iterate.

class NPC; // forward

struct NPCManager {
    uint32_t m_npcCount; // +0x38
    // other fields...
};

extern NPCManager* gNPCManager; // DAT_0112a558

// Forward declarations of helper functions (from game binary)
NPC* getNPCByIndex(uint32_t index); // FUN_006b0770
bool isNPCAlive(NPC* npc);          // FUN_006b8220
bool isNPCInActiveState();          // FUN_006b4440 (global state check)
void* allocateMemory(size_t size);  // FUN_009c8e80
void freeMemory(void* ptr);         // FUN_009c8f10
void logWarning(uint32_t code);     // FUN_00849170

// Parameters: param_1 is 'this' pointer to an object that has a filter flag at +0x84
NPC* selectRandomFilteredNPC(void* filterObject) {
    NPC* result = 0;
    uint32_t candidateCount = 0;
    uint32_t maxCandidates = 20; // 0x14
    NPC** candidateArray = (NPC**) allocateMemory(maxCandidates * sizeof(NPC*)); // 0x50 bytes
    if (!candidateArray) return 0;

    uint32_t npcCount = gNPCManager->m_npcCount;
    uint32_t filterFlag = *(uint32_t*)((uint8_t*)filterObject + 0x84);
    bool filterIncludeFlag = (filterFlag >> 2) & 1; // bit2 of the flag

    for (uint32_t i = 0; i < npcCount; i++) {
        NPC* npc = getNPCByIndex(i);
        // Condition: if filterIncludeFlag is set, then require npc's field at +0xf4 to be 0 (likely 'dead' flag)
        // Then also require both helper checks to pass.
        bool includeDead = !filterIncludeFlag; // if flag not set, allow dead?
        bool npcDeadFlag = *(int32_t*)((uint8_t*)npc + 0xf4) == 0; // 0 means alive?
        if ((!filterIncludeFlag || npcDeadFlag) && isNPCAlive(npc) && isNPCInActiveState()) {
            if (candidateCount >= maxCandidates) {
                logWarning(0x28); // warns when exceeding limit
                // Bug? Does not break, continues and overflows the allocated array
                // The original code sets candidateCount back to current value (no change)
                candidateCount = candidateCount; // no op
            }
            candidateArray[candidateCount] = npc;
            candidateCount++;
        }
    }

    if (candidateCount > 0) {
        uint32_t randomIndex = rand() % candidateCount;
        result = candidateArray[randomIndex];
    }

    freeMemory(candidateArray);
    return result;
}