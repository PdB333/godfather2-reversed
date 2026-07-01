// FUNC_NAME: SomeActionChecker::canPerformAction
// Address: 0x00770820
// Role: Checks if an action (e.g., grapple or attack) is available based on target state and distance.

// Global distance thresholds (from .data)
extern float g_fFightRange;      // DAT_00e51c94 (for state 0x15)
extern float g_fCloseRange;      // DAT_00e51c90 (for state 0x17)
extern float g_fGrappleRange;    // DAT_00e51c8c (for state 0x18)

// Forward declaration of the distance function (likely returns Euclidean distance between two entities)
extern float __cdecl getDistanceToEntity(class Entity* pEntity); // FUN_00470360

// Virtual method table offset 0x10: method that accepts a hash and writes an int.
// Typical EARS pattern: virtual bool hasProperty(uint32_t propertyHash, int& outValue) = 0;
// The hash 0x55859efa likely identifies a specific property (e.g., 'isEnemy' or 'isAggressive').

class SomeActionChecker
{
public:
    // Offsets (relative to this):
    // +0x88: int actionState (expected value 2 for this check)
    // +0x64 (100): int* pTargetEntity (pointer to Entity subclass, with offset -0x48 for vtable base)
    int actionState;       // +0x88
    int* pTargetEntity;    // +0x64 (0x100)

    bool __thiscall canPerformAction(class Entity* pPlayer) // unaff_EBX passed as this? Actually pPlayer is the entity referenced
    {
        // pPlayer is the entity pointer passed via EBX (global or caller register)
        if (actionState != 2)
            return false;
        if (pTargetEntity == nullptr)
            return false;

        // pTargetEntity is a pointer to some structure; subtract 0x48 to get the base object with vtable
        int* pTargetBase = (int*)(pTargetEntity - 0x48); // correct? pTargetEntity is an int*; subtract 0x48 in bytes? Actually (int*)((char*)pTargetEntity - 0x48)

        // Virtual call: pTargetBase->vtable[4] (offset 0x10)
        typedef bool (__thiscall* HasPropertyFunc)(void* pThis, uint32_t propHash, int* outValue);
        HasPropertyFunc hasProperty = *(HasPropertyFunc*)(*(int*)pTargetBase + 0x10);
        int outValue = 0;
        if (!hasProperty(pTargetBase, 0x55859efa, &outValue))
            return false;

        // pPlayer is required (passed via register EBX)
        if (pPlayer == nullptr)
            return false;

        int* pAnimState = *(int**)((char*)pPlayer + 0x74c); // pointer to animation state machine
        if (pAnimState == nullptr || pAnimState == (int*)0x48) // check both null and sentinel 0x48
            return false;

        uint32_t flags = *(uint32_t*)((char*)pPlayer + 0x8e0);
        if (!(flags & (1 << 10)))
            return false;

        // State at offset 0x165 in the animation state machine
        char animState = *(char*)((char*)pAnimState + 0x165);
        float fMaxDistance;
        switch (animState)
        {
        case 0x15: // 21
            fMaxDistance = g_fFightRange;
            break;
        case 0x17: // 23
            fMaxDistance = g_fCloseRange;
            break;
        case 0x18: // 24
            fMaxDistance = g_fGrappleRange;
            break;
        default:
            return false;
        }

        float fDist = getDistanceToEntity(pPlayer);
        return (fDist <= fMaxDistance);
    }
};