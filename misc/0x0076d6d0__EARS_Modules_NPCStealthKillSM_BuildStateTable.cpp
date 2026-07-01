// Xbox PDB: EARS_Modules_NPCStealthKillSM_BuildStateTable
// FUNC_NAME: NPCStealthKillSM::initializeStateMachine
void NPCStealthKillSM::initializeStateMachine()
{
    // Get the state machine name registration ID for "npcStealthKillST"
    int nameId = StateMachineManager::registerStateMachineName();
    
    // Set the state machine name
    StateMachineManager::setStateMachineName("npcStealthKillST", nameId);
    
    // Set initial state transition for "stealthKillInit" (no target state)
    StateMachineManager::setStateTransition("stealthKillInit", 0xFFFFFFFF);
    
    // Set state machine parameter to 0x23 (e.g., enable some flag)
    StateMachineManager::setStateParameter(0x23);
    
    // Add states with their IDs
    StateMachineManager::addState("terminate", 0x13);           // ID 19
    StateMachineManager::addState("stealthKill", 0x12);         // ID 18
    StateMachineManager::addState("approachKillTarget", 4);
    
    // Set transition for "approachKillTarget" to any state
    StateMachineManager::setStateTransition("approachKillTarget", 0xFFFFFFFF);
    
    // Set substate machine reference for "NPCChaseST" with priority 1
    StateMachineManager::setSubStateMachine("NPCChaseST", 1);
    
    // Re-add some states (likely to reinitialize)
    StateMachineManager::addState("terminate", 0x13);
    StateMachineManager::addState("stealthKill", 0x12);
    StateMachineManager::addState("terminate", 1);              // Another terminate state ID 1
    
    // Add transition from state "terminate" (ID 6?) with event 0x20 to state 1
    StateMachineManager::addStateTransition("terminate", 6, 0x20, 1);
    
    // Set transition for "stealthKill" to any state
    StateMachineManager::setStateTransition("stealthKill", 0xFFFFFFFF);
    
    // Set parameters
    StateMachineManager::setStateParameter(0x25);
    StateMachineManager::setStateParameter(0x24);
    StateMachineManager::setStateParameter(0x26);
    
    // Set substate machine for "seekTargetTable" with priority 1
    StateMachineManager::setSubStateMachine("seekTargetTable", 1);
    
    // Set parameter 8
    StateMachineManager::setStateParameter(8);
    // Enable something for parameter 8
    StateMachineManager::enableState(8);
    
    // Re-add terminate states
    StateMachineManager::addState("terminate", 0x13);
    StateMachineManager::addState("terminate", 7);
    
    // Set transition for "terminate" to any state
    StateMachineManager::setStateTransition("terminate", 0xFFFFFFFF);
    
    // Set parameter 2
    StateMachineManager::setStateParameter(2);
    
    // Register the state machine class with its vtable and name
    StateMachineManager::registerStateMachineClass(0xE4B1F57A, &NPCStealthKillSM::vtable, "NPCStealthKillSM");
    
    // Finalize initialization
    StateMachineManager::finalizeInitialization();
}