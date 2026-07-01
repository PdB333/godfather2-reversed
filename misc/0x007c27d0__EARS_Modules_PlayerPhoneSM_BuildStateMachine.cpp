// Xbox PDB: EARS_Modules_PlayerPhoneSM_BuildStateMachine
// FUNC_NAME: PlayerPhoneSM::buildStateTable
void PlayerPhoneSM::buildStateTable(void)
{
  // Get the state machine manager instance
  StateMachineManager* stateMachineMgr = StateMachineManager::getInstance();
  
  // Register the player phone state table with the manager
  StateMachineManager::registerStateTable("playerPhoneStateTable", stateMachineMgr);
  
  // Set the initial state to -1 (invalid/not started)
  StateMachineManager::setState("playerPhoneStateTable", 0xffffffff);
  
  // Create state 0x31 (49) - "start" state
  StateMachineManager::createState(0x31);
  StateMachineManager::addTransition("start", 4); // Transition to state 4 on "start"
  
  // Create state 0x32 (50) - "holsterWeapon" state
  StateMachineManager::createState(0x32);
  StateMachineManager::addTransition("start", 0xffffffff); // Transition to invalid on "start"
  
  // Create state 0x33 (51) - "holsterWeapon" and "orientToPhone" state
  StateMachineManager::createState(0x33);
  StateMachineManager::addTransition("holsterWeapon", 0x13); // Transition to state 19 on "holsterWeapon"
  StateMachineManager::addTransition("orientToPhone", 4); // Transition to state 4 on "orientToPhone"
  
  // Create state 0x34 (52) - "holsterWeapon" state
  StateMachineManager::createState(0x34);
  StateMachineManager::addTransition("holsterWeapon", 0xffffffff); // Transition to invalid on "holsterWeapon"
  
  // Create state 0x35 (53) - playerConcealItemStateTable
  StateMachineManager::createState(0x35);
  StateMachineManager::setStateTable("playerConcealItemStateTable", 1); // Set to state table 1
  StateMachineManager::addTransition("start", 1); // Transition to state 1 on "start"
  
  // Create state 0x36 (54) - "orientToPhone" state
  StateMachineManager::createState(0x36);
  StateMachineManager::addTransition("orientToPhone", 0xffffffff); // Transition to invalid on "orientToPhone"
  
  // Create state 0x37 (55) - trackToPositionAndDirectionStateTable
  StateMachineManager::createState(0x37);
  StateMachineManager::setStateTable("trackToPositionAndDirectionStateTable", 0); // Set to state table 0
  
  // Create state 0x38 (56) - "trackToPositionAndDirection" state
  StateMachineManager::createState(0x38);
  StateMachineManager::addTransition("trackToPositionAndDirection", 1); // Transition to state 1 on "trackToPositionAndDirection"
  
  // Create state 0x39 (57) - "hangup" state
  StateMachineManager::createState(0x39);
  StateMachineManager::addTransition("hangup", 0x14); // Transition to state 20 on "hangup"
  
  // Create state 0x3a (58) - "hangup" state
  StateMachineManager::createState(0x3a);
  StateMachineManager::addTransition("hangup", 0xffffffff); // Transition to invalid on "hangup"
  
  // Create state 0x3b (59) - "drawWeapon" state
  StateMachineManager::createState(0x3b);
  StateMachineManager::addTransition("drawWeapon", 7); // Transition to state 7 on "drawWeapon"
  
  // Create state 0x3c (60) - "drawWeapon" and "orientToPhone" state
  StateMachineManager::createState(0x3c);
  StateMachineManager::addTransition("drawWeapon", 0xffffffff); // Transition to invalid on "drawWeapon"
  StateMachineManager::addTransition("drawWeapon", 0x15); // Transition to state 21 on "drawWeapon"
  StateMachineManager::addTransition("orientToPhone", 4); // Transition to state 4 on "orientToPhone"
  
  // Create state 2 - playerRevealItemStateTable
  StateMachineManager::createState(2);
  StateMachineManager::setStateTable("playerRevealItemStateTable", 1); // Set to state table 1
  StateMachineManager::addTransition("orientToPhone", 1); // Transition to state 1 on "orientToPhone"
  StateMachineManager::addTransition("orientToPhone", 0xffffffff); // Transition to invalid on "orientToPhone"
  
  // Register the state machine with a unique ID and callback
  StateMachineManager::registerStateMachine(0xf4895c47, FUN_007c2780, "PlayerPhoneSM");
  
  // Finalize the state table
  StateMachineManager::finalizeStateTable();
}