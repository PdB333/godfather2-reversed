// FUNC_NAME: Player::updateFactionReputation
uint __thiscall Player::updateFactionReputation(int thisPtr, int param_2)
{
  char cVar1;
  undefined4 in_EAX;
  int iVar2;
  uint uVar3;
  byte bVar4;
  undefined4 uVar5;
  undefined4 local_c;
  
  if ((*(byte *)(thisPtr + 0x8a) & 0x20) == 0) {
    in_EAX = FUN_006e6700(); // some initialization or check
  }
  bVar4 = ~(*(byte *)(thisPtr + 0x89) >> 4);
  if ((bVar4 & 1) == 0) {
    return CONCAT31((int3)((uint)in_EAX >> 8),bVar4) & 0xffffff01;
  }
  uVar3 = *(uint *)(param_2 + 0x24c4); // +0x24C4: some state or type
  if ((uVar3 == 0) || (uVar3 == 0x48)) goto LAB_006e7552;
  cVar1 = FUN_007167a0(); // likely isPlayerInSinglePlayer()
  if (cVar1 == '\0') {
    cVar1 = FUN_007174e0(); // likely isMultiplayer()
    local_c = 0;
    if (cVar1 != '\0') goto LAB_006e74dd;
  }
  else {
LAB_006e74dd:
    local_c = 1;
  }
  iVar2 = FUN_00471610(); // likely getCurrentTime() or frame counter
  cVar1 = FUN_00717b00(); // likely isPaused()
  uVar5 = _DAT_00d5780c; // global game time or delta
  if (*(int *)(param_2 + 0x21b8) != 0) { // +0x21B8: some component pointer
    uVar5 = *(undefined4 *)(*(int *)(param_2 + 0x21b8) + 0x5c); // +0x5C: time delta
  }
  uVar3 = FUN_006e64a0(iVar2 + 0x30,local_c,cVar1 == '\0',uVar5); // reputation update function
  if ((char)uVar3 == '\0') {
    return uVar3;
  }
LAB_006e7552:
  return CONCAT31((int3)(uVar3 >> 8),bVar4) & 0xffffff01;
}