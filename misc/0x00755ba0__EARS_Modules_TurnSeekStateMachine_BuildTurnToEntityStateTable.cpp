// Xbox PDB: EARS::Modules::TurnSeekStateMachine::BuildTurnToEntityStateTable
// FUNC_NAME: AIStateMachineManager::registerTurnSeekStateMachine
void AIStateMachineManager::registerTurnSeekStateMachine(void)
{
    uint32_t tableKey;
    int32_t tableExists;

    tableKey = hashString("turnToEntityTable");
    tableExists = findTable(tableKey);
    if (tableExists == 0) {
        // Table doesn't exist yet – create and populate it
        void* manager = getStateMachineManager();              // singleton / global
        createTable(manager, "turnToEntityTable", tableKey);    // +0x? : creates a new table keyed by hash
        addEntity(manager, "turnToEntity", 0xFFFFFFFF);          // +0x? : register a default entity (-1 = none)
        setMaxStates(manager, 0x12);                            // +0x? : allocate room for 18 state slots
        registerStateMachine(manager, 0x1b2d5c51,               // hash for "TurnSeekStateMachine"
                             &TurnSeekStateMachine_Update,      // callback at LAB_00755af0
                             "TurnSeekStateMachine");           // debug name
        finalizeTable(manager);                                 // +0x? : commit registration
    }
    return;
}