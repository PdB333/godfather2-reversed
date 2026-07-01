// FUNC_NAME: PlayerActionableTargetSM::update
void __thiscall PlayerActionableTargetSM::update(void)
{
    // +0x2c: pointer to current target (e.g., actionable object)
    if (*(int *)(this + 0x2c) == 0) {
        // +0x20 and +0x24: action state and substate pointers
        *(int *)(this + 0x20) = 0;
        *(int *)(this + 0x24) = 0;
    }

    // Prepare an event structure (likely for input or state transition)
    struct EventData event;          // local_c
    EventData_unknown local8;        // local_8 (unused beyond init)
    EventData_unknown local4;        // local_4 (unused beyond init)
    event = g_globalEventTemplate;   // DAT_0112fe10
    local8 = 0;
    local4 = 0;

    // Push the event into the global event system
    pushEventToSystem(&event, 0);    // FUN_00408a00

    // Update the global state manager
    updateGlobalStateManager(&g_stateManager); // DAT_012069c4, FUN_00408680
}