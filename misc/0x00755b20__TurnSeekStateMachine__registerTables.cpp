// FUNC_NAME: TurnSeekStateMachine::registerTables
void TurnSeekStateMachine::registerTables()
{
    // Look up the table by name "setHeadingToEntityTable"
    uint32_t tableHandle = Engine::findTableByName("setHeadingToEntityTable");

    // If table not already registered, create and populate it
    if (!Engine::isTableRegistered(tableHandle))
    {
        // Create a new table entry (likely returns handle or pointer)
        uint32_t newTable = Engine::createNewTable();

        // Register the table with name "setHeadingToEntityTable"
        Engine::registerTable("setHeadingToEntityTable", newTable);

        // Set default action for "setHeadingToEntity" to invalid index (0xFFFFFFFF)
        Engine::setTableDefault("setHeadingToEntity", 0xFFFFFFFF);

        // Set the state type identifier (0x16 = 22, likely a type enum)
        Engine::setStateType(newTable, 0x16);

        // Register the callback function (at 0x00755af0) under hash 0x1b2d5c51 with the state machine name
        Engine::registerStateMachineCallback(0x1b2d5c51, reinterpret_cast<void*>(0x00755af0), "TurnSeekStateMachine");

        // Finalize table registration
        Engine::finalizeTableRegistration();
    }
}