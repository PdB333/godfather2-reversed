// FUNC_NAME: Entity::isAliveOrActive
uint __fastcall Entity::isAliveOrActive(int this)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  // +0x5c: pointer to some state/component (e.g., health component or state machine)
  if ((*(int *)(this + 0x5c) != 0) && (*(int *)(this + 0x5c) != 0x48)) {
    if (*(int *)(this + 0x5c) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(this + 0x5c) + -0x48;
    }
    uVar2 = *(uint *)(iVar1 + 0x11c) >> 2;
    uVar3 = uVar2 & 0xffffff01;
    if ((uVar2 & 1) != 0) goto LAB_00775944;
  }
  uVar3 = *(uint *)(this + 0x5c);
  if ((uVar3 != 0) && (uVar3 = uVar3 - 0x48, uVar3 != 0)) {
    if (*(int *)(this + 0x5c) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(this + 0x5c) + -0x48;
    }
    bVar4 = (*(byte *)(iVar1 + 0x11c) & 0x79) != 0;
    uVar3 = CONCAT31((int3)((uint)iVar1 >> 8),bVar4);
    if (bVar4) {
LAB_00775944:
      return uVar3 & 0xffffff00;
    }
  }
  return CONCAT31((int3)(uVar3 >> 8),1);
}