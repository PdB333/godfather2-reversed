// FUNC_NAME: ActionOptions::canAct
// Function address: 0x0071ac00
// Returns 1 if the action can be performed, 0 otherwise.
// Checks proximity, owner state, and special conditions.

#include <cstdint>

// Global maximum squared distance for action
extern const float g_actionRangeSquared;

// Forward declarations of helper functions (from other modules)
extern void* getPlayerTransform();       // returns pointer to position data
extern int32_t getGameState();           // returns current game state ID

bool __thiscall ActionOptions::canAct(void* this_ptr) {
    // this_ptr points to ActionOptions instance
    // Offsets:
    //   +0x0c: Owner entity (pointer)
    //   +0x20: Target handle (uint32_t, 0 means no target)
    int32_t* owner = *(int32_t**)((char*)this_ptr + 0x0c);  // Owner entity
    int32_t targetHandle = *(int32_t*)((char*)this_ptr + 0x20); // Target handle

    // Check if there is a pending action list node in the owner
    int32_t listNode = *(int32_t*)((char*)owner + 0x24c4);
    if (listNode != 0) {
        int32_t actionContainer = listNode - 0x48; // Back-link to container
        if (actionContainer != 0) {
            // Virtual call on owner: getActionDistance(actionContainer)
            float actionDistModifier;
            void** vtable = *(void***)owner;
            typedef float (__thiscall *GetDistanceFunc)(void*, int32_t);
            GetDistanceFunc getDist = (GetDistanceFunc)vtable[0xbc / 4];
            actionDistModifier = getDist(owner, actionContainer);

            if (actionDistModifier != 0.0f) {
                // Check bit 14 (0xE) of owner flag at +0x8e4
                uint32_t flags = *(uint32_t*)((char*)owner + 0x8e4);
                if ((flags & (1 << 14)) == 0) {
                    // Get positions of two entities (likely player and another)
                    void* posA = getPlayerTransform(); // First entity position
                    void* posB = getPlayerTransform(); // Second entity position (or maybe different)

                    float dx = *(float*)((char*)posA + 0x30) - *(float*)((char*)posB + 0x30);
                    float dy = *(float*)((char*)posA + 0x34) - *(float*)((char*)posB + 0x34);
                    float dz = *(float*)((char*)posA + 0x38) - *(float*)((char*)posB + 0x38);
                    float distSq = dx*dx + dy*dy + dz*dz;

                    if (distSq <= g_actionRangeSquared) {
                        return true; // Within range
                    }
                    return false; // Too far
                }
            }
        }
    }

    // Fallback: if no target handle and game state is 3, allow action
    if (targetHandle == 0 && getGameState() == 3) {
        return true;
    }

    return false;
}