// FUNC_NAME: PlayerReputationTracker::getReputationForCrime
void __thiscall PlayerReputationTracker::getReputationForCrime(undefined8 *this, undefined8 *outReputation)
{
  undefined4 uVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  int *piVar5;
  undefined8 *local_4;
  
  if (*(char *)((int)this + 700) != '\0') {
    local_4 = this;
    iVar4 = FUN_00471610(); // likely getGameManager or getPlayer
    *outReputation = *(undefined8 *)(iVar4 + 0x10);
    *(undefined4 *)(outReputation + 1) = *(undefined4 *)(iVar4 + 0x18);
    return;
  }
  if (*(int *)(this + 0x1d) == 0) {
    piVar5 = (int *)0x0;
  }
  else {
    piVar5 = (int *)(*(int *)(this + 0x1d) + -0x48);
  }
  iVar4 = -0x3b89163b;
  local_4 = (undefined8 *)0x0;
  cVar3 = (**(code **)(*piVar5 + 0x10))(0xc476e9c5,&local_4);
  if ((cVar3 != '\0') && (iVar4 != 0)) {
    uVar1 = *(undefined4 *)(iVar4 + 0x44);
    uVar2 = *(undefined4 *)(iVar4 + 0x48);
    *(undefined4 *)local_4 = *(undefined4 *)(iVar4 + 0x40);
    *(undefined4 *)((int)local_4 + 4) = uVar1;
    *(undefined4 *)(local_4 + 1) = uVar2;
    return;
  }
  *local_4 = DAT_00d5ee68;
  *(undefined4 *)(local_4 + 1) = DAT_00d5ee70;
  return;
}