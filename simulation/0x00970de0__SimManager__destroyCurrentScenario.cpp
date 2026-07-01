// FUNC_NAME: SimManager::destroyCurrentScenario
void __fastcall SimManager::destroyCurrentScenario(int thisPtr)

{
  int state;
  
  state = *(int *)(thisPtr + 0xdc); // +0xdc: current scenario state
  if (state != 9) {
    *(undefined4 *)(thisPtr + 0xc4) = 0; // +0xc4: scenario transition timer
    *(undefined4 *)(thisPtr + 0xd4) = 0; // +0xd4: scenario flags
    switch(state) {
    case 1:
    case 6:
      uVar2 = 9;
      break;
    default:
      uVar2 = 10;
    }
    *(undefined4 *)(thisPtr + 0xd8) = uVar2; // +0xd8: next scenario state
    if (state == 4) {
      FUN_005a04a0("HideReadyState",0,&DAT_00d8cdec,0); // generic hook/event system call
    }
    if (*(int *)(thisPtr + 0xdc) == 1) { // if still in scenario state 1
      FUN_0096adc0(); // some global cleanup function
    }
    state = thisPtr + 0x10;
    FUN_005c02f0(state,&LAB_00969090,1); // removes scenario type 0x909090 from list
    FUN_005c02f0(state,&LAB_00963ee0,1); // removes scenario type 0x63ee0 from list
    FUN_005c02f0(state,&LAB_0096fba0,1); // removes scenario type 0x6fba0 from list
    FUN_005c02f0(state,&LAB_0096ccb0,1); // removes scenario type 0x6ccb0 from list
    FUN_005c02f0(state,&LAB_0096ee00,1); // removes scenario type 0x6ee00 from list
    *(undefined4 *)(thisPtr + 0xdc) = 9; // set state to destroyed/cleaned
    FUN_00965720(); // post-cleanup function
  }
  FUN_005a04a0("Destroy",0,&DAT_00d8cdec,0); // signal destruction to event system
  FUN_005a04a0("ShowSetUp",0,&DAT_00d8cdec,0); // signal setup visibility to event system
  (**(code **)(*(int *)(thisPtr + 0x590) + 0x6c))(0); // call base destructor vtable
  return;
}