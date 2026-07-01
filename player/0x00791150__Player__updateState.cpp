// FUNC_NAME: Player::updateState
void __fastcall Player::updateState(int thisPtr)
{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  // Check if current state is 0 or 0x48 (72) - likely idle or specific state
  if ((*(int *)(thisPtr + 0x9c) != 0) && (*(int *)(thisPtr + 0x9c) != 0x48)) {
    return;
  }
  // Check if bit flags 0x60000 are set (some blocking state)
  if ((*(uint *)(thisPtr + 0x5c) & 0x60000) != 0) {
    return;
  }
  // Check if there's a valid player camera/controller reference
  if ((int *)**(int **)(DAT_012233a0 + 4) != (int *)0x0) {
    // Call some camera/controller function (vtable +0xc)
    (**(code **)(*(int *)**(int **)(DAT_012233a0 + 4) + 0xc))();
    iVar1 = FUN_00471610(); // Get player position or camera position
    // Calculate distance from player to something (likely camera or target)
    fVar2 = *(float *)(thisPtr + 0x50) - *(float *)(iVar1 + 0x30);
    fVar3 = *(float *)(thisPtr + 0x54) - *(float *)(iVar1 + 0x34);
    fVar4 = *(float *)(thisPtr + 0x58) - *(float *)(iVar1 + 0x38);
    fVar2 = fVar4 * fVar4 + fVar3 * fVar3 + fVar2 * fVar2; // squared distance
    fVar3 = *(float *)(DAT_0112a678 + 100) * *(float *)(DAT_0112a678 + 100); // some squared threshold
    if (fVar2 < fVar3 * DAT_00e445a4) { // within extended range
      if (fVar2 <= fVar3) { // within close range
        *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x10000; // set bit 16 (in range flag)
      }
      goto LAB_007911fe;
    }
  }
  *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) & 0xfffeffff; // clear bit 16 (out of range)
LAB_007911fe:
  if ((*(byte *)(thisPtr + 0x5e) & 1) == 0) { // check some flag
    FUN_00792200(thisPtr); // handle non-cover state
    return;
  }
  FUN_00792cb0(thisPtr, 0 < *(int *)(thisPtr + 0x74)); // handle cover state with parameter
  return;
}