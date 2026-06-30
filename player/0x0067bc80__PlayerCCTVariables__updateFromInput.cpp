// FUNC_NAME: PlayerCCTVariables::updateFromInput
void PlayerCCTVariables::updateFromInput(void)
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  // Read left stick X axis (two samples for smoothing?)
  iVar1 = FUN_00676010(); // likely InputManager::getAxisValue or similar
  iVar2 = FUN_00676010();
  *(int *)(this + 0xf0) = *(int *)(this + 0xf0) + iVar1 + iVar2; // +0xF0: moveX (accumulated)
  
  // Read left stick Y axis
  iVar1 = FUN_00676010();
  iVar2 = FUN_00676010();
  *(int *)(this + 0xf4) = *(int *)(this + 0xf4) + iVar1 + iVar2; // +0xF4: moveY (accumulated)
  
  // Read right stick X axis
  uVar3 = FUN_00676010();
  *(undefined4 *)(this + 0xe0) = uVar3; // +0xE0: lookX
  
  // Read right stick Y axis
  uVar3 = FUN_00676010();
  *(undefined4 *)(this + 0xe8) = uVar3; // +0xE8: lookY
  
  // Read left trigger
  uVar3 = FUN_00676010();
  *(undefined4 *)(this + 0xe4) = uVar3; // +0xE4: leftTrigger
  
  // Read right trigger
  uVar3 = FUN_00676010();
  *(undefined4 *)(this + 0xec) = uVar3; // +0xEC: rightTrigger
  
  return;
}