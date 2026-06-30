// Xbox PDB: EARS::Modules::TurnSeekStateMachine::BuildSeekTargetTerminateStateTable
// FUNC_NAME: SeekTargetTerminateStateMachine::initialize
void SeekTargetTerminateStateMachine::initialize()
{
    // Look up the hash for the "seekTargetTerminateTable" symbol
    uint32_t tableId = lookupStringHash("seekTargetTerminateTable");

    // Check if the table already exists
    if (doesTableExist(tableId) == 0)
    {
        // Get the resource manager (likely for creating tables)
        uint32_t resourceMgr = getResourceManager();

        // Register the table with the resource manager
        registerTable("seekTargetTerminateTable", resourceMgr);

        // Set the "seekToTargetNoAnims" flag to -1 (meaning disabled or unset)
        setTableEntry("seekToTargetNoAnims", 0xFFFFFFFF);

        // Allocate space for 0x14 (20) entries in the state machine
        allocateTableEntries(0x14);

        // Add transitions: first with index 10, then with index 11
        // (These likely represent state transitions for the seek target terminate behavior)
        addTransition(&gSeekTargetTerminateTable, 10);
        addTransition(&gSeekTargetTerminateTable, 11);

        // Set the "seekToTargetNoAnims" entry again? Or set a separate entry?
        setTableEntry(&gSeekTargetTerminateTable, 0xFFFFFFFF);

        // Set the initial state to index 2
        setInitialState(2);

        // Bind this table to the "TurnSeekStateMachine" state machine
        bindStateMachine(0x1b2d5c51, &LAB_00755af0, "TurnSeekStateMachine");

        // Finalize / apply the table changes
        finalizeTable();
    }
}