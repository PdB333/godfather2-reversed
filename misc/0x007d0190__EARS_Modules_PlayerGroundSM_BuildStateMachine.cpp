// Xbox PDB: EARS_Modules_PlayerGroundSM_BuildStateMachine
// FUNC_NAME: PlayerGroundSM::buildStateTable
void PlayerGroundSM::buildStateTable(void)
{
  undefined4 uVar1;
  
  uVar1 = FUN_009c8f80(); // Get some runtime ID or handle
  FUN_004ad9d0("playerGroundStateTable",uVar1); // Register state table name
  FUN_004adae0(&DAT_00d63420,0); // Set initial state (idle)
  FUN_004acf70(0x31); // Add state 0x31 (idle)
  FUN_004acc70(&DAT_00d64b74,4); // Add transition to state 4 (locomote)
  FUN_004adae0(&DAT_00d64b74,1); // Set state 1 (walk)
  FUN_004acf70(0x33); // Add state 0x33 (walk)
  FUN_004acff0(0x31); // Remove state 0x31 (idle) from current
  FUN_004acff0(0x34); // Remove state 0x34 (run)
  FUN_004acc70("faceToFace",0x1f); // Add transition to faceToFace state
  FUN_004acc70("disabled",0x1d); // Add transition to disabled state
  FUN_004acc70("idleTurn",0x14); // Add transition to idleTurn state
  FUN_004acc70("locomote",0x15); // Add transition to locomote state
  FUN_004ad070(0x35); // Add state 0x35 (idleTurn)
  FUN_004adae0("idleTurn",2); // Set state 2 (idleTurn)
  FUN_004acf70(0x36); // Add state 0x36 (idleTurn)
  FUN_004acff0(0x31); // Remove state 0x31
  FUN_004acff0(0x37); // Remove state 0x37
  FUN_004acc70("faceToFace",0x1f); // Add transition to faceToFace
  FUN_004acc70("disabled",0x1d); // Add transition to disabled
  FUN_004acc70("locomote",0x17); // Add transition to locomote
  FUN_004acc70("flickTurn",0x18); // Add transition to flickTurn
  FUN_004acc70(&DAT_00d64b74,0x16); // Add transition to state 0x16
  FUN_004ad070(0x38); // Add state 0x38 (flickTurn)
  FUN_004adae0("flickTurn",3); // Set state 3 (flickTurn)
  FUN_004acff0(0x31); // Remove state 0x31
  FUN_004acff0(0x39); // Remove state 0x39
  FUN_004acc70("faceToFace",0x1f); // Add transition to faceToFace
  FUN_004acc70("disabled",0x1d); // Add transition to disabled
  FUN_004acc70("locomote",0x19); // Add transition to locomote
  FUN_004acc70(&DAT_00d64b74,0x1a); // Add transition to state 0x1a
  FUN_004adae0("locomote",4); // Set state 4 (locomote)
  FUN_004acf70(0x3a); // Add state 0x3a (locomote)
  FUN_004acff0(0x31); // Remove state 0x31
  FUN_004acff0(0x3b); // Remove state 0x3b
  FUN_004acc70("faceToFace",0x1f); // Add transition to faceToFace
  FUN_004acc70("disabled",0x1d); // Add transition to disabled
  FUN_004acc70("locomote180Turn",0x1b); // Add transition to locomote180Turn
  FUN_004acc70(&DAT_00d64b74,0x13); // Add transition to state 0x13
  FUN_004ad070(0x42); // Add state 0x42 (locomote180Turn)
  FUN_004ad070(0x3c); // Add state 0x3c
  FUN_004adae0("locomote180Turn",5); // Set state 5 (locomote180Turn)
  FUN_004acf70(0x3d); // Add state 0x3d
  FUN_004acff0(0x31); // Remove state 0x31
  FUN_004acff0(0x3e); // Remove state 0x3e
  FUN_004acc70("faceToFace",0x1f); // Add transition to faceToFace
  FUN_004acc70("disabled",0x1d); // Add transition to disabled
  FUN_004acc70(&DAT_00d64b74,0x13); // Add transition to state 0x13
  FUN_004acc70("locomote",0x1c); // Add transition to locomote
  FUN_004ad070(0x3f); // Add state 0x3f
  FUN_004ad070(0x42); // Add state 0x42
  FUN_004adae0("faceToFace",6); // Set state 6 (faceToFace)
  FUN_004acf70(0x41); // Add state 0x41 (faceToFace)
  FUN_004acc70(&DAT_00d64b74,0x20); // Add transition to state 0x20
  FUN_004adae0("disabled",7); // Set state 7 (disabled)
  FUN_004acf70(0x40); // Add state 0x40 (disabled)
  FUN_004acc70(&DAT_00d64b74,0x1e); // Add transition to state 0x1e
  FUN_004adc90(0xf1a2c8fe,FUN_007d0090,"PlayerGroundSM"); // Register state machine with hash
  FUN_004ada40(); // Finalize state table
  return;
}