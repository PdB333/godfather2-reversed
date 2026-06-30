// FUNC_NAME: EntityManager::findSlotById
#include <cstdint>

// External mutex lock/unlock functions (thread-safe access)
extern void lockMutex(uint32_t* mutex);
extern void unlockMutex(uint32_t* mutex);
extern uint32_t gManagerMutex; // 0x00e2cbe8

// Internal structure representing a group of IDs
struct IdSlotGroup {
    uint32_t count;        // +0x104: number of IDs in the group
    uint32_t ids[];        // +0x4: array of IDs (variable length, count elements)
};

// Manager class holding an array of pointers to IdSlotGroup objects
class EntityManager {
public:
    // Returns the index of the slot group containing the given ID, or -1 if not found.
    int __thiscall findSlotById(uint32_t id) {
        lockMutex(&gManagerMutex);

        uint32_t groupCount = *(uint32_t*)((uint8_t*)this + 0x328);
        if (groupCount == 0) {
            unlockMutex(&gManagerMutex);
            return -1;
        }

        // Pointer to the array of IdSlotGroup pointers at this+0x228
        intptr_t* groupPtrArray = (intptr_t*)((uint8_t*)this + 0x228);

        for (uint32_t groupIndex = 0; groupIndex < groupCount; ++groupIndex) {
            IdSlotGroup* group = (IdSlotGroup*)*groupPtrArray;
            uint32_t numIds = group->count;

            for (uint32_t subIndex = 0; subIndex < numIds; ++subIndex) {
                if (group->ids[subIndex] == id) {
                    unlockMutex(&gManagerMutex);
                    return groupIndex; // Found -> return the group index
                }
            }

            ++groupPtrArray; // Move to next group pointer
        }

        unlockMutex(&gManagerMutex);
        return -1; // Not found
    }
};