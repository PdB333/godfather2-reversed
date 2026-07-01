// Xbox PDB: EARS_Modules_PlayerLungeAttackSM_BuildStateMachine
// FUNC_NAME: PlayerLungeAttackSM::registerStateTable
void PlayerLungeAttackSM::registerStateTable()
{
    // Obtain a new state table ID from the state machine manager
    uint stateTableId = StateMachineManager::createStateTableID();

    // Register the state table for the player lunge attack with the generated ID
    StateMachineManager::registerStateTable("playerLungeAttackStateTable", stateTableId);

    // Add the initial state "lungeAttackInit" with no parent transition (0xFFFFFFFF)
    StateMachineManager::addState("lungeAttackInit", 0xFFFFFFFF);
    // Set the animation ID for this state (0x31 = 49, e.g., lunge start)
    StateMachineManager::setAnimationID(0x31);

    // Add the main lunge attack state with a duration of 4 (seconds or frames)
    StateMachineManager::addState("lungeAttack", 4);
    StateMachineManager::addState("lungeAttack", 0xFFFFFFFF);
    // Set animation ID for the lunge attack (0x32 = 50)
    StateMachineManager::setAnimationID(0x32);

    // Register the terminate state with parameters: name, priority=9, flag0=0, flag1=1
    StateMachineManager::registerTerminateState("terminate", 9, 0, 1);
    StateMachineManager::addState("terminate", 0xFFFFFFFF);
    StateMachineManager::setAnimationID(2);

    // Register the state machine itself: pointer to a static label, pointer to label code, name
    StateMachineManager::registerStateMachine(0x2d5cbc4, &LAB_007bf360, "PlayerLungeAttackSM");

    // Finalize the registration (e.g., commit changes to runtime table)
    StateMachineManager::finalizeRegistration();
}