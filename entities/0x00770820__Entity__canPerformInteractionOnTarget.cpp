// FUNC_NAME: Entity::canPerformInteractionOnTarget
// Address: 0x00770820
// This function checks if an interaction can be performed on the target entity (this)
// by the local player (stored in global pointer via EBX register convention).
// It validates state, component ownership, player state, and distance thresholds.

// Global player pointer (set by caller via EBX, treated as global for clarity)
extern Player* g_pPlayer;

// Distance thresholds for different player movement states
extern float g_fDistWalk;    // DAT_00e51c94
extern float g_fDistRun;     // DAT_00e51c90
extern float g_fDistSprint;  // DAT_00e51c8c

// Forward declaration: computes distance (presumably from player to interaction target)
float FUN_00470360(Player* player);

// Virtual function signature for component interface query (hash-based)
typedef bool (__thiscall *QueryInterfaceFn)(void* component, uint32_t hash, int* result);

class Entity {
public:
    // Offsets within Entity
    int32_t m_state;           // +0x88  (expected value 2)
    void*   m_pComponent;       // +0x64  (points to a sub-object, owner at -0x48)

    // Constructor/other members omitted for brevity

    // This function is the decompiled body
    bool canPerformInteractionOnTarget() {
        // 1. Target must be in valid state
        if (m_state != 2)
            return false;

        // 2. Component pointer must exist and not be a special sentinel (0x48)
        if (m_pComponent == nullptr || m_pComponent == (void*)0x48)
            return false;

        // 3. Retrieve owner of the component (object containing it at offset 0x48)
        void* componentOwner = (char*)m_pComponent - 0x48;

        // 4. Query component owner for interface via virtual function at vtable+0x10
        int queryResult = 0;
        QueryInterfaceFn queryFn = *(QueryInterfaceFn*)(*(int32_t*)componentOwner + 0x10);
        if (!queryFn(componentOwner, 0x55859efa, &queryResult))
            return false;

        // 5. Validate global player pointer
        if (g_pPlayer == nullptr)
            return false;

        // 6. Check player's current interaction target (at +0x74c)
        Entity* playerTarget = *(Entity**)((char*)g_pPlayer + 0x74c);
        if (playerTarget == nullptr || playerTarget == (Entity*)0x48)
            return false;

        // 7. Check player's flag at bit 10 (offset +0x8e0) – likely "in vehicle" or "stunt mode"
        uint32_t playerFlags = *(uint32_t*)((char*)g_pPlayer + 0x8e0);
        if (!(playerFlags & (1 << 10)))
            return false;

        // 8. Determine movement state from player's animation state (char at +0x165)
        char movementChar = *(char*)((char*)g_pPlayer + 0x165);
        float distanceThreshold;
        switch (movementChar) {
            case 0x15:  // Walk
                distanceThreshold = g_fDistWalk;
                break;
            case 0x17:  // Run
                distanceThreshold = g_fDistRun;
                break;
            case 0x18:  // Sprint
                distanceThreshold = g_fDistSprint;
                break;
            default:
                return false;   // Unknown movement state – interaction not allowed
        }

        // 9. Compute distance from player to target (function uses player pointer only)
        float distance = FUN_00470360(g_pPlayer);

        // 10. Allow interaction only if within range
        if (distance <= distanceThreshold)
            return true;

        return false;
    }
};