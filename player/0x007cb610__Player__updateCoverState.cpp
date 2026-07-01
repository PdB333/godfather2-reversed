// FUNC_NAME: Player::updateCoverState
void __fastcall Player::updateCoverState(int this)
{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 local_18;
  float fStack_14;
  undefined4 local_10;
  undefined1 local_c [4];
  float local_8;
  
  // Check if bit 0x800000 (bit 23) is set in flags at +0x1d0
  if (((*(uint *)(this + 0x1d0) >> 0x17 & 1) != 0) && (cVar1 = FUN_007fd640(), cVar1 == '\0')) {
    iVar2 = FUN_00471610(); // Get some global time/position data
    local_10 = *(undefined4 *)(iVar2 + 0x38);
    fStack_14 = (float)((ulonglong)*(undefined8 *)(iVar2 + 0x30) >> 0x20);
    fStack_14 = fStack_14 + DAT_00d5ef70; // Add some offset
    local_18 = (undefined4)*(undefined8 *)(iVar2 + 0x30);
    if (*(int *)(this + 0x1b4) == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(this + 0x1b4) + -0x48; // Offset to some sub-object
    }
    cVar1 = FUN_009a75e0(local_c, iVar2, &local_18); // Check cover validity
    if ((cVar1 != '\0') && ((double)(fStack_14 - local_8) < _DAT_00d6eb88)) {
      if (*(int *)(this + 0x1b4) == 0) {
        piVar3 = (int *)0x0;
      }
      else {
        piVar3 = (int *)(*(int *)(this + 0x1b4) + -0x48);
      }
      (**(code **)(*piVar3 + 0x1c))(local_c); // Call virtual function at vtable+0x1c
    }
    // Clear bit 0x800000 (bit 23) in flags at +0x1d0
    *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) & 0xff7fffff;
  }
  return;
}