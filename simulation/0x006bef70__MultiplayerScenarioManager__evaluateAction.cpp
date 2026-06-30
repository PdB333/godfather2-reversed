// FUNC_NAME: MultiplayerScenarioManager::evaluateAction
// Function at 0x006bef70: Evaluates conditions and executes one of two action paths based on state flags and object IDs.
// The object has three sub-object pointers at +0x10, +0x14, +0x18 (likely target, instigator, participant).
// Flags at +0x34 control which path is taken.
// Returns: 0 = no action, 1 = action A executed, 2 = action B executed, 3 = error/abort.

int __fastcall MultiplayerScenarioManager::evaluateAction(int this)
{
    int targetId;          // iVar1 - ID from object at +0x10 (+0x40 offset)
    int instigatorId;      // iVar2 - ID from object at +0x14 (+0x54 offset)
    uint flags;            // uVar3 - bitfield at +0x34
    char canProceed;       // cVar4 - result of condition check

    // Read IDs from sub-objects
    targetId = *(int *)(*(int *)(this + 0x10) + 0x40);   // +0x10: pointer to target object, +0x40: some ID field
    instigatorId = *(int *)(*(int *)(this + 0x14) + 0x54); // +0x14: pointer to instigator object, +0x54: ID field

    // If instigator and target IDs differ, and participant's ID also differs from target, abort with error
    if ((instigatorId != targetId) && (*(int *)(*(int *)(this + 0x18) + 0x54) != targetId)) {
        logOrCleanup();   // FUN_008bd820 - likely logging or cleanup
        return 3;         // Error/abort
    }

    flags = *(uint *)(this + 0x34);   // +0x34: state flags (bitfield)

    // Check if bit 3 is clear (not in some state) AND
    // (bit 0 is set AND instigatorId equals a specific hash 0x637b907) OR (some flag at +0x20 is non-zero)
    if (((flags >> 3 & 1) == 0) &&
        ((((flags & 1) != 0 && (instigatorId == 0x637b907)) || (*(int *)(this + 0x20) != 0)))) {
        // Check bit 2: if clear, run a condition check
        if ((flags >> 2 & 1) == 0) {
            canProceed = checkCondition();   // FUN_006beb50
            if (canProceed == '\0') {
                return 0;   // Condition not met, no action
            }
        }
        // If instigator and target IDs differ, start an action on the instigator
        if (targetId != instigatorId) {
            startAction(instigatorId, 0, 0, 1);   // FUN_006b68c0
        }
        // Execute action A with the three sub-objects
        executeActionA(*(int *)(this + 0x14), *(int *)(this + 0x18), *(int *)(this + 0x10)); // FUN_006be8a0
        logOrCleanup();
        return 1;   // Action A executed
    }

    // Otherwise, execute action B
    executeActionB(*(int *)(this + 0x14), *(int *)(this + 0x18), *(int *)(this + 0x10)); // FUN_006be840
    logOrCleanup();
    return 2;   // Action B executed
}