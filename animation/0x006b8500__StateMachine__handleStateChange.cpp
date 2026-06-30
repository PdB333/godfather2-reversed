// FUNC_NAME: StateMachine::handleStateChange
// Address: 0x006b8500
// Role: Handles state transitions for an entity, possibly part of a state machine.
// Uses fields at offsets: +0x58 (entityHandle), +0x5c (stateId), +0x60 (flags), +0x64 (extraPtr).
// Calls helper functions for object lookup, state reset, and transition.

void __thiscall StateMachine::handleStateChange(int this)
{
    int entityPtr; // pointer returned from getEntityByHandle
    int oldStateId;
    int newStateObj;
    int fromStateObj;
    char globalByte; // from global DAT_0112a590+4

    entityPtr = getEntityByHandle(*(int *)(this + 0x58)); // e.g., EntityManager::getByHandle
    if (entityPtr != 0) {
        // Check if current state matches the one in the entity
        if (*(int *)(entityPtr + 0x40) == *(int *)(this + 0x5c)) {
            // Already in that state → finalize
            finalizeGlobalUpdate(); // FUN_008c7330
            if ((*(unsigned int *)(this + 0x60) >> 1 & 1) != 0) {
                finishStateMachine(); // FUN_006b59f0
                return;
            }
        }
        else {
            // Transition to new state
            globalByte = *(char *)(DAT_0112a590 + 4);
            if ((*(char *)(this + 0x60) & 1) != 0) {
                setState(0); // FUN_0084ab30(0)
            }
            oldStateId = *(int *)(entityPtr + 0x40);
            newStateObj = 0;
            resetState(*(int *)(this + 0x5c), 0, 0, 0); // FUN_006b68c0
            // Handle special case: state ID 0x637b907 and extraPtr present
            if ((*(int *)(this + 100) != 0) && (*(int *)(this + 0x5c) == 0x637b907)) {
                newStateObj = getObjectByID(0x637b907); // FUN_008c74d0
                attachEntity(*(int *)(this + 100), entityPtr); // FUN_008c10d0
            }
            if ((*(char *)(this + 0x60) & 1) == 0) {
                // Use computed state objects
                if (newStateObj == 0) {
                    newStateObj = getObjectByID(*(int *)(this + 0x5c)); // FUN_008c74d0
                }
                fromStateObj = getObjectByID(oldStateId);
                transitionToNewState(newStateObj, fromStateObj, entityPtr); // FUN_006be8a0
            }
            else {
                setState(globalByte); // FUN_0084ab30(globalByte)
            }
            if ((*(unsigned int *)(this + 0x60) >> 1 & 1) != 0) {
                finishStateMachine(); // FUN_006b59f0
                return;
            }
        }
    }
    return;
}