// FUNC_NAME: InputManager::readControllerState
void __thiscall InputManager::readControllerState(int this, undefined4 param_2)
{
  char cVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int local_40 [16]; // 8 pairs of (controllerId, value)
  
  FUN_0046c710(param_2); // likely some input initialization
  FUN_0043aff0(param_2,0x971a9098); // set up input context with magic value
  
  piVar3 = local_40;
  iVar4 = 7;
  do {
    *piVar3 = 0;
    piVar3[1] = 0;
    piVar3 = piVar3 + 2;
    iVar4 = iVar4 + -1;
  } while (-1 < iVar4);
  
  cVar1 = FUN_0043b120(); // check if input processing should continue
  while (cVar1 == '\0') {
    FUN_0043b210(); // process next input event
    uVar2 = FUN_0043ab70(); // get event type/controller index
    if (uVar2 < 0x10) {
      if ((uVar2 & 1) == 0) {
        iVar4 = FUN_0043b210(); // get event data
        local_40[(uVar2 >> 1) * 2] = *(int *)(iVar4 + 8); // store controller value
      }
      else if ((uVar2 & 1) == 1) {
        iVar4 = FUN_0043b210(); // get event data
        local_40[(uVar2 >> 1) * 2 + 1] = *(int *)(iVar4 + 8); // store controller value
      }
    }
    FUN_0043b1a0(); // advance to next event
    cVar1 = FUN_0043b120(); // check if more events
  }
  
  piVar3 = local_40;
  iVar4 = 8;
  do {
    if ((piVar3[1] != 0) && (uVar2 = *(uint *)(this + 0x94), uVar2 < 8)) {
      *(int *)(this + 0x54 + uVar2 * 8) = *piVar3; // +0x54: controller state array (8 slots, 8 bytes each)
      *(int *)(this + 0x58 + uVar2 * 8) = piVar3[1];
      *(int *)(this + 0x94) = *(int *)(this + 0x94) + 1; // +0x94: controller count
    }
    piVar3 = piVar3 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}