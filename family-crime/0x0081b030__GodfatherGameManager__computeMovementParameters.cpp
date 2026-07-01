// FUNC_NAME: GodfatherGameManager::computeMovementParameters
void GodfatherGameManager::computeMovementParameters(int param1, int param2, char param3)
{
  byte bVar1;
  char cVar2;
  undefined8 *puVar3;
  ulonglong *puVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  float *pfVar8;
  int *piVar9;
  float10 fVar10;
  unkbyte10 Var11;
  undefined4 uVar12;
  float fVar13;
  undefined8 uVar14;
  float local_bc;
  byte local_b5;
  int local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  undefined4 local_a4;
  undefined8 local_9c;
  float local_94;
  ulonglong local_90;
  float local_88;
  undefined4 local_84;
  int local_7c;
  undefined1 auStack_78 [4];
  undefined1 auStack_74 [4];
  float local_70;
  float local_6c;
  float local_68;
  undefined1 auStack_54 [4];
  undefined8 local_50;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_24;
  undefined4 local_14;
  
  local_14 = _DAT_00d5780c;
  local_b4 = *(int *)(param_2 + 0xf0); // +0xF0: some pointer in output struct
  local_44 = 0;
  local_34 = 0;
  local_24 = 0;
  *(int *)(param_2 + 8) = param_1; // +0x08: store input param1
  
  if (param_3 == '\0') {
    // init from identity matrix
    puVar5 = (undefined4 *)FUN_00471610(); // getIdentityMatrix()
    puVar3 = &local_50;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *(undefined4 *)puVar3 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar3 = (undefined8 *)((int)puVar3 + 4);
    }
    FUN_007f7ed0(param_2 + 0xc); // clear position?
  }
  else {
    // compute position from index
    local_bc = *(float *)(&DAT_00002494 + param_1); // get some offset based on param1
    puVar3 = (undefined8 *)FUN_00425060(&local_90, local_bc); // sin/cos
    local_9c = *puVar3;
    local_94 = *(float *)(puVar3 + 1);
    puVar4 = (ulonglong *)FUN_00424fb0(&local_b0, local_bc); // cos/sin
    local_90 = *puVar4;
    local_88 = (float)puVar4[1];
    FUN_0056b8a0(local_9c._4_4_, (float)local_9c, local_94, &local_50); // build matrix from orientation
    *(ulonglong *)(param_2 + 0xc) = local_90; // +0x0C: position x
    *(float *)(param_2 + 0x14) = local_88; // +0x14: position z
  }
  
  local_bc = DAT_0122339c;
  local_7c = FUN_004262f0(0); // get some object
  local_7c = local_7c + 0x40;
  puVar3 = (undefined8 *)FUN_00424fb0(&local_b0, 0);
  local_9c = *puVar3;
  local_94 = *(float *)(puVar3 + 1);
  local_90 = 0;
  local_88 = (float)DAT_00e44634;
  
  if ((*(byte *)(param_1 + 0x249f) & 1) == 0) {
    local_90 = *(ulonglong *)(DAT_01129944 + 0x108);
    local_88 = *(float *)(DAT_01129944 + 0x110);
  }
  
  local_84 = _DAT_00d5780c;
  FUN_0056b420(local_7c, &local_90, &local_70); // transform point
  local_b0 = local_70 - (float)local_9c;
  local_ac = local_6c - local_9c._4_4_;
  local_a8 = local_68 - local_94;
  local_a4 = 0;
  fVar10 = (float10)FUN_0056afa0(&local_b0, &local_b0); // vector length
  local_9c = CONCAT44(local_ac, local_b0);
  local_94 = local_a8;
  fVar13 = local_a8;
  uVar14 = local_9c;
  if (fVar10 <= (float10)0) {
    fVar13 = DAT_00d731c0;
    uVar14 = DAT_00d731b8;
  }
  
  *(undefined8 *)(param_2 + 0x18) = uVar14; // +0x18: forward direction XZ
  *(undefined8 *)(param_2 + 0x24) = local_40; // +0x24: up direction?
  *(float *)(param_2 + 0x20) = fVar13; // +0x20: forward direction Y?
  *(undefined8 *)(param_2 + 0x30) = local_50; // +0x30: orientation matrix?
  *(undefined4 *)(param_2 + 0x38) = local_48;
  *(undefined4 *)(param_2 + 0x2c) = local_38;
  FUN_007f7ed0(param_2 + 0x3c); // clear something
  iVar6 = FUN_00471610(); // get identity matrix
  *(undefined8 *)(param_2 + 0x48) = *(undefined8 *)(iVar6 + 0x20);
  *(undefined4 *)(param_2 + 0x50) = *(undefined4 *)(iVar6 + 0x28);
  
  fVar13 = DAT_00e44564;
  if (((*(uint *)(param_1 + 0x8e0) >> 0x19 & 1) != 0) && ((*(uint *)(param_1 + 0x8e4) >> 8 & 1) == 0)) {
    // flip if flipped
    *(float *)(param_2 + 0x48) = DAT_00e44564 - *(float *)(param_2 + 0x48);
    *(float *)(param_2 + 0x4c) = fVar13 - *(float *)(param_2 + 0x4c);
    *(float *)(param_2 + 0x50) = fVar13 - *(float *)(param_2 + 0x50);
  }
  
  uVar7 = *(uint *)(param_1 + 0x8e8) >> 2;
  local_b5 = (byte)uVar7 & 1;
  if ((uVar7 & 1) == 0) {
    *(undefined4 *)(param_2 + 0x5c) = 0;
    *(undefined4 *)(param_2 + 0x58) = 0;
    *(undefined4 *)(param_2 + 0x54) = 0;
  }
  else {
    local_b0 = *(float *)(param_1 + 0x8f0) - *(float *)(param_2 + 0xc);
    local_ac = *(float *)(param_1 + 0x8f4) - *(float *)(param_2 + 0x10);
    local_a8 = *(float *)(param_1 + 0x8f8) - *(float *)(param_2 + 0x14);
    local_a4 = 0;
    FUN_0056afa0(&local_b0, &local_b0);
    fVar13 = *(float *)(local_b4 + 0x1d8);
    *(float *)(param_2 + 0x54) = local_b0 * fVar13; // +0x54: target offset?
    *(float *)(param_2 + 0x58) = local_ac * fVar13;
    *(float *)(param_2 + 0x5c) = local_a8 * fVar13;
  }
  
  Var11 = FUN_0079eb90(0, 0); // random
  fVar10 = (float10)fsin(Var11);
  local_90 = (ulonglong)(uint)(float)fVar10;
  fVar10 = (float10)fcos(Var11);
  local_88 = (float)fVar10;
  FUN_006cb9d0((float *)(param_2 + 0x60), &local_90, &local_50); // build rotation matrix
  *(undefined4 *)(param_2 + 0x6c) = 0; // +0x6C: flags
  
  if (local_b5 == 0) {
    local_bc = *(float *)(local_b4 + 0x54);
  }
  else {
    local_bc = *(float *)(local_b4 + 0x60);
  }
  
  fVar10 = (float10)FUN_0079eb40(0, 0); // random
  if ((((float10)local_bc < fVar10) && ((*(byte *)(param_1 + 0x8e3) & 1) == 0)) && (param_3 != '\0')) {
    *(uint *)(param_2 + 0x6c) = *(uint *)(param_2 + 0x6c) | 1;
    if (*(float *)(param_2 + 100) * *(float *)(param_2 + 0x1c) +
        *(float *)(param_2 + 0x60) * *(float *)(param_2 + 0x18) +
        *(float *)(param_2 + 0x68) * *(float *)(param_2 + 0x20) < 0.0) {
      *(uint *)(param_2 + 0x6c) = *(uint *)(param_2 + 0x6c) | 2;
    }
  }
  
  bVar1 = *(byte *)(param_2 + 0x6c) & 1;
  if (local_b5 == 0) {
    if (bVar1 == 0) {
      uVar12 = *(undefined4 *)(local_b4 + 0x50);
    }
    else {
      uVar12 = *(undefined4 *)(local_b4 + 0x58);
    }
  }
  else if (bVar1 == 0) {
    uVar12 = *(undefined4 *)(local_b4 + 0x5c);
  }
  else {
    uVar12 = *(undefined4 *)(local_b4 + 100);
  }
  *(undefined4 *)(param_2 + 0x74) = uVar12; // +0x74: animation ID?
  
  if ((((((*(uint *)(param_1 + 0x8e0) >> 10 & 1) != 0) ||
        ((*(uint *)(param_1 + 0x8e4) >> 5 & 1) != 0)) ||
       ((*(uint *)(param_1 + 0x8e4) >> 7 & 1) != 0)) &&
      ((iVar6 = FUN_00800a90(), iVar6 != 0 || (iVar6 = FUN_00800b10(), iVar6 != 0)))) ||
     (((*(int *)(param_1 + 0x30c0) != 0 && (*(int *)(param_1 + 0x30c0) != 0x48)) ||
      ((*(byte *)(param_1 + 0x8e3) & 1) != 0)))) {
    *(uint *)(param_2 + 0x6c) = *(uint *)(param_2 + 0x6c) | 4;
    if (((((byte)*(undefined4 *)(param_2 + 0x70) & 1) == 1) && (*(int *)(param_2 + 0x7c) != 0)) &&
       (*(int *)(param_2 + 0x7c) != 0x48)) {
      if (*(int *)(param_2 + 0x7c) == 0) {
        piVar9 = (int *)0x0;
      }
      else {
        piVar9 = (int *)(*(int *)(param_2 + 0x7c) + -0x48);
      }
      local_bc = 0.0;
      cVar2 = (**(code **)(*piVar9 + 0x10))(0x369ac561, &local_bc);
      if (((cVar2 == '\0') || (local_bc == 0.0)) ||
         ((cVar2 = FUN_008184d0(auStack_54, auStack_78, auStack_74), cVar2 == '\0' || (local_7c != 1))
         )) {
        *(uint *)(param_2 + 0x6c) = *(uint *)(param_2 + 0x6c) | 0x80;
      }
      else {
        *(uint *)(param_2 + 0x6c) = *(uint *)(param_2 + 0x6c) | 0x18;
      }
    }
    if ((*(byte *)(param_1 + 0x8e3) & 1) != 0) {
      *(uint *)(param_2 + 0x6c) = *(uint *)(param_2 + 0x6c) | 0x12;
      if ((*(uint *)(param_1 + 0x8e0) >> 0x19 & 1) == 0) {
        *(uint *)(param_2 + 0x6c) = *(uint *)(param_2 + 0x6c) | 8;
      }
    }
  }
  
  iVar6 = local_b4;
  if ((*(byte *)(param_2 + 0x6c) & 4) == 0) {
    local_bc = *(float *)(local_b4 + 0x84);
  }
  else {
    local_bc = *(float *)(local_b4 + 0x80);
  }
  
  if ((_DAT_00d577a0 <= local_bc) && (pfVar8 = (float *)FUN_008d6ae0(), local_bc <= *pfVar8)) {
    *(uint *)(param_2 + 0x6c) = *(uint *)(param_2 + 0x6c) | 0x40;
  }
  
  if ((*(uint *)(param_2 + 0x70) & 6) != 0) {
    *(uint *)(param_2 + 0x6c) = *(uint *)(param_2 + 0x6c) | 2;
  }
  
  if (param_3 == '\0') {
    *(undefined1 *)(param_2 + 0x78) = 0;
  }
  else {
    FUN_00818940(*(undefined4 *)(iVar6 + 0x68));
  }
  
  fVar13 = *(float *)(iVar6 + 0x78);
  if (fVar13 < 0.0) {
    *(undefined4 *)(param_2 + 0xb8) = DAT_00d5f6f0;
    return;
  }
  if (0.0 <= *(float *)(param_2 + 4)) {
    fVar13 = fVar13 * *(float *)(param_2 + 4);
  }
  *(float *)(param_2 + 0xb8) = fVar13 * fVar13;
  return;
}