// FUNC_NAME: Player::copyFromOtherPlayer
void __thiscall Player::copyFromOtherPlayer(int thisPlayer, int otherPlayer)
{
  int *piVar1;
  float fVar2;
  undefined4 uVar3;
  float fVar4;
  int iVar5;
  int local_c [2];
  undefined1 local_4;
  
  // Copy linked list node (likely a node in a list of players or objects)
  piVar1 = (int *)(thisPlayer + 0x43c);
  if (otherPlayer == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = otherPlayer + 0x48;
  }
  if (*piVar1 != iVar5) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1); // Remove from list
    }
    *piVar1 = iVar5;
    if (iVar5 != 0) {
      *(undefined4 *)(thisPlayer + 0x440) = *(undefined4 *)(iVar5 + 4);
      *(int **)(iVar5 + 4) = piVar1;
    }
  }
  // Copy various state fields from otherPlayer to thisPlayer
  *(undefined4 *)(thisPlayer + 0x7c) = *(undefined4 *)(otherPlayer + 0x5c); // +0x7c = some state
  *(undefined4 *)(thisPlayer + 0x78) = *(undefined4 *)(otherPlayer + 0x5c); // +0x78 = same state
  *(undefined4 *)(thisPlayer + 0x70) = *(undefined4 *)(otherPlayer + 0x70); // +0x70 = some value
  *(undefined4 *)(thisPlayer + 0x428) = *(undefined4 *)(otherPlayer + 0x78); // +0x428 = some value
  *(undefined4 *)(thisPlayer + 0x434) = *(undefined4 *)(otherPlayer + 0xac); // +0x434 = some value
  *(undefined4 *)(thisPlayer + 400) = *(undefined4 *)(otherPlayer + 0xa8); // +0x190 = some value
  *(undefined4 *)(thisPlayer + 0xb0) = *(undefined4 *)(otherPlayer + 0x7c); // +0xb0 = position/rotation
  *(undefined4 *)(thisPlayer + 0xb4) = *(undefined4 *)(otherPlayer + 0x80); // +0xb4 = position/rotation
  *(undefined4 *)(thisPlayer + 0xb8) = *(undefined4 *)(otherPlayer + 0x84); // +0xb8 = position/rotation
  *(undefined4 *)(thisPlayer + 0xbc) = *(undefined4 *)(otherPlayer + 0x88); // +0xbc = position/rotation
  fVar4 = DAT_00e44598; // Some global threshold
  if ((*(uint *)(thisPlayer + 0x170) >> 1 & 1) == 0) { // Check some flag
    fVar2 = *(float *)(otherPlayer + 0x58); // +0x58 = some float value
    *(float *)(thisPlayer + 0x164) = fVar2; // +0x164 = copy float
    if (fVar4 < fVar2) {
      *(uint *)(thisPlayer + 0x170) = *(uint *)(thisPlayer + 0x170) & 0xfffffdff; // Clear flag
      local_c[0] = DAT_0112feb0; // Some global
      local_c[1] = 0;
      local_4 = 0;
      FUN_00408a00(local_c,0); // Likely a function call with parameters
    }
  }
  *(undefined4 *)(thisPlayer + 0x18c) = *(undefined4 *)(otherPlayer + 0x94); // +0x18c = copy some value
  FUN_0083b6c0(-*(int *)(thisPlayer + 0x2d8)); // Release reference
  uVar3 = *(undefined4 *)(otherPlayer + 0x74); // +0x74 = some value
  *(undefined4 *)(thisPlayer + 0x2d8) = uVar3; // +0x2d8 = copy value
  FUN_0083b6c0(uVar3); // Add reference
  *(undefined4 *)(thisPlayer + 0x17c) = *(undefined4 *)(otherPlayer + 0x98); // +0x17c = copy quaternion/rotation
  *(undefined4 *)(thisPlayer + 0x180) = *(undefined4 *)(otherPlayer + 0x9c); // +0x180 = copy quaternion/rotation
  *(undefined4 *)(thisPlayer + 0x184) = *(undefined4 *)(otherPlayer + 0xa0); // +0x184 = copy quaternion/rotation
  *(undefined4 *)(thisPlayer + 0x188) = *(undefined4 *)(otherPlayer + 0xa4); // +0x188 = copy quaternion/rotation
  local_c[0] = *(int *)(otherPlayer + 0x68); // +0x68 = some pointer
  if (local_c[0] != 0) {
    local_c[1] = 0;
    local_4 = 0;
    FUN_00408a00(local_c,0); // Call with pointer
  }
  local_c[0] = DAT_0112fe98; // Some global
  local_c[1] = 0;
  local_4 = 0;
  FUN_00408a00(local_c,0); // Call with global
  return;
}