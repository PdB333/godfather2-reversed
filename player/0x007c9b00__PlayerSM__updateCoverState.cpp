// FUNC_NAME: PlayerSM::updateCoverState
void __fastcall PlayerSM::updateCoverState(int this)
{
  bool bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = FUN_007a5f40(); // likely getGameMode() or similar
  if ((iVar2 == 2) &&
     (((iVar2 = *(int *)(this + 0x58), (*(uint *)(iVar2 + 0x249c) >> 0x17 & 1) != 0 ||
       ((*(uint *)(iVar2 + 0x8e0) >> 9 & 1) != 0)) || ((*(uint *)(iVar2 + 0x8e0) >> 9 & 1) != 0))))
  {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  uVar3 = *(uint *)(this + 0x128) >> 0xd;
  if (((uVar3 & 1) == 0) && (bVar1)) {
    if ((*(uint *)(*(int *)(this + 0x58) + 0x8e0) >> 0x1a & 1) != 0) goto LAB_007c9ba6;
    *(uint *)(this + 0x128) = *(uint *)(this + 0x128) | 0x2000; // set bit 13 (cover flag)
  }
  else {
    if (((uVar3 & 1) == 0) ||
       ((bVar1 || ((*(uint *)(*(int *)(this + 0x58) + 0x8e0) >> 0x1a & 1) != 0))))
    goto LAB_007c9ba6;
    *(uint *)(this + 0x128) = *(uint *)(this + 0x128) & 0xffffdfff; // clear bit 13
  }
  FUN_007c9860(_DAT_00d6e910,2); // likely setCoverState or similar
LAB_007c9ba6:
  if (((*(int *)(this + 0x58) != 0) && (iVar2 = FUN_0043b870(DAT_01130950), iVar2 != 0)) &&
     ((*(uint *)(iVar2 + 0x4c) >> 1 & 1) != 0)) {
    return;
  }
  if ((*(byte *)(*(int *)(this + 0x58) + 0x249f) & 1) == 0) {
    if ((*(uint *)(this + 0x128) >> 0xe & 1) == 0) {
      return;
    }
    *(uint *)(this + 0x128) = *(uint *)(this + 0x128) & 0xffffbfff; // clear bit 14
    (**(code **)(**(int **)(this + 0x58) + 0x304))(); // call vtable function at offset 0x304 (likely exitCover)
  }
  else {
    if ((*(uint *)(this + 0x128) >> 0xe & 1) != 0) {
      return;
    }
    *(uint *)(this + 0x128) = *(uint *)(this + 0x128) | 0x4000; // set bit 14
    (**(code **)(**(int **)(this + 0x58) + 0x308))(); // call vtable function at offset 0x308 (likely enterCover)
  }
  FUN_007c9860(_DAT_00d6e910,0); // likely setCoverState or similar
  return;
}