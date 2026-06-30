// FUNC_NAME: VehicleDamageComponent::updateDamageVisuals
void VehicleDamageComponent::updateDamageVisuals(int param_1, float param_2)
{
  int iVar1;
  int *unaff_EDI;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar7;
  double dVar6;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float in_XMM4_Da;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float local_130;
  float fStack_12c;
  float fStack_128;
  float fStack_124;
  float local_120;
  float fStack_11c;
  float fStack_118;
  float fStack_114;
  float local_110;
  float fStack_10c;
  float fStack_108;
  float fStack_104;
  float local_100;
  float fStack_fc;
  float fStack_f8;
  float fStack_f4;
  float local_f0;
  float fStack_ec;
  float fStack_e8;
  float fStack_e4;
  float local_e0;
  float fStack_dc;
  float fStack_d8;
  float fStack_d4;
  float local_c4;
  float local_c0;
  float fStack_bc;
  float fStack_b8;
  float local_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  float local_94;
  undefined1 local_90 [48];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  
  if (in_XMM4_Da < 0.0) {
    in_XMM4_Da = 0.0;
  }
  fVar4 = (float)unaff_EDI[0x24]; // +0x90: current position X
  fVar5 = (float)unaff_EDI[0x25]; // +0x94: current position Y
  fVar8 = (float)unaff_EDI[0x26]; // +0x98: current position Z
  fStack_d4 = (float)unaff_EDI[0x27]; // +0x9c: current position W
  fVar7 = (float)unaff_EDI[0x15]; // +0x54: previous position Y
  fStack_104 = (float)unaff_EDI[0x17]; // +0x5c: previous position W
  fVar2 = (float)unaff_EDI[0x25] + in_XMM4_Da;
  fVar14 = (float)((uint)in_XMM4_Da & DAT_00e44680) + (float)((uint)param_2 & DAT_00e44680);
  unaff_EDI[0x25] = (int)fVar2;
  fVar15 = DAT_00e2cbe0;
  local_c0 = (float)unaff_EDI[0x34] - (float)unaff_EDI[0x44]; // +0xd0 - +0x110: target - base position X
  fStack_bc = (float)unaff_EDI[0x35] - (float)unaff_EDI[0x45]; // Y
  fStack_b8 = (float)unaff_EDI[0x36] - (float)unaff_EDI[0x46]; // Z
  fStack_a4 = (float)unaff_EDI[0x37] - (float)unaff_EDI[0x47]; // W
  local_b0 = fVar4 - (float)unaff_EDI[0x34]; // current - target X
  fStack_ac = fVar5 - (float)unaff_EDI[0x35]; // Y
  fStack_a8 = fVar8 - (float)unaff_EDI[0x36]; // Z
  fVar9 = fStack_d4 - (float)unaff_EDI[0x37]; // W
  fVar16 = (float)unaff_EDI[0x24] - (float)unaff_EDI[0x44]; // current - base X
  fVar17 = (float)unaff_EDI[0x25] - (float)unaff_EDI[0x45]; // Y
  fVar18 = (float)unaff_EDI[0x26] - (float)unaff_EDI[0x46]; // Z
  local_94 = fStack_bc * fStack_bc + fStack_b8 * fStack_b8 + local_c0 * local_c0;
  fVar12 = fVar17 * fVar17 + fVar18 * fVar18 + fVar16 * fVar16;
  fVar10 = (((fVar12 + local_94) -
            (local_b0 * local_b0 + fStack_a8 * fStack_a8 + fStack_ac * fStack_ac)) / fVar12) *
           DAT_00e2cd54;
  fVar13 = 0.0;
  local_94 = local_94 - fVar10 * fVar10 * fVar12;
  if (local_94 <= 0.0) {
    local_94 = 0.0;
  }
  else {
    local_94 = SQRT(local_94);
  }
  fVar12 = fVar10 * fVar16 + (float)unaff_EDI[0x44];
  fVar16 = fVar10 * fVar17 + (float)unaff_EDI[0x45];
  fVar17 = fVar10 * fVar18 + (float)unaff_EDI[0x46];
  fVar18 = fStack_b8 * fStack_b8 + fStack_bc * fStack_bc + local_c0 * local_c0;
  if (DAT_00e2cbe0 < fVar18) {
    fVar13 = DAT_00e2b1a4 / SQRT(fVar18);
  }
  fVar19 = fVar4 - (float)unaff_EDI[0x44];
  fVar20 = fVar5 - (float)unaff_EDI[0x45];
  fVar21 = fVar8 - (float)unaff_EDI[0x46];
  fVar18 = fVar21 * fStack_b8 * fVar13 + fVar20 * fStack_bc * fVar13 + local_c0 * fVar13 * fVar19;
  fVar11 = fVar20 * fVar20 + fVar21 * fVar21 + fVar19 * fVar19;
  fVar3 = DAT_00e44564 - fVar18 / fVar11;
  fVar19 = fVar3 * fVar19 + local_c0 * fVar13;
  fVar20 = fVar3 * fVar20 + fStack_bc * fVar13;
  fVar21 = fVar3 * fVar21 + fStack_b8 * fVar13;
  fVar3 = fVar3 * (fStack_d4 - (float)unaff_EDI[0x47]) + fStack_a4;
  fVar13 = fVar19 * fVar19 + fVar3 * fVar3 + fVar21 * fVar21 + fVar20 * fVar20;
  if (fVar13 <= DAT_00e2cbe0) {
    fVar13 = 0.0;
  }
  else {
    fVar13 = DAT_00e2b1a4 / SQRT(fVar13);
  }
  unaff_EDI[0x34] = (int)(local_94 * fVar19 * fVar13 + fVar12);
  unaff_EDI[0x35] = (int)(local_94 * fVar20 * fVar13 + fVar16);
  unaff_EDI[0x36] = (int)(local_94 * fVar21 * fVar13 + fVar17);
  unaff_EDI[0x37] =
       (int)(local_94 * fVar3 * fVar13 +
            fVar10 * ((float)unaff_EDI[0x27] - (float)unaff_EDI[0x47]) + (float)unaff_EDI[0x47]);
  if ((float)((uint)(fVar18 * fVar18 - fVar11) & DAT_00e44680) < DAT_00e2e210) {
    unaff_EDI[0x34] = (int)fVar12;
    unaff_EDI[0x35] = (int)fVar16;
    unaff_EDI[0x36] = (int)(fVar17 + local_94);
  }
  fVar10 = DAT_00e3ac54;
  param_2 = param_2 + (float)unaff_EDI[0x15];
  unaff_EDI[0x15] = (int)param_2;
  if (fVar14 < fVar10) {
    fVar2 = (DAT_00e2b1a4 - fVar14 * DAT_00e448cc) * (param_2 - fVar2) + fVar2;
  }
  if (fVar2 < param_2) {
    unaff_EDI[0x15] = (int)fVar2;
  }
  fVar2 = (float)unaff_EDI[0x24];
  fVar10 = (float)unaff_EDI[0x25];
  fVar12 = (float)unaff_EDI[0x26];
  fVar13 = local_c0 * local_c0 + fStack_b8 * fStack_b8 + fStack_bc * fStack_bc;
  if (fVar13 <= fVar15) {
    fVar13 = 0.0;
  }
  else {
    fVar13 = DAT_00e2b1a4 / SQRT(fVar13);
  }
  fStack_bc = fStack_bc * fVar13;
  local_c0 = local_c0 * fVar13;
  fStack_b8 = fStack_b8 * fVar13;
  fVar13 = local_b0 * local_b0 + fStack_a8 * fStack_a8 + fStack_ac * fStack_ac;
  if (fVar13 <= fVar15) {
    fVar13 = 0.0;
  }
  else {
    fVar13 = DAT_00e2b1a4 / SQRT(fVar13);
  }
  fStack_ac = fStack_ac * fVar13;
  local_b0 = local_b0 * fVar13;
  fStack_a8 = fStack_a8 * fVar13;
  fVar4 = (float)unaff_EDI[0x14] - fVar4;
  fVar7 = fVar7 - fVar5;
  fVar8 = (float)unaff_EDI[0x16] - fVar8;
  fVar13 = fStack_104 - fStack_d4;
  fVar5 = fVar8 * fVar8 + fVar7 * fVar7 + fVar4 * fVar4;
  if (fVar5 <= fVar15) {
    fVar5 = 0.0;
  }
  else {
    fVar5 = DAT_00e2b1a4 / SQRT(fVar5);
  }
  local_e0 = (float)unaff_EDI[0x34] - (float)unaff_EDI[0x44];
  fStack_dc = (float)unaff_EDI[0x35] - (float)unaff_EDI[0x45];
  fStack_d8 = (float)unaff_EDI[0x36] - (float)unaff_EDI[0x46];
  fVar14 = fStack_d8 * fStack_d8 + fStack_dc * fStack_dc + local_e0 * local_e0;
  if (fVar14 <= fVar15) {
    fVar14 = 0.0;
  }
  else {
    fVar14 = DAT_00e2b1a4 / SQRT(fVar14);
  }
  local_e0 = local_e0 * fVar14;
  fStack_dc = fStack_dc * fVar14;
  fStack_d8 = fStack_d8 * fVar14;
  local_f0 = fVar2 - (float)unaff_EDI[0x34];
  fStack_ec = fVar10 - (float)unaff_EDI[0x35];
  fStack_e8 = fVar12 - (float)unaff_EDI[0x36];
  fVar14 = fStack_e8 * fStack_e8 + fStack_ec * fStack_ec + local_f0 * local_f0;
  if (fVar14 <= fVar15) {
    fVar14 = 0.0;
  }
  else {
    fVar14 = DAT_00e2b1a4 / SQRT(fVar14);
  }
  fStack_ec = fStack_ec * fVar14;
  fStack_e8 = fStack_e8 * fVar14;
  local_f0 = local_f0 * fVar14;
  local_110 = (float)unaff_EDI[0x14] - fVar2;
  fStack_10c = (float)unaff_EDI[0x15] - fVar10;
  fStack_108 = (float)unaff_EDI[0x16] - fVar12;
  fVar14 = fStack_108 * fStack_108 + fStack_10c * fStack_10c + local_110 * local_110;
  if (fVar14 <= fVar15) {
    fVar15 = 0.0;
  }
  else {
    fVar15 = DAT_00e2b1a4 / SQRT(fVar14);
  }
  fStack_108 = fStack_108 * fVar15;
  fStack_10c = fStack_10c * fVar15;
  local_110 = local_110 * fVar15;
  fVar15 = SQRT(fVar7 * fVar7 + fVar8 * fVar8 + fVar4 * fVar4);
  fStack_114 = fVar15 * fStack_104 + (float)unaff_EDI[0x27];
  unaff_EDI[0x14] = (int)(fVar15 * local_110 + fVar2);
  unaff_EDI[0x15] = (int)(fVar15 * fStack_10c + fVar10);
  unaff_EDI[0x16] = (int)(fVar15 * fStack_108 + fVar12);
  local_100 = fStack_bc * fStack_d8 - fStack_b8 * fStack_dc;
  fStack_fc = fStack_b8 * local_e0 - local_c0 * fStack_d8;
  fStack_f8 = local_c0 * fStack_dc - fStack_bc * local_e0;
  local_130 = fStack_ac * fStack_e8 - fStack_a8 * fStack_ec;
  fStack_12c = fStack_a8 * local_f0 - local_b0 * fStack_e8;
  fStack_128 = local_b0 * fStack_ec - fStack_ac * local_f0;
  local_120 = fStack_108 * fVar7 * fVar5 - fStack_10c * fVar8 * fVar5;
  fStack_11c = local_110 * fVar8 * fVar5 - fStack_108 * fVar4 * fVar5;
  fStack_118 = fStack_10c * fVar4 * fVar5 - local_110 * fVar7 * fVar5;
  fVar4 = fStack_fc * fStack_fc + fStack_f8 * fStack_f8 + local_100 * local_100;
  fStack_124 = fVar13;
  fStack_f4 = fVar9;
  fStack_e4 = fVar9;
  local_c4 = fStack_114;
  if (DAT_00e2b05c < fVar4) {
    fVar4 = SQRT(fVar4);
    dVar6 = (double)fVar4;
    FUN_00b9a9fa();
    fVar4 = (float)dVar6 / fVar4;
    local_100 = fVar4 * local_100;
    fStack_fc = fVar4 * fStack_fc;
    fStack_f8 = fVar4 * fStack_f8;
    fStack_f4 = fVar9;
    FUN_0058dfa0();
    FUN_0056cba0(&local_c0,unaff_EDI + 100,&local_100);
    FUN_0056cef0(&local_100,unaff_EDI + 0x38);
  }
  fVar4 = fStack_12c * fStack_12c + fStack_128 * fStack_128 + local_130 * local_130;
  if (DAT_00e2b05c < fVar4) {
    fVar4 = SQRT(fVar4);
    dVar6 = (double)fVar4;
    FUN_00b9a9fa();
    fVar4 = (float)dVar6 / fVar4;
    local_130 = fVar4 * local_130;
    fStack_12c = fVar4 * fStack_12c;
    fStack_128 = fVar4 * fStack_128;
    fStack_124 = fVar13;
    FUN_0058dfa0();
    FUN_0056cba0(&local_100,unaff_EDI + 0x60,&local_130);
    FUN_0056cef0(&local_130,unaff_EDI + 0x28);
  }
  fVar4 = fStack_11c * fStack_11c + fStack_118 * fStack_118 + local_120 * local_120;
  if (DAT_00e2b05c < fVar4) {
    fVar4 = SQRT(fVar4);
    dVar6 = (double)fVar4;
    FUN_00b9a9fa();
    fVar4 = (float)dVar6 / fVar4;
    local_120 = fVar4 * local_120;
    fStack_11c = fVar4 * fStack_11c;
    fStack_118 = fVar4 * fStack_118;
    fStack_114 = local_c4;
    FUN_0058dfa0();
    FUN_0056cba0(&local_130,unaff_EDI + 0x5c,&local_120);
    FUN_0056cef0(&local_120,unaff_EDI + 0x18);
    FUN_0056cba0(&local_130,unaff_EDI + 0x58,&local_120);
    FUN_0056cef0(&local_120,unaff_EDI + 8);
  }
  iVar1 = unaff_EDI[3] * 0x20 + 0x10 + *(int *)(param_1 + 0x38);
  FUN_00424470();
  FUN_00417560();
  FUN_0056d530(local_90,iVar1);
  *(undefined4 *)(iVar1 + 0x10) = local_60;
  *(undefined4 *)(iVar1 + 0x14) = local_5c;
  *(undefined4 *)(iVar1 + 0x18) = local_58;
  iVar1 = unaff_EDI[2] * 0x20 + 0x10 + *(int *)(param_1 + 0x38);
  FUN_00424470();
  FUN_00417560();
  FUN_0056d530(local_90,iVar1);
  *(undefined4 *)(iVar1 + 0x10) = local_60;
  *(undefined4 *)(iVar1 + 0x14) = local_5c;
  *(undefined4 *)(iVar1 + 0x18) = local_58;
  iVar1 = unaff_EDI[1] * 0x20 + 0x10 + *(int *)(param_1 + 0x38);
  FUN_00424470();
  FUN_00417560();
  FUN_0056d530(local_90,iVar1);
  *(undefined4 *)(iVar1 + 0x10) = local_60;
  *(undefined4 *)(iVar1 + 0x14) = local_5c;
  *(undefined4 *)(iVar1 + 0x18) = local_58;
  iVar1 = *unaff_EDI * 0x20 + 0x10 + *(int *)(param_1 + 0x38);
  FUN_00424470();
  FUN_00417560();
  FUN_0056d530(local_90,iVar1);
  *(undefined4 *)(iVar1 + 0x10) = local_60;
  *(undefined4 *)(iVar1 + 0x14) = local_5c;
  *(undefined4 *)(iVar1 + 0x18) = local_58;
  return;
}