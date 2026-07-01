// FUNC_NAME: Player::updateCombatState
byte __thiscall Player::updateCombatState(int thisPtr, char param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  byte bVar5;
  
  bVar5 = 1;
  if ((*(int *)(thisPtr + 0x1b4) != 0) && (*(int *)(thisPtr + 0x1b4) != 0x48)) {
    iVar2 = *(int *)(thisPtr + 0x58);
    cVar1 = FUN_007f7c50(); // likely isPlayerInCutscene or similar
    if ((cVar1 == '\0') &&
       (((*(uint *)(iVar2 + 0x24a0) >> 5 & 1) == 0 && ((*(byte *)(iVar2 + 0x8e4) & 1) == 0)))) {
      *(uint *)(thisPtr + 0x1d0) = *(uint *)(thisPtr + 0x1d0) & 0xffffff7f; // clear bit 7 (combat flag)
    }
    else {
      *(uint *)(thisPtr + 0x1d0) = *(uint *)(thisPtr + 0x1d0) | 0x80; // set bit 7 (combat flag)
    }
    bVar5 = (byte)(*(uint *)(thisPtr + 0x1d0) >> 7) & 1;
    if (*(int *)(thisPtr + 0x1b4) == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(thisPtr + 0x1b4) + -0x48;
    }
    if (*(char *)(iVar2 + 0x1b8c) != '\0') {
      bVar5 = 1;
    }
  }
  if (param_2 != '\0') {
    piVar3 = (int *)FUN_007ab160(); // likely getInputManager or similar
    if (bVar5 != 0) {
      (*(code *)((undefined4 *)*piVar3)[1])(1); // enable combat input
      return bVar5;
    }
    (**(code **)*piVar3)(0x80); // disable combat input
    puVar4 = (undefined4 *)FUN_007ab160();
    (**(code **)*puVar4)(1); // enable normal input
  }
  return bVar5;
}