// FUNC_NAME: ObjectiveManager::triggerObjectives

#include <cstdint>

// Forward declarations
void profileScope(uint32_t scopeId);                                           // 0x00894c90
void fireObjectiveEvent(ObjectiveID* objectiveId, int zero);                   // 0x00408a00

// ID structure used for objective events (size 12 bytes, but only first 4 used)
struct ObjectiveID {
    uint32_t id;      // +0x00
    uint32_t zero;    // +0x04
    uint8_t  unused;  // +0x08  // padding, likely part of alignment
};

class ObjectiveManager {
public:
    void triggerObjectives();

private:
    // Field offsets (from this):
    // +0x180: pointer to flag structure
    // +0x29c: first objective ID
    // +0x2a4: second objective ID

    struct FlagStruct {
        uint32_t flags;   // +0x34
    };
};

void __fastcall ObjectiveManager::triggerObjectives()
{
    profileScope(0xdab8f267);  // Begin profile scope for objective trigger

    ObjectiveID objId;
    objId.id   = *(uint32_t*)(this + 0x29c);   // First objective identifier
    objId.zero = 0;
    objId.unused = 0;
    fireObjectiveEvent(&objId, 0);              // Fire objective event (pre‑activation?)

    FlagStruct* flagStruct = *(FlagStruct**)(this + 0x180);
    if ((flagStruct->flags >> 0x1a & 1) == 0)   // Check if bit 26 is clear (objective not yet active)
    {
        profileScope(0x33affd55);               // Begin nested profile scope
        flagStruct->flags |= 0x4000000;          // Set bit 26 – mark objective as active

        objId.id   = *(uint32_t*)(this + 0x2a4); // Second objective identifier
        objId.zero = 0;
        objId.unused = 0;
        fireObjectiveEvent(&objId, 0);           // Fire objective event (activation)
    }
}