// FUNC_NAME: CrimeManager::updateCrimeParticipants
// Address: 0x00706380
// Role: For a given crime type (0-10), finds eligible NPCs/entities and marks them as participants.
//        Called when a crime is active and the game is running. Iterates over a participant list
//        and sets entity indices and flags.

#include <cstdint>

struct CrimeData {
    int field0;  // +0x00
    int field4;  // +0x04
    int field8;  // +0x08
    int fieldC;  // +0x0C
};

struct Entity {
    int participantIndex; // +0x18
    int type;             // +0x?? (used via getEntityType)
    char unknown1A8;      // +0x1A8
    uint stateFlags;      // +0x2D8
};

// Stubs for external functions (real names would be resolved from the binary)
extern CrimeData* getCrimeData(uint crimeType);                               // 0x007aa2f0
extern bool isGameActive();                                                   // 0x00445250
extern void getParticipantRange(void* rangeBase, uint& outStart, uint& outEnd); // 0x00705bf0
extern EntityManager* getEntityManager(void* thisPtr);                       // 0x00445f00 (uses this+0xF0)
extern Entity* findFirstEntityByCriteria(CrimeData*, EntityManager*, int, int, int); // 0x00856780
extern uint getEntityType(Entity*);                                          // 0x00704860
extern void setEntityFlag(Entity*, int flag);                                // 0x007062a0
extern void showObjective(int index);                                        // 0x007014d0
extern void freeList(void* listHead);                                        // 0x004daf90

void CrimeManager::updateCrimeParticipants(uint crimeType)
{
    if (crimeType >= 0xB) // Maximum crime type index
        return;

    CrimeData* crimeData = getCrimeData(crimeType);
    if (crimeData == nullptr)
        return;

    // Check if the crime data has any active elements (none of the first four fields is entirely zero)
    if (crimeData->field0 == 0 &&
        crimeData->field4 == 0 &&
        crimeData->field8 == 0 &&
        crimeData->fieldC == 0)
    {
        return;
    }

    if (!isGameActive())
        return;

    // Base of the participant list array for this crime type
    // Each entry is 20 bytes (5 * 4), starting at offset (crimeType * 5 + 5) * 4 relative to 'this'
    void* participantRangeBase = reinterpret_cast<void*>(
        reinterpret_cast<uintptr_t>(this) + (crimeType * 5 + 5) * 4
    );

    uint startIdx, endIdx;
    getParticipantRange(participantRangeBase, startIdx, endIdx);

    EntityManager* entityMgr = *reinterpret_cast<EntityManager**>(
        reinterpret_cast<uintptr_t>(this) + 0xF0
    );

    for (uint i = startIdx; i < endIdx; ++i)
    {
        // Search for an entity matching the crime data (parameters 3-5 are zero)
        Entity* entity = findFirstEntityByCriteria(crimeData, entityMgr, 0, 0, 0);
        if (entity == nullptr)
            continue;

        entity->participantIndex = i; // +0x18

        uint entityType = getEntityType(entity);
        if (entityType == crimeType)
        {
            setEntityFlag(entity, 1);
            if (entity->unknown1A8 == 1)   // +0x1A8
            {
                showObjective(0);
                entity->stateFlags |= 0x20; // +0x2D8
            }
        }
    }

    // Clean up the list if it was allocated (local_10[0] != 0 in original)
    if (startIdx != 0)
    {
        freeList(nullptr); // Placeholder; actual cleanup uses 'startIdx' as a pointer
    }
}