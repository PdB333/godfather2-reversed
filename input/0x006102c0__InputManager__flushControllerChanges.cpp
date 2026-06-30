// FUNC_NAME: InputManager::flushControllerChanges
void InputManager::flushControllerChanges(void)
{
  int iVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  
  piVar2 = DAT_01205750; // InputManager singleton pointer
  uVar4 = 0;
  do {
    uVar3 = *(uint *)((int)&DAT_00f15988 + uVar4); // controllerMinSlot (0x00f15988, per-slot array)
    if (uVar3 <= *(uint *)((int)&DAT_012058d0 + uVar4)) { // controllerMaxSlot (0x012058d0)
      do {
        iVar1 = *(int *)(&DAT_011f39d8 + uVar3 * 4); // currentControllerState (0x011f39d8, per-slot)
        if (iVar1 != (&DAT_011f3dd8)[uVar3]) { // previousControllerState (0x011f3dd8)
          (&DAT_011f3dd8)[uVar3] = iVar1; // update previous state
          (**(code **)(*piVar2 + 0xe4))(piVar2,uVar3,iVar1); // vtable call: onControllerStateChanged(slot, newState)
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 <= *(uint *)((int)&DAT_012058d0 + uVar4));
    }
    *(undefined4 *)((int)&DAT_012058d0 + uVar4) = 0; // reset max slot to 0
    *(undefined4 *)((int)&DAT_00f15988 + uVar4) = 0xff; // reset min slot to 0xFF (invalid)
    uVar4 = uVar4 + 4;
  } while (uVar4 < 8); // 2 controller slots (each 4 bytes for min/max)
  return;
}