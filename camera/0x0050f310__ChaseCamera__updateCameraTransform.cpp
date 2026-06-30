// FUNC_NAME: ChaseCamera::updateCameraTransform
void __thiscall ChaseCamera::updateCameraTransform(int this, int cameraTransform)
{
  float *pfVar1;
  int iVar2;
  void *_Dst;
  int *piVar3;
  int unaff_FS_OFFSET;
  float fVar4;
  float fVar5;
  float local_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  undefined4 local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  float local_30;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  
  // Check if camera is active (bit flags at +0x10c)
  if ((*(byte *)(*(int *)(this + 0x24) + 0x10c) & 0x18) != 0) {
    iVar2 = **(int **)(unaff_FS_OFFSET + 0x2c);
    *(int *)(this + 0x70) = cameraTransform;
    // Update camera transform matrix
    FUN_004eb6a0(*(int *)(this + 0x10) + 0x80 + *(int *)(iVar2 + 8),
                 *(uint *)(*(int *)(this + 0x24) + 0x10c) >> 4 & 0xffffff01);
    iVar2 = *(int *)(this + 0x10) + *(int *)(iVar2 + 8);
    FUN_0056b230(&local_50, iVar2 + 0x10, iVar2 + 0x50, 3);
    *(undefined4 *)(iVar2 + 0x5c) = 0;
    *(undefined4 *)(iVar2 + 0x6c) = 0;
    *(undefined4 *)(iVar2 + 0x7c) = 0;
  }
  
  // Initialize local variables with global constants
  local_70 = *(undefined4 *)(this + 0x74);
  local_5c = *(undefined4 *)(this + 0x2c);
  local_80 = DAT_00e2b1a4;
  fStack_7c = DAT_00e2b1a4;
  fStack_78 = DAT_00e2b1a4;
  fStack_74 = DAT_00e2b1a4;
  local_6c = DAT_00e2b1a4;
  local_68 = DAT_00e2b1a4;
  local_64 = DAT_00e2b1a4;
  fVar4 = DAT_00e2b1a4;
  
  FUN_00509710();
  local_58 = *(undefined4 *)(this + 0x48);
  local_60 = fVar4;
  
  // Get target object transform if available
  if (*(int *)(*(int *)(this + 4) + 0x20) != 0) {
    iVar2 = *(int *)(*(int *)(this + 4) + 0x20);
    if (iVar2 != 0) {
      *(int *)(iVar2 + 4) = *(int *)(iVar2 + 4) + 1;
    }
    iVar2 = FUN_00513f70(iVar2);
    if (iVar2 != 0) {
      local_80 = *(float *)(iVar2 + 0x10);
      fStack_7c = *(float *)(iVar2 + 0x14);
      fStack_78 = *(float *)(iVar2 + 0x18);
      fStack_74 = *(float *)(iVar2 + 0x1c);
      local_6c = *(float *)(iVar2 + 0x2c);
      local_68 = *(float *)(iVar2 + 0x30);
      local_64 = *(float *)(iVar2 + 0x34);
    }
  }
  
  // Apply collision avoidance if flag is set
  if ((*(uint *)(*(int *)(this + 0x24) + 0x104) & 0x8000) != 0) {
    local_50 = *(undefined4 *)(cameraTransform + 0x40);
    uStack_4c = *(undefined4 *)(cameraTransform + 0x44);
    uStack_48 = *(undefined4 *)(cameraTransform + 0x48);
    uStack_44 = *(undefined4 *)(cameraTransform + 0x4c);
    local_40 = *(undefined4 *)(cameraTransform + 0x50);
    uStack_3c = *(undefined4 *)(cameraTransform + 0x54);
    uStack_38 = *(undefined4 *)(cameraTransform + 0x58);
    uStack_34 = *(undefined4 *)(cameraTransform + 0x5c);
    local_30 = *(float *)(cameraTransform + 0x60);
    fStack_2c = *(float *)(cameraTransform + 100);
    fStack_28 = *(float *)(cameraTransform + 0x68);
    uStack_24 = *(undefined4 *)(cameraTransform + 0x6c);
    
    pfVar1 = (float *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x80 +
                      *(int *)(this + 0x10));
    fVar5 = fStack_2c * (pfVar1[1] - *(float *)(cameraTransform + 0x74)) +
            fStack_28 * (pfVar1[2] - *(float *)(cameraTransform + 0x78)) +
            local_30 * (*pfVar1 - *(float *)(cameraTransform + 0x70));
    fVar4 = *(float *)(*(int *)(*(int *)(this + 4) + 0x10) + 0x24);
    
    // Scale collision avoidance if needed
    if ((fVar4 < fVar5) && (DAT_00e2b05c < fVar4)) {
      local_6c = (fVar5 / fVar4) * local_6c;
    }
  }
  
  // Apply camera shake if flag is set
  if ((*(uint *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + *(int *)(this + 0x10)) &
      0x80000) != 0) {
    iVar2 = *(int *)(this + 4);
    local_80 = *(float *)(iVar2 + 0xa0) * local_80;
    fStack_7c = *(float *)(iVar2 + 0xa4) * fStack_7c;
    fStack_78 = *(float *)(iVar2 + 0xa8) * fStack_78;
  }
  
  // Store camera transform data
  piVar3 = (int *)(DAT_01206880 + 0x14);
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_0112511c;
  *piVar3 = *piVar3 + 4;
  *(int *)*piVar3 = this;
  _Dst = (void *)(*piVar3 + 0x13U & 0xfffffff0);
  *piVar3 = (int)_Dst;
  _memcpy(_Dst, &local_80, 0x30);
  *piVar3 = *piVar3 + 0x30;
  return;
}