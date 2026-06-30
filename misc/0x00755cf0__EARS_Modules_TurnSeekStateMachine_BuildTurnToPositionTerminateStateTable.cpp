// Xbox PDB: EARS::Modules::TurnSeekStateMachine::BuildTurnToPositionTerminateStateTable
// FUNC_NAME: AnimationStateMachine::initTurnToPositionTerminateTable
void AnimationStateMachine::initTurnToPositionTerminateTable(void)
{
    // Get handle to the turn-to-position terminate table by name
    int tableHandle = getTable("turnToPositionTerminateTable");
    if (tableHandle == 0)
    {
        // Table doesn't exist yet – create and initialize it
        tableHandle = allocateTable();
        setTableName("turnToPositionTerminateTable", tableHandle);
        setDefaultAnimation("turnToPositionNoIdleAnims", 0xffffffff); // No idle anim
        addAnimation(0x1a); // Animation ID 26
        addAnimation(0x18); // Animation ID 24
        addAnimationWithPriority(0x13); // Animation ID 19 (priority variant)
        setAnimationFlags("turnToPositionAnimTable", 0xb); // +0x00? flags for another table
        setDefaultAnimation("turnToPositionAnimTable", 0xffffffff);
        addAnimation(2); // Animation ID 2
        registerStateMachine(0x1b2d5c51, (StateMachineUpdateFunc)updateTurnSeek, "TurnSeekStateMachine");
        finalizeStateMachine();
    }
}