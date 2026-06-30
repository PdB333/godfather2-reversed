// FUNC_NAME: ObjectiveManager::updateObjectiveState
void __thiscall ObjectiveManager::updateObjectiveState(int objectiveId, int newState)
{
    // this at unaff_EDI, passed in ECX (__thiscall)
    ObjectiveManager* thisManager = this;
    bool canUpdate;

    // Check if this objective can transition to the given state
    // Uses data from this+0x54 (mission data) +0x30 (objective list) and an extra register (in_EAX)
    canUpdate = isObjectiveUpdateAllowed(thisManager, objectiveId,
                                         *(int*)(*(int*)((int)thisManager + 0x54) + 0x30),
                                         /* in_EAX - possibly a context flag */ );

    if (canUpdate != false) {
        // Call a global vtable function (likely a sound/UI notification)
        ((void (*)(void))(*DAT_012058e8 + 0x1c))();

        if ((newState != 2) && (newState != 4)) {
            // States other than 2 (success?) or 4 (failure?) just do cleanup
            performCleanup();
            return;
        }

        // For success/failure states, play effect, call component on this+0xa0, then cleanup
        playMissionEndEffect();

        // Call a virtual function on the component at offset 0xA0
        ((void (*)(void*))(*(int*)PTR_FUN_0110ac14))((void*)((int)thisManager + 0xA0));

        performCleanup();

        // Another global virtual call (maybe finalize)
        ((void (*)(void))(*(int*)PTR_FUN_0110ac18))();
    }
}