// Xbox PDB: EARS_Modules_VaultSM_BuildStateMachine
// FUNC_NAME: VaultStateMachine::buildStateMachine
void __thiscall VaultStateMachine::buildStateMachine(void)
{
  // Get the state table identifier (likely a hash or pointer)
  uint32_t stateTableId = getVaultStateTable(); // FUN_009c8f80

  // Register the main vault state table by name
  registerStateTable("vaultStateTable", stateTableId); // FUN_004ad9d0

  // Add entry state: "uncrouch" with no transition target (-1 = exit state)
  addStateTransition("uncrouch", -1); // FUN_004adae0
  setStateTimeout(0x14); // 20 (ms?) // FUN_004acf70

  // Add a state from global string constant (DAT_00d63420) with parameter 10
  addState((const char*)&DAT_00d63420, 10); // FUN_004acc70
  addStateTransition((const char*)&DAT_00d63420, -1); // FUN_004adae0
  setStateTimeout(0x12); // 18 // FUN_004acf70

  // Track a sub‑state machine for position/direction
  trackSubStateMachine("trackToPositionAndDirectionStateTable", 0); // FUN_004acf10

  // Add the "vault" state (param 1)
  addState("vault", 1); // FUN_004acc70
  addStateTransition("vault", -1); // FUN_004adae0

  // Set the vault animation (hash 0x84d99455, flags: 1,1,1, speed 1.0)
  setAnimationHash(0x84d99455, 1, 1, 1, 1.0f); // FUN_004ace70

  // Additional motion timeouts
  setMotionTimeout(8); // FUN_004acf70
  setMotionTimeout2(8); // FUN_004acff0 (possibly different timeout slot)

  // Add another state from global string constant (DAT_00d63ba4) with parameter 7
  addState((const char*)&DAT_00d63ba4, 7); // FUN_004acc70
  addStateTransition((const char*)&DAT_00d63ba4, -1); // FUN_004adae0
  setStateTimeout(2); // FUN_004acf70

  // Set exit callback (event hash 0x414678c, handler at LAB_0080f360, state machine name "VaultSM")
  setStateMachineExitHandler(0x414678c, &LAB_0080f360, "VaultSM"); // FUN_004adc90

  // Finalize state machine building
  finalizeStateMachine(); // FUN_004ada40
}