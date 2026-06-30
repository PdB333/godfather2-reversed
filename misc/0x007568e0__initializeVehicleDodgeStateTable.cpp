// FUNC_NAME: initializeVehicleDodgeStateTable

void initializeVehicleDodgeStateTable(void)
{
    // Retrieve or create the state table for vehicle dodge states
    int stateTableId = findStateTable("vehicleDodgeStateTable");
    if (stateTableId == 0) {
        // Table not yet created, build it
        int newTable = createNewStateTable();
        registerStateTable("vehicleDodgeStateTable", newTable);

        // Define states
        defineState("dodgeInit", 0xFFFFFFFF);
        addTransition(10);
        addTransition(0xB);

        linkState("dodgeLeft", 0xB);
        linkState("dodgeRight", 10);
        linkState("dodgeCower", 0xC);
        linkState("terminate", 0xD);

        defineState("dodgeLeft", 0xFFFFFFFF);
        addTransition(0xD);
        setStateEntryAction(8);
        setStateExitAction(0xF);
        setStateExitAction(0x10);
        linkState("terminate", 7);

        defineState("dodgeRight", 0xFFFFFFFF);
        addTransition(0xC);
        setStateEntryAction(8);
        setStateExitAction(0xF);
        setStateExitAction(0x10);
        linkState("terminate", 7);

        defineState("dodgeCower", 0xFFFFFFFF);
        addConditionalTransition(0xABDB8E78, 1, 1, 0, 1.0f);
        setStateEntryAction(8);
        setStateExitAction(0xF);
        setStateExitAction(0x10);
        linkState("terminate", 7);

        defineState("terminate", 0xFFFFFFFF);
        addTransition(2);
        registerStateMachine(&LAB_007568b0, "VehicleDodgeStateMachine");
        finalizeStateMachine();
    }
}