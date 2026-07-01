// FUNC_NAME: InputManager::updateControllerSlots
byte __thiscall InputManager::updateControllerSlots(int this, undefined4 param_2)
{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  
  uVar3 = 0;
  bVar2 = 0;
  if (*(int *)(this + 8) != 0) {
    do {
      // Call each controller's update function via vtable at offset 0x1c
      // param_1+4 points to array of controller objects (0x8 bytes each)
      bVar1 = (**(code **)(**(int **)(*(int *)(this + 4) + uVar3 * 8) + 0x1c))(param_2);
      uVar3 = uVar3 + 1;
      bVar2 = bVar2 | bVar1;
    } while (uVar3 < *(uint *)(this + 8));
  }
  return bVar2;
}