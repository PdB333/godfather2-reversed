// FUNC_NAME: PlayerSM::updateState
void __thiscall PlayerSM::updateState(int *this, undefined4 param_2, undefined4 param_3)
{
  uint *puVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  code *pcVar10;
  int iVar11;
  
  iVar8 = this[0x25]; // +0x94 - some state/flag
  cVar2 = FUN_0076ec60(); // likely isPlayerInVehicle or similar
  if (**(int **)(DAT_012233a0 + 4) == 0) {
    iVar11 = 0;
  }
  else {
    iVar11 = **(int **)(DAT_012233a0 + 4) + -0x1f30; // offset to some object
  }
  iVar7 = this[0x22]; // +0x88 - current state
  if (iVar7 == 3) {
LAB_00770437:
    if ((this[0x17] != 0) && (this[0x17] != 0x48)) { // +0x5C - some index
      if (this[0x17] == 0) {
        iVar8 = 0;
      }
      else {
        iVar8 = this[0x17] + -0x48;
      }
      FUN_0046fd90(iVar8,0); // likely playAnimation
    }
    if ((*(byte *)(this + 0x15) & 8) == 0) { // +0x54 - flags
      FUN_007f4490(1,0,DAT_00d5ef90); // likely setFlag
      *(byte *)(this + 0x15) = *(byte *)(this + 0x15) | 8;
    }
    uVar9 = 0x81cfd529; // animation hash
LAB_00770496:
    pcVar10 = *(code **)(*this + 0x2c); // vtable offset for playAnimation
  }
  else {
    if ((((*(uint *)(this[0x14] + 0x1f5c) >> 0xc & 1) != 0) && (this[0x19] != 0)) && // +0x64 - some index
       (this[0x19] != 0x48)) {
      if (this[0x19] == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = this[0x19] + -0x48;
      }
      if ((iVar5 == iVar11) && ((*(uint *)(this[0x14] + 0x1f54) >> 0x16 & 1) == 0))
      goto LAB_00770437;
    }
    if (iVar7 == 4) {
LAB_007703e0:
      FUN_0046ffe0(this + 0x1e,0); // +0x78 - some timer
      if (*(char *)(this[0x14] + 0x1b8c) == '\x01') { // +0x1b8c - flag
        puVar1 = (uint *)(this[0x14] + 0x1b94); // +0x1b94 - flags
        *puVar1 = *puVar1 | 8;
      }
      if ((*(byte *)(this + 0x15) & 8) == 0) { // +0x54 - flags
        FUN_007f4490(1,0,DAT_00d5ef90); // likely setFlag
        *(byte *)(this + 0x15) = *(byte *)(this + 0x15) | 8;
      }
      uVar9 = 0xc996f012; // animation hash
      goto LAB_00770496;
    }
    bVar3 = FUN_0084d420(iVar7); // likely getStateFlags
    if ((bVar3 & 8) != 0) goto LAB_007703e0;
    uVar6 = FUN_0084d420(this[0x22]); // +0x88 - current state
    if ((uVar6 & 0x40) != 0) goto LAB_0077049f;
    cVar4 = FUN_0084d420(this[0x22]); // +0x88 - current state
    if (cVar4 < '\\0') goto LAB_0077049f;
    if (((cVar2 == '\\0') || (this[0x19] == 0)) || (this[0x19] == 0x48)) { // +0x64 - some index
LAB_007703ce:
      FUN_0076e5c0(iVar8,cVar2); // likely updateMovement
      goto LAB_0077049f;
    }
    if (this[0x19] == 0) {
      iVar7 = 0;
    }
    else {
      iVar7 = this[0x19] + -0x48;
    }
    if (iVar7 != iVar11) goto LAB_007703ce;
    uVar6 = FUN_0084d420(this[0x22]); // +0x88 - current state
    if ((uVar6 & 1) == 0) goto LAB_007703ce;
    cVar4 = FUN_007fd640(); // likely isPlayerInCombat
    if ((cVar4 != '\\0') || (*(char *)(this[0x14] + 0x1ec5) == -1)) goto LAB_007703ce; // +0x1ec5 - some index
    cVar4 = FUN_00690150(0x66); // likely checkAbility
    if (cVar4 == '\\0') goto LAB_007703ce;
    iVar11 = *(int *)(this[0x14] + 0x1ecc); // +0x1ecc - some value
    cVar4 = *(char *)(this[0x14] + 0x1ec5); // +0x1ec5 - some index
    if (((cVar4 == -1) || (';' < cVar4)) || (4 < iVar11)) {
      FUN_0076e5c0(iVar8,cVar2); // likely updateMovement
      goto LAB_0077049f;
    }
    pcVar10 = *(code **)(*this + 0x2c); // vtable offset for playAnimation
    uVar9 = *(undefined4 *)(&DAT_00d6636c + (cVar4 * 0x19 + iVar11) * 4); // animation hash table lookup
  }
  (*pcVar10)(uVar9,1,1,0,0x3f800000,0x3f800000); // playAnimation(hash, loop, blend, ?, 1.0f, 1.0f)
LAB_0077049f:
  if (this[0x22] == 1) { // +0x88 - current state
    iVar8 = *this;
    uVar9 = thunk_FUN_004dafd0("trackToPositionAndDirectionStateTable"); // getStateTable
    (**(code **)(iVar8 + 0x20))(param_2,param_3,uVar9); // vtable offset for transitionToState
    FUN_00624ca0(1); // likely setFlag
  }
  *(uint *)(this[0x14] + 0x1f5c) = *(uint *)(this[0x14] + 0x1f5c) & 0xffffefff; // clear bit 12
  return;
}