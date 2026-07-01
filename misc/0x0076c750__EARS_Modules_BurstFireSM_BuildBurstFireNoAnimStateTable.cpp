// Xbox PDB: EARS_Modules_BurstFireSM_BuildBurstFireNoAnimStateTable
// FUNC_NAME: BurstFireSM::initializeStateMachine
void BurstFireSM::initializeStateMachine(void)
{
  undefined4 uVar1;
  
  uVar1 = FUN_009c8f80(); // likely returns some ID or pointer
  FUN_004ad9d0("BurstFireNoAnimST",uVar1); // register state "BurstFireNoAnimST"
  FUN_004adae0("burstNoAnimInit",0xffffffff); // set initial state to "burstNoAnimInit"
  FUN_004acf70(0x23); // add transition (0x23 = 35, likely a state ID)
  FUN_004acc70("burstNoAnimDoneShotBlocked",0x14); // add state "burstNoAnimDoneShotBlocked" with timeout 0x14 (20)
  FUN_004acc70("useGunNoAnim",0x16); // add state "useGunNoAnim" with timeout 0x16 (22)
  FUN_004adae0("useGunNoAnim",0xffffffff); // set another initial state? or override
  FUN_004acf70(0x26); // add transition (0x26 = 38)
  FUN_004acf70(0x27); // add transition (0x27 = 39)
  FUN_004acf70(0x2b); // add transition (0x2b = 43)
  FUN_004acc70("burstNoAnimDone",0x15); // add state "burstNoAnimDone" with timeout 0x15 (21)
  FUN_004acc70("useGunNoAnim",0x16); // add state "useGunNoAnim" again
  FUN_004acc70("burstNoAnimDoneShotBlocked",0x14); // add state again
  FUN_004adae0("burstNoAnimDoneShotBlocked",0xffffffff); // set initial state
  FUN_004acf70(0x29); // add transition (0x29 = 41)
  FUN_004acf70(0x2a); // add transition (0x2a = 42)
  FUN_004acc70("burstNoAnimDone",4); // add state with timeout 4
  FUN_004adae0("burstNoAnimDone",0xffffffff); // set initial state
  FUN_004acf70(2); // add transition (2)
  FUN_004adc90(0x211bc9c1,&LAB_0076c1d0,"BurstFireSM"); // register state machine with ID 0x211bc9c1, entry point at 0x76c1d0, name "BurstFireSM"
  FUN_004ada40(); // finalize/initialize state machine
  return;
}