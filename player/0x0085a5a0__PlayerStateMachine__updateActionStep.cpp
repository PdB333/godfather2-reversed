// FUNC_NAME: PlayerStateMachine::updateActionStep
void __thiscall PlayerStateMachine::updateActionStep(PlayerStateMachine* this, PlayerState* state, int param3)
{
    uint flags;
    int entityType;
    int result;

    // Check if bit 4 of flags is set (0x44 offset)
    if ((*(uint*)(state + 0x44) >> 4 & 1) == 0) {
        // Normal state transition
        FUN_00859300(state, param3);
    } else {
        // Special state transition
        FUN_00859dd0(state);
    }

    // If state is 4 (e.g., "stunned" or "knockedDown"), reset action timer
    if (*(int*)(state + 0x30) == 4) {
        *(int*)(this + 0x14) = -1; // clear action timer
    }

    // Static update (e.g., frame counter, input processing)
    FUN_00858f50();

    // Check global flags: bit 0x15 (cover/action allowed?), bit 0xB (something else?)
    flags = *(uint*)(*(int*)(this + 0x3c) + 0xc88);
    if ((((flags >> 0x15 & 1) != 0) && ((flags >> 0xb & 1) == 0)) // condition: canDoAction && notRestricted
        && (*(int*)(state + 0x30) == 3) // state == ACTION (3)
        && (*(int*)(state + 0xc) != 0) // entityType exists
        && (*(int*)(state + 0xc) != 0x48)) // entityType is NOT player (0x48 = 72)
    {
        // Compute entity offset from type
        if (*(int*)(state + 0xc) == 0) {
            entityType = 0;
        } else {
            entityType = *(int*)(state + 0xc) + -0x48; // subtract base for non-player
        }
        // Lookup entity by hash (likely a database/ID)
        result = FUN_006c9470(entityType, 0x383225a1);
        if (result != 0) {
            // Get current frame/time
            int tick = FUN_00471610();
            // Spawn effect/object (0x14 = sound?, +0x30 offset, entityType, flag=0)
            FUN_00787700(0x14, tick + 0x30, entityType, 0);
        }
    }
}