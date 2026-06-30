// Xbox PDB: EARS::Modules::NPCBackupSM::BuildStateMachine
// FUNC_NAME: NPCBackUpComponent::initializeBackupStateMachine
void NPCBackUpComponent::initializeBackupStateMachine(void)
{
  // Get a unique identifier for the state machine (likely from a string table or pool)
  uint stateMachineId = StateMachineManager::allocateId(); // 0x009c8f80

  // Register the state machine with a label "NPCBackupST"
  StateMachineManager::registerStateMachine("NPCBackupST", stateMachineId); // 0x004ad9d0

  // Set default timeout or transition for "backup" state (ID 0xffffffff = infinite?)
  StateMachine::addTransition(&gStateMachineData, 0xffffffff, "backup"); // 0x004adae0

  // Add state with ID 0x14 (20) 
  StateMachine::addState(20); // 0x004acf70

  // Add transient state definitions (name, id)
  StateMachine::addStateDefinition("terminate", 11);   // 0x0b
  StateMachine::addStateDefinition("backup", 13);      // 0x0d
  StateMachine::addStateDefinition("backup", 10);
  StateMachine::addStateDefinition("turnToTarget", 4);

  // Add transition from state "turnToTarget" to arbitrary state (-1 = any)
  StateMachine::addTransition("turnToTarget", 0xffffffff);

  // Add states with IDs 0x0e, 0x11, 0x12, 0x08
  StateMachine::addState(14);
  StateMachine::addState(17);
  StateMachine::addState(18);
  StateMachine::addState(8);

  // Conditional transitions? (state-based triggers)
  StateMachine::addConditionalTransition(17); // 0x11
  StateMachine::addConditionalTransition(19); // 0x13
  StateMachine::addConditionalTransition(8);

  // Re-define "terminate" and "backup" states (maybe override)
  StateMachine::addStateDefinition("terminate", 11);
  StateMachine::addStateDefinition("backup", 10);

  // Override transition from "backup" to any
  StateMachine::addTransition("backup", 0xffffffff);

  // Additional states
  StateMachine::addState(15);
  StateMachine::addState(17);
  StateMachine::addState(18);
  StateMachine::addState(16);

  // More conditional transitions
  StateMachine::addConditionalTransition(17);
  StateMachine::addConditionalTransition(19);
  StateMachine::addConditionalTransition(16);

  // Add state "blocked" with ID 12
  StateMachine::addStateDefinition("blocked", 12);

  // Transition from "blocked" to any
  StateMachine::addTransition("blocked", 0xffffffff);

  // Another state with ID 0x15 (21)
  StateMachine::addState(21);

  // Define "terminate" with ID 4 (overwrites? different ID)
  StateMachine::addStateDefinition("terminate", 4);

  // Transition from "terminate" to any
  StateMachine::addTransition("terminate", 0xffffffff);

  // State ID 2
  StateMachine::addState(2);

  // Register the complete behavior machine with a hash and label "NPCBackupSM"
  // Hash 0x53c8ca9d might be derived from the string "NPCBackupSM"
  StateMachine::registerBehavior(0x53c8ca9d, &behaviorFuncTable, "NPCBackupSM"); // 0x004adc90

  // Finalize the state machine (compile transitions, etc.)
  StateMachine::finalize(); // 0x004ada40

  return;
}