// Xbox PDB: EARS::Modules::CoverDashSM::BuildCoverDashStateTable
// FUNC_NAME: CoverDashStateMachine::initialize
void CoverDashStateMachine::initialize(void)
{
    // Get the state machine manager instance
    void *manager = StateMachineManager::getInstance(); // FUN_009c8f80

    // Register the main cover dash state
    StateMachineManager::addState(manager, "CoverDashST", 0); // FUN_004ad9d0
    // Add a transition from CoverDashST to itself? Or to an error state: ID -1 means wildcard?
    StateMachineManager::addTransition(manager, &DAT_00d63420, 0xFFFFFFFF); // FUN_004adae0

    // Set initial state? ID 0x23 = 35
    StateMachineManager::setInitialState(manager, 0x23); // FUN_004acf70

    // Register states with specific IDs
    StateMachineManager::registerState(manager, "pathFailureTooFar", 0x15); // FUN_004acc70
    StateMachineManager::registerState(manager, &DAT_00d65a18, 4); // DAT could be a string like "pathFailureNoPath"?
    StateMachineManager::addTransition(manager, &DAT_00d65a18, 0xFFFFFFFF); // transition to wildcard

    // Add a conditional transition (3, 0x4020, 1) – condition type, param, flag
    StateMachineManager::addTransitionCondition(manager, 3, 0x4020, 1); // FUN_004ad0f0

    // Enable states by name
    StateMachineManager::setStateEnabled(manager, "ContinualBurstFireST", 1); // FUN_004acf10
    StateMachineManager::setStateEnabled(manager, "FollowPathST", 1);

    // Disable states by ID
    StateMachineManager::disableState(manager, 0x24); // FUN_004acff0
    StateMachineManager::disableState(manager, 0x27);
    StateMachineManager::setStateTerminal(manager, 0x28); // FUN_004ad070? Or maybe "setStateAsTerminal"

    // Register state with properties (name, id, flags, something)
    StateMachineManager::registerStateWithProperties(manager, "pathFailureNoPath", 10, 0x20, 1); // FUN_004acd20

    // Register more states
    StateMachineManager::registerState(manager, "pathError", 0x13);
    StateMachineManager::registerState(manager, "pathFailureTooFar", 0x15);
    StateMachineManager::registerState(manager, "errorDone", 0x14);
    StateMachineManager::registerState(manager, &DAT_00d63afc, 0x17); // DAT likely "pathSuccess"? or another string

    // Add transitions from these states to wildcard (error handler)
    StateMachineManager::addTransition(manager, "pathFailure", 0xFFFFFFFF);
    StateMachineManager::setInitialState(manager, 0x29);
    StateMachineManager::registerState(manager, "pathError", 4);
    StateMachineManager::addTransition(manager, "pathFailureNoPath", 0xFFFFFFFF);
    StateMachineManager::setInitialState(manager, 0x2A);
    StateMachineManager::registerState(manager, "pathError", 4);
    StateMachineManager::addTransition(manager, "pathFailureTooFar", 0xFFFFFFFF);
    StateMachineManager::setInitialState(manager, 0x2B);
    StateMachineManager::registerState(manager, "pathError", 4);
    StateMachineManager::addTransition(manager, "pathError", 0xFFFFFFFF);

    // Register final states
    StateMachineManager::registerState(manager, &DAT_00d63afc, 0x16);
    StateMachineManager::registerState(manager, "errorDone", 4);
    StateMachineManager::addTransition(manager, "errorDone", 0xFFFFFFFF);
    StateMachineManager::setInitialState(manager, 0x26);
    StateMachineManager::setInitialState(manager, 2);
    StateMachineManager::addTransition(manager, &DAT_00d63afc, 0xFFFFFFFF);
    StateMachineManager::setInitialState(manager, 0x25);
    StateMachineManager::setInitialState(manager, 2);

    // Finalize the state machine with a unique hash, update function, and name
    StateMachineManager::createStateMachine(manager, 0x14cbc763, &CoverDashSM::update, "CoverDashSM"); // FUN_004adc90
    StateMachineManager::finalize(manager); // FUN_004ada40
}