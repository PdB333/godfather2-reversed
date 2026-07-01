// Xbox PDB: EARS_Modules_NPCDeathSM_BuildStateTable
// FUNC_NAME: NPCDeathSM::buildStateMachine
void NPCDeathSM::buildStateMachine(void)
{
  // Get the state machine manager instance
  undefined4 uVar1 = FUN_009c8f80(); // likely getStateMachineManager()
  
  // Create the state machine with name "NPCDeathST"
  FUN_004ad9d0("NPCDeathST", uVar1); // createStateMachine
  
  // Set initial state to "wounded" with no parent
  FUN_004adae0(&DAT_00d63420, 0xffffffff); // setInitialState
  
  // Add transitions from "wounded" state
  FUN_004acc70("wounded", 0x13); // addTransition (0x13 = enterWounded)
  FUN_004acc70("playDeathAnim", 4); // addTransition (4 = deathAnimComplete)
  
  // Remove transition from "wounded"
  FUN_004adae0("wounded", 0xffffffff); // removeTransition
  
  // Add states with their IDs
  FUN_004acf70(0x2c); // addState (44 = STATE_WOUNDED)
  FUN_004acf70(0x24); // addState (36 = STATE_DEATH_ANIM)
  FUN_004acf70(8);    // addState (8 = STATE_RECOVER)
  FUN_004acf70(0x2a); // addState (42 = STATE_SPAWN_CORPSE)
  
  // Add exit states
  FUN_004acff0(8);    // addExitState (8 = STATE_RECOVER)
  FUN_004acff0(0x26); // addExitState (38 = STATE_TERMINATE)
  
  // Add transitions for "playDeathAnim" state
  FUN_004acc70("recover", 0x15); // addTransition (0x15 = recoverFromDeath)
  FUN_004acc70("playDeathAnim", 0x14); // addTransition (0x14 = deathAnimFinished)
  
  // Set state actions
  FUN_004ad070(0x27); // setStateAction (39 = STATE_DEATH_ANIM_ENTER)
  FUN_004ad070(0x2b); // setStateAction (43 = STATE_SPAWN_CORPSE_ENTER)
  
  // Remove transition from "recover"
  FUN_004adae0("recover", 0xffffffff); // removeTransition
  
  // Add more states
  FUN_004acf70(0x28); // addState (40 = STATE_DEATH_ANIM_EXIT)
  FUN_004acf70(0x29); // addState (41 = STATE_SPAWN_CORPSE_EXIT)
  
  // Add transition for "terminate" state
  FUN_004acc70("terminate", 7); // addTransition (7 = terminateDeath)
  
  // Remove transition from "playDeathAnim"
  FUN_004adae0("playDeathAnim", 0xffffffff); // removeTransition
  
  // Add more states
  FUN_004acf70(0x25); // addState (37 = STATE_DEATH_ANIM_LOOP)
  FUN_004acf70(0x23); // addState (35 = STATE_WOUNDED_LOOP)
  
  // Add transitions for "spawnCorpse" state
  FUN_004acc70("spawnCorpse", 0x12); // addTransition (0x12 = corpseSpawned)
  FUN_004acc70("spawnCorpse", 0x16); // addTransition (0x16 = corpseSpawnFailed)
  
  // Remove transition from "spawnCorpse"
  FUN_004adae0("spawnCorpse", 0xffffffff); // removeTransition
  
  // Add more states
  FUN_004acf70(0x13); // addState (19 = STATE_CORPSE_SPAWNED)
  FUN_004acff0(0x14); // addExitState (20 = STATE_CORPSE_SPAWN_FAILED)
  
  // Remove transition from "terminate"
  FUN_004adae0("terminate", 0xffffffff); // removeTransition
  
  // Add final state
  FUN_004acf70(2); // addState (2 = STATE_TERMINATED)
  
  // Register the state machine with a callback
  FUN_004adc90(0xbf9dbad, &LAB_0076e070, "NPCDeathSM"); // registerStateMachine
  
  // Finalize state machine creation
  FUN_004ada40(); // finalizeStateMachine
  
  return;
}