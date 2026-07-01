// FUNC_NAME: Player::updateCameraShake
void __fastcall Player::updateCameraShake(int *this)
{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  float **ppfStack_a0;
  undefined4 uStack_9c;
  undefined4 *puStack_98;
  undefined4 uStack_94;
  float *pfStack_90;
  undefined1 *puStack_8c;
  float *pfStack_88;
  undefined4 uStack_84;
  float fStack_74;
  float local_70;
  float local_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  undefined1 local_50 [12];
  undefined4 local_44;
  undefined4 local_34;
  undefined8 uStack_2c;
  float local_24;
  undefined4 local_14;
  
  // Check if camera shake is active (this[0x14] is camera shake object, this[0x16] is camera)
  if (((this[0x14] != 0) && (this[0x14] != 0x48)) && (this[0x16] != 0)) {
    // Determine shake intensity based on bit 7 of flags (this[0x1c])
    if (((uint)this[0x1c] >> 7 & 1) == 0) {
      local_6c = (float)this[0x18]; // Use primary intensity
    }
    else {
      local_6c = (float)this[0x1a]; // Use secondary intensity
    }
    local_44 = 0;
    local_34 = 0;
    local_24 = 0.0;
    local_14 = _DAT_00d5780c;
    if (this[0x14] == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(this[0x14] + -0x48); // Get base object from shake object
    }
    uStack_84 = 1;
    pfStack_88 = &local_6c;
    puStack_8c = local_50;
    pfStack_90 = (float *)0x88548b;
    // Call virtual function at offset 0x90 on shake object (likely getShakeOffset)
    (**(code **)(*piVar3 + 0x90))();
    local_6c = local_24;
    pfStack_90 = (float *)0x8854a7;
    iVar1 = FUN_00471610(); // Get player position
    fStack_74 = (float)uStack_2c;
    fStack_68 = fStack_74 - *(float *)(iVar1 + 0x30); // Calculate offset from player position
    local_70 = (float)((ulonglong)uStack_2c >> 0x20);
    fStack_64 = local_70 - *(float *)(iVar1 + 0x34);
    fStack_60 = local_6c - *(float *)(iVar1 + 0x38);
    pfStack_90 = &fStack_68;
    uStack_94 = 0x8854ec;
    // Call virtual function at offset 100 (0x64) on camera - likely setPositionOffset
    (**(code **)(*(int *)this[0x16] + 100))();
    uStack_94 = DAT_00d5f00c;
    if (((uint)this[0x1c] >> 6 & 1) != 0) {
      uStack_94 = DAT_00e446a0;
    }
    puStack_98 = &DAT_00d77000;
    uStack_9c = 0x885525;
    uStack_84 = uStack_94;
    // Call virtual function at offset 0x60 on camera - likely setFOV or similar
    (**(code **)(*(int *)this[0x16] + 0x60))();
    iVar1 = 0;
    if ((*(byte *)(this + 0x1c) & 1) == 0) {
      iVar1 = this[0x16];
    }
    puStack_8c = (undefined1 *)_DAT_00d5780c;
    if (((uint)this[0x1c] >> 1 & 1) != 0) {
      puStack_8c = (undefined1 *)DAT_00d5eee4;
    }
    if (this[0x14] == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(this[0x14] + -0x48);
    }
    ppfStack_a0 = &pfStack_88;
    uStack_9c = puStack_8c;
    uStack_a4 = 0x88557b;
    uStack_a4 = (**(code **)(*piVar3 + 0x27c))(); // Call virtual function at offset 0x27c on shake object
    local_10 = this[0x16];
    uStack_ac = 0x885593;
    uVar2 = FUN_00875af0(); // Get some game object
    uStack_a4 = 0x8855a8;
    FUN_0045e580(); // Apply camera shake to view
    uStack_a4 = 0x3f800000; // 1.0f
    local_10 = uStack_94;
    uStack_ac = 0;
    // Call virtual function at offset 0x2c on this - likely setShakeIntensity
    (**(code **)(*this + 0x2c))(uVar2,0,1);
    if (this[0x14] == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(this[0x14] + -0x48);
    }
    // Call virtual function at offset 0x26c on shake object - likely updateShake
    (**(code **)(*piVar3 + 0x26c))(this[0x16]);
    if (this[0x14] == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(this[0x14] + -0x48);
    }
    // Call virtual function at offset 0x204 on shake object - likely applyShakeToCamera
    (**(code **)(*piVar3 + 0x204))(this[0x16],&uStack_ac);
    // Call virtual function at offset 0x1b4 on camera - likely finalizeCameraUpdate
    (**(code **)(*(int *)this[0x16] + 0x1b4))();
    if (iVar1 != 0) {
      // Clear bit 13 (0x2000) of flags at offset 0x1f58 in camera object
      *(uint *)(iVar1 + 0x1f58) = *(uint *)(iVar1 + 0x1f58) & 0xffffdfff;
    }
  }
  return;
}