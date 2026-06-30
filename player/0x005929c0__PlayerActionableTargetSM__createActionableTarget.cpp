// FUNC_NAME: PlayerActionableTargetSM::createActionableTarget
int PlayerActionableTargetSM::createActionableTarget(void)
{
  float fVar1;
  int *this;
  int iVar2;
  int iVar3;
  float10 fVar4;
  undefined4 uVar5;
  undefined4 in_stack_00000010;
  uint in_stack_00000018;
  uint local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined1 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined1 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined1 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  float local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  float local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  float local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  float local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  
  uVar5 = 0;
  iVar2 = this[1]; // +0x4: some pointer member
  local_a4 = 0;
  local_a0 = 0;
  local_9c = 0;
  local_98 = 0;
  local_94 = 0;
  local_cc = 0;
  local_c8 = 0;
  local_c4 = 0;
  local_c0 = 0;
  local_bc = 0;
  local_b8 = 0;
  local_b4 = 0;
  local_b0 = 0;
  local_ac = 0;
  local_a8 = 0;
  // Check some version/type field at +0x4 of the pointed object
  if ((*(uint *)(iVar2 + 4) & 0xff) < 10) {
    iVar2 = *(int *)(iVar2 + 8); // +0x8
  }
  else {
    iVar2 = *(int *)(iVar2 + 0x18); // +0x18
  }
  FUN_00593770(in_stack_00000010,iVar2 != 0,*(undefined4 *)(*this + 0x10)); // +0x10 of main object
  // Initialize float arrays with a constant (likely 0.0f or 1.0f)
  local_84 = DAT_00e2b1a4;
  local_74 = DAT_00e2b1a4;
  local_64 = DAT_00e2b1a4;
  local_54 = DAT_00e2b1a4;
  local_44 = DAT_00e2b1a4;
  local_34 = DAT_00e2b1a4;
  local_24 = DAT_00e2b1a4;
  local_14 = DAT_00e2b1a4;
  local_d0 = in_stack_00000018 >> 5 & 1; // Extract bit 5 from flags
  local_90 = uVar5;
  local_8c = uVar5;
  local_88 = uVar5;
  local_80 = uVar5;
  local_7c = uVar5;
  local_78 = uVar5;
  local_70 = uVar5;
  local_6c = uVar5;
  local_68 = uVar5;
  local_60 = uVar5;
  local_5c = uVar5;
  local_58 = uVar5;
  local_50 = uVar5;
  local_4c = uVar5;
  local_48 = uVar5;
  local_40 = uVar5;
  local_3c = uVar5;
  local_38 = uVar5;
  local_30 = uVar5;
  local_2c = uVar5;
  local_28 = uVar5;
  local_20 = uVar5;
  local_1c = uVar5;
  local_18 = uVar5;
  FUN_00593210(&local_90,0); // Initialize some structure
  // Check bit 0xD of flags at +0x10
  if ((*(uint *)(*this + 0x10) >> 0xd & 1) == 0) {
    iVar2 = this[1]; // +0x4
    if ((*(uint *)(iVar2 + 4) & 0xff) < 10) {
      iVar2 = *(int *)(iVar2 + 0x10); // +0x10
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x24); // +0x24
    }
    if (-1 < iVar2) {
      fVar4 = (float10)FUN_00593910(in_stack_00000010);
      FUN_00593910((float)fVar4);
      if (((in_stack_00000018 >> 5 & 1) != 0) &&
         (iVar2 = FUN_005934a0(this,&local_90), iVar2 == 0)) {
        return 0;
      }
      iVar2 = FUN_005934f0(&local_50,&local_a4);
      if (iVar2 == 0) {
        return 0;
      }
      iVar2 = FUN_005934f0(&local_70,&local_cc);
      if (iVar2 == 0) {
        return 0;
      }
    }
  }
  iVar2 = FUN_00593cb0(*this,this[4],&local_b8,in_stack_00000018,&local_90);
  if (iVar2 == 0) {
    return 0;
  }
  if ((*(uint *)(*this + 0x10) >> 0xd & 1) == 0) {
    iVar3 = this[1]; // +0x4
    if ((*(uint *)(iVar3 + 4) & 0xff) < 10) {
      iVar3 = *(int *)(iVar3 + 0x10); // +0x10
    }
    else {
      iVar3 = *(int *)(iVar3 + 0x24); // +0x24
    }
    if (-1 < iVar3) {
      FUN_00586fa0(iVar2 + 0x10,&local_30,local_d0);
      *(undefined1 *)(iVar2 + 0x30) = 2; // Set type to 2
      if ((*this != 0) && (fVar1 = *(float *)(*this + 0x104), fVar1 != DAT_00e2b1a4)) {
        *(float *)(iVar2 + 0x20) = fVar1 * *(float *)(iVar2 + 0x20);
        *(float *)(iVar2 + 0x24) = *(float *)(iVar2 + 0x24) * fVar1;
        *(float *)(iVar2 + 0x28) = *(float *)(iVar2 + 0x28) * fVar1;
      }
    }
  }
  return iVar2;
}