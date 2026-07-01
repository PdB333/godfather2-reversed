// Xbox PDB: EARS_Modules_PlayerLowerBodySM_BuildStateMachine
// FUNC_NAME: PlayerSM::initializeStateTables
void PlayerSM::initializeStateTables(void)
{
  int iVar1;
  
  // Check if state tables already initialized
  iVar1 = FUN_00621530(thunk_FUN_004dafd0("playerLowerBodyStateTable"));
  if (iVar1 == 0) {
    // Create the main player lower body state table
    thunk_FUN_004dafd0("playerLowerBodyStateTable");
    FUN_004ad9d0("playerLowerBodyStateTable", FUN_009c8f80());
    
    // Ground movement state table
    FUN_004adae0("groundMovement", 0xffffffff); // -1 = default parent
    FUN_004ad0f0(5, 1, 1); // 5 states, 1 initial, 1 final
    FUN_004acf70(0x26); // state ID 0x26
    FUN_004acf10("playerGroundStateTable", 1); // 1 = active
    FUN_004acff0(0x35); // state ID 0x35
    FUN_004acff0(0x41); // state ID 0x41
    FUN_004acff0(0x42); // state ID 0x42
    FUN_004acff0(0x43); // state ID 0x43
    FUN_004acff0(0x44); // state ID 0x44
    FUN_004acff0(0x45); // state ID 0x45
    FUN_004acc70("arrested", 0x2a); // transition to arrested state
    FUN_004acd20(&DAT_00d63370, 6, 1, 1); // 6 transitions, 1 initial, 1 final
    FUN_004acc70(&DAT_00d63370, 0xc); // transition to state 0xc
    FUN_004acc70("wounded", 0x1d); // transition to wounded state
    FUN_004acc70("mp_garroted", 0x31); // transition to garroted state
    FUN_004acd20("recover", 0xe, 2, 1); // recover state, 2 transitions
    FUN_004acc70("freeAim", 0x18); // transition to free aim
    FUN_004acc70("revive", 0x1c); // transition to revive
    FUN_004acc70("block", 0x15); // transition to block
    FUN_004acc70("grapple", 0x16); // transition to grapple
    FUN_004acc70("grappleAttempt", 0x17); // transition to grapple attempt
    FUN_004acc70("ladder", 0x24); // transition to ladder
    FUN_004acc70("wallCover", 0x1a); // transition to wall cover
    FUN_004acc70("pickplant", 0x22); // transition to pick plant
    FUN_004acc70(&PTR_LAB_00d6f210, 0x14); // transition to some state
    FUN_004acc70("vault", 0x21); // transition to vault
    FUN_004acc70("vehicle", 0x13); // transition to vehicle (enter)
    FUN_004acc70("vehicle", 0x2b); // transition to vehicle (exit?)
    FUN_004acc70("vehicleHijack", 0x2c); // transition to vehicle hijack
    FUN_004acc70("saveGame", 0x1e); // transition to save game
    FUN_004acc70("phone", 0x1f); // transition to phone
    FUN_004acc70("GenericCSA", 0x30); // transition to generic CSA
    
    // Strafe movement state table
    FUN_004adae0("freeAim", 0xffffffff); // parent = default
    FUN_004acf70(0x26); // state ID 0x26
    FUN_004acf70(0x31); // state ID 0x31
    FUN_004acf10("playerStrafeMovementStateTable", 1);
    FUN_004acff0(0x35);
    FUN_004acff0(0x41);
    FUN_004acff0(0x42);
    FUN_004acff0(0x43);
    FUN_004acff0(0x44);
    FUN_004acff0(0x45);
    FUN_004acd20(&DAT_00d63370, 6, 1, 1);
    FUN_004acc70("mp_garroted", 0x31);
    FUN_004acc70(&DAT_00d63370, 0xc);
    FUN_004acc70("wounded", 0x1d);
    FUN_004acd20("recover", 0xe, 2, 1);
    FUN_004acc70("revive", 0x1c);
    FUN_004acc70("grapple", 0x16);
    FUN_004acc70("grappleAttempt", 0x17);
    FUN_004acc70("wallCover", 0x1a);
    FUN_004acc70("block", 0x15);
    FUN_004acc70("vault", 0x21);
    FUN_004acc70("vehicle", 0x13);
    FUN_004acc70("vehicle", 0x2b);
    FUN_004acc70("vehicleHijack", 0x2c);
    FUN_004acc70("groundMovement", 0x19);
    FUN_004acc70("pickplant", 0x22);
    FUN_004acc70("ladder", 0x24);
    FUN_004acc70("saveGame", 0x1e);
    FUN_004acc70("phone", 0x1f);
    FUN_004acc70("GenericCSA", 0x30);
    FUN_004ad070(0x32); // add state 0x32
    FUN_004adae0("wallCover", 0xffffffff);
    
    // Wall cover state table
    FUN_004acf10("playerWallCoverStateTable", 1);
    FUN_004acff0(0x35);
    FUN_004acff0(0x41);
    FUN_004acff0(0x42);
    FUN_004acff0(0x43);
    FUN_004acff0(0x44);
    FUN_004acff0(0x45);
    FUN_004acc70("groundMovement", 1);
    FUN_004acc70("groundMovement", 0x2e);
    FUN_004acc70("vault", 0x21);
    FUN_004acd20(&DAT_00d63370, 6, 1, 1);
    FUN_004acc70(&DAT_00d63370, 0xc);
    FUN_004acc70("wounded", 0x1d);
    FUN_004acd20("recover", 0xe, 2, 1);
    FUN_004adae0("vehicle", 0xffffffff);
    
    // Vehicle state table
    FUN_004acf10("playerVehicleStateTable", 1);
    FUN_004acc70(&DAT_00e41d10, 0xc);
    FUN_004acc70("groundMovement", 1);
    FUN_004adae0("vehicleHijack", 0xffffffff);
    
    // Vehicle hijack state table
    FUN_004acf10("playerVehicleHijackStateTable", 1);
    FUN_004acf70(0x31);
    FUN_004acf70(0x3c);
    FUN_004acd20(&DAT_00d63370, 6, 1, 1);
    FUN_004acc70(&DAT_00e41d10, 0xc);
    FUN_004acc70("groundMovement", 1);
    FUN_004acc70("groundMovement", 0x2d);
    FUN_004ad070(0x3d);
    FUN_004ad070(0x32);
    FUN_004adae0(&PTR_LAB_00d6f210, 0xffffffff);
    FUN_004acf70(0x33);
    
    // Hand-to-hand combat state table
    FUN_004acf10("playerH2HStateTable", 1);
    FUN_004acff0(8);
    FUN_004acc70("block", 0x15);
    FUN_004acc70("grapple", 0x32);
    FUN_004acc70("grappleAttempt", 0x33);
    FUN_004acd20(&DAT_00d63370, 6, 1, 1);
    FUN_004acc70(&DAT_00d63370, 0xc);
    FUN_004acd20("recover", 0xe, 2, 1);
    FUN_004acc70("groundMovement", 1);
    FUN_004ad070(0x34);
    FUN_004adae0("grapple", 0xffffffff);
    
    // Grapple state table
    FUN_004acf10("playerGrappleStateTable", 1);
    FUN_004acff0(8);
    FUN_004acff0(0x37);
    FUN_004acff0(0x3a);
    FUN_004acd20(&DAT_00d63370, 6, 1, 1);
    FUN_004acc70("groundMovement", 1);
    FUN_004adae0("grappleAttempt", 0xffffffff);
    FUN_004acf70(0x36);
    FUN_004acff0(8);
    FUN_004acc70("groundMovement", 0x34);
    FUN_004adae0(&DAT_00d63370, 0xffffffff);
    FUN_004ad0f0(4, 1, 1);
    FUN_004ad170(3, 1, 1);
    
    // Pain state table
    FUN_004acf10("PlayerPainStateTable", 1);
    FUN_004acc70(&DAT_00e41d10, 0x23);
    FUN_004acc70("AfterPain", 1);
    FUN_004adae0("AfterPain", 0xffffffff);
    FUN_004acc70("recover", 0x20);
    FUN_004acc70("wounded", 0x1d);
    FUN_004acc70(&DAT_00e41d10, 0xc);
    FUN_004adae0("wounded", 0xffffffff);
    
    // Wounded state machine
    FUN_004acf10("PlayerWoundedSM", 1);
    FUN_004acc70("recover", 1);
    FUN_004adae0("recover", 0xffffffff);
    
    // Recover state table
    FUN_004acf10("PlayerRecoverStateTable", 1);
    FUN_004acd20(&DAT_00d63370, 6, 1, 1);
    FUN_004acc70("groundMovement", 1);
    FUN_004adae0(&DAT_00e41d10, 0xffffffff);
    
    // Death state machine
    FUN_004acf10("playerDeathSM", 0); // 0 = not active initially
    FUN_004adae0("mp_garroted", 0xffffffff);
    FUN_004acf70(0x3f);
    
    // Grab reaction state table
    FUN_004acf10("grabReactStateTable", 0);
    FUN_004acc70(&DAT_00e41d10, 1);
    FUN_004ad070(0x40);
    FUN_004adae0("block", 0xffffffff);
    
    // Block state machine
    FUN_004acf10("playerBlockSM", 1);
    FUN_004acd20(&DAT_00d63370, 6, 1, 1);
    FUN_004acd20("recover", 0xe, 2, 1);
    FUN_004acff0(8);
    FUN_004acc70("groundMovement", 1);
    FUN_004acc70(&PTR_LAB_00d6f210, 0x14);
    FUN_004adae0("revive", 0xffffffff);
    
    // Revive state table
    FUN_004acf10("playerReviveStateTable", 1);
    FUN_004acc70(&DAT_00d63370, 0xd);
    FUN_004acc70("groundMovement", 1);
    FUN_004adae0("saveGame", 0xffffffff);
    FUN_004acf70(0x38);
    FUN_004acc70("groundMovement", 0x28);
    FUN_004ad070(0x39);
    FUN_004adae0("phone", 0xffffffff);
    
    // Phone state table
    FUN_004acf10("playerPhoneStateTable", 1);
    FUN_004acc70("groundMovement", 1);
    FUN_004adae0("pickplant", 0xffffffff);
    FUN_004acc70("carbomb", 0x2f);
    FUN_004acc70("plant", 4);
    FUN_004adae0("carbomb", 0xffffffff);
    
    // Car bomb state table
    FUN_004acf10("playerCarBombTable", 1);
    FUN_004acc70("groundMovement", 1);
    FUN_004adae0("plant", 0xffffffff);
    
    // Plant state table
    FUN_004acf10("playerPlantStateTable", 1);
    FUN_004acc70("groundMovement", 1);
    FUN_004adae0("ladder", 0xffffffff);
    
    // Ladder state table
    FUN_004acf10("playerLadderStateTable", 1);
    FUN_004acc70(&DAT_00e41d10, 0x25);
    FUN_004acc70(&DAT_00d63370, 0x26);
    FUN_004acc70(&DAT_00d63370, 0x27);
    FUN_004acc70("groundMovement", 1);
    FUN_004adae0("vault", 0xffffffff);
    
    // Vault state table
    FUN_004acf10("playerVaultStateTable", 1);
    FUN_004acc70("groundMovement", 1);
    FUN_004adae0("arrested", 0xffffffff);
    FUN_004ace70(0xe17f8711, 1, 1, 0, 0x3f800000); // some special transition
    FUN_004acf70(0x3b);
    FUN_004acc70("groundMovement", 0x29);
    FUN_004adae0("GenericCSA", 0xffffffff);
    
    // Generic CSA state table
    FUN_004acf10("playerGenericCSAStateTable", 1);
    FUN_004acc70(&DAT_00d63370, 0xc);
    FUN_004acc70("mp_garroted", 0x31);
    FUN_004acc70("groundMovement", 1);
    
    // Register the main state machine
    FUN_004adc90(0x14c85830, &LAB_007d6880, "PlayerLowerBodySM");
    FUN_004ada40();
  }
  return;
}