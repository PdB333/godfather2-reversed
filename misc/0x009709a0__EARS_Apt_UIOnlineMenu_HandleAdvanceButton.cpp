// Xbox PDB: EARS_Apt_UIOnlineMenu_HandleAdvanceButton
// FUNC_NAME: MultiplayerScenarioManager::startQuickMatchSearch
void __fastcall MultiplayerScenarioManager::startQuickMatchSearch(int *this)
{
  int *piVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  bool bVar7;
  
  iVar2 = this[0x37]; // +0xDC - current state
  if (iVar2 != 8) { // STATE_SEARCHING
    this[0x31] = 0; // +0xC4 - some timer/counter
    this[0x35] = 0; // +0xD4 - some flag
    switch(iVar2) {
    case 1: // STATE_IDLE
    case 6: // STATE_WAITING_FOR_PLAYERS
      iVar5 = 9; // STATE_SEARCHING
      break;
    default:
      iVar5 = 10; // STATE_ERROR
    }
    this[0x36] = iVar5; // +0xD8 - next state
    if (iVar2 == 4) { // STATE_LOADING
      FUN_005a04a0("HideReadyState",0,&DAT_00d8cdec,0); // hide ready state UI
    }
    if (this[0x37] == 1) { // STATE_IDLE
      FUN_0096adc0(); // reset matchmaking
    }
    piVar1 = this + 4; // +0x10 - some object pointer
    FUN_005c02f0(piVar1,&LAB_00969090,1); // register callback
    FUN_005c02f0(piVar1,&LAB_00963ee0,1); // register callback
    FUN_005c02f0(piVar1,&LAB_0096fba0,1); // register callback
    FUN_005c02f0(piVar1,&LAB_0096ccb0,1); // register callback
    FUN_005c02f0(piVar1,&LAB_0096ee00,1); // register callback
    this[0x37] = 8; // STATE_SEARCHING
    FUN_00965720(); // start search timer
  }
  if (((uint)this[0x1bd] >> 0xc & 1) != 0) { // +0x6F4 - flags bit 12
    return; // already searching
  }
  FUN_00964070(); // update matchmaking UI
  bVar7 = DAT_00e574a9 == '\0'; // some global flag
  this[0x6d] = 1; // +0x1B4 - some flag
  if (bVar7) {
    FUN_00567c60(); // start quick match (offline?)
  }
  else {
    if (DAT_01223484 == 0) { // global pointer
      return;
    }
    if (DAT_0112b9b4 == 0) { // global pointer
      return;
    }
    if (*(int *)(DAT_0112b9b4 + 0x34) == -1) { // +0x34 - some index
      return;
    }
    iVar2 = *(int *)(*(int *)(DAT_0112b9b4 + 0x28) + *(int *)(DAT_0112b9b4 + 0x34) * 4); // get some data
    uVar6 = 8; // default flags
    if (iVar2 != 0) {
      uVar3 = *(uint *)(iVar2 + 0x2c); // +0x2C - flags
      if ((uVar3 & 4) != 0) {
        uVar6 = 0x48; // add more flags
      }
      if ((uVar3 & 8) != 0) {
        uVar6 = uVar6 | 0x10;
      }
      if ((uVar3 & 0x10) != 0) {
        uVar6 = uVar6 | 0x20;
      }
    }
    cVar4 = FUN_008a3140(this[0x6a],uVar6,1,(char)this[0x7d],1,(int)this + 0x1f5); // start matchmaking
    if (cVar4 == '\0') {
      return; // failed to start
    }
  }
  this[0x1bd] = this[0x1bd] | 0x1000; // set bit 12
  (**(code **)(*this + 0xc))(); // virtual function call (e.g. onSearchStarted)
  FUN_00983120("$mp_quickmatch_searching",0,0); // show searching text
  return;
}