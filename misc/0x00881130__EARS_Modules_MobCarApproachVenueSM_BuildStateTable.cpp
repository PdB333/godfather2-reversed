// Xbox PDB: EARS_Modules_MobCarApproachVenueSM_BuildStateTable
// FUNC_NAME: MobCarApproachVenueSM::registerStates
void MobCarApproachVenueSM::registerStates(void)
{
  undefined4 uVar1;
  
  uVar1 = FUN_009c8f80(); // GetStateMachineID or similar
  FUN_004ad9d0("MobCarRootST",uVar1); // Register root state
  FUN_004adae0(&DAT_00d63420,0xffffffff); // Set default transition
  FUN_004acf70(0x12); // Add state 0x12 (18)
  FUN_004acf70(0xc); // Add state 0x0C (12)
  FUN_004acc70("normalVehicleFollowGraph",0xc); // Set state name
  FUN_004acc70("followGraph",4); // Set state name
  FUN_004adae0("normalVehicleFollowGraph",0xffffffff); // Set transition
  FUN_004acff0(10); // Add transition 0x0A (10)
  FUN_004acff0(0xc); // Add transition 0x0C (12)
  FUN_004acc70("letOccupantsOut",10); // Set transition name
  FUN_004acc70("letOccupantsOut",0xf); // Set transition name
  FUN_004acc70("letOccupantsOut",0xe); // Set transition name
  FUN_004acc70("letOccupantsOut",0x12); // Set transition name
  FUN_004acc70("followGraph",0xd); // Set state name
  FUN_004adae0("followGraph",0xffffffff); // Set transition
  FUN_004acff0(0xd); // Add transition 0x0D (13)
  FUN_004acff0(10); // Add transition 0x0A (10)
  FUN_004acff0(0xe); // Add transition 0x0E (14)
  FUN_004acc70("letOccupantsOut",10); // Set transition name
  FUN_004acc70("letOccupantsOut",0x14); // Set transition name
  FUN_004acc70("letOccupantsOut",0xf); // Set transition name
  FUN_004acc70("letOccupantsOut",0xe); // Set transition name
  FUN_004acc70("letOccupantsOut",0xb); // Set transition name
  FUN_004acc70("letOccupantsOut",0x11); // Set transition name
  FUN_004acc70("letOccupantsOut",0x12); // Set transition name
  FUN_004adae0("letOccupantsOut",0xffffffff); // Set transition
  FUN_004acf70(0x10); // Add state 0x10 (16)
  FUN_004acf70(0x11); // Add state 0x11 (17)
  FUN_004acff0(0x11); // Add transition 0x11 (17)
  FUN_004acff0(0xe); // Add transition 0x0E (14)
  FUN_004acc70("occupantsExit",10); // Set transition name
  FUN_004acc70("occupantsExit",0x10); // Set transition name
  FUN_004adae0("occupantsExit",0xffffffff); // Set transition
  FUN_004acf70(0xf); // Add state 0x0F (15)
  FUN_004acff0(10); // Add transition 0x0A (10)
  FUN_004acc70("waitForOccupantsToExit",10); // Set transition name
  FUN_004adae0("waitForOccupantsToExit",0xffffffff); // Set transition
  FUN_004acff0(10); // Add transition 0x0A (10)
  FUN_004acc70(&DAT_00d63afc,0x13); // Set transition name
  FUN_004adae0(&DAT_00d63afc,0xffffffff); // Set transition
  FUN_004acf70(0xb); // Add state 0x0B (11)
  FUN_004acf70(2); // Add state 0x02 (2)
  FUN_004adc90(0xbddc09cd,&LAB_008810c0,"MobCarApproachVenueSM"); // Register state machine
  FUN_004ada40(); // Finalize registration
  return;
}