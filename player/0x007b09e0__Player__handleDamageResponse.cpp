// FUNC_NAME: Player::handleDamageResponse
void __thiscall Player::handleDamageResponse(int this, int damageType)
{
  int iVar2;
  int iVar3;
  float *pfVar4;
  undefined8 *puVar5;
  int iVar6;
  undefined8 local_1e0;
  float local_1d8;
  float local_1d4;
  undefined4 local_1d0;
  float local_1cc;
  undefined4 local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  float fStack_1b4;
  float local_1b0;
  int local_1ac;
  undefined4 local_1a8;
  float fStack_1a4;
  undefined4 local_1a0;
  undefined8 local_19c;
  float local_194;
  undefined **local_190;
  float local_18c;
  float local_170;
  undefined4 local_16c;
  undefined4 local_160;
  undefined4 local_140;
  int local_130;
  undefined **local_120;
  float local_11c;
  float local_100;
  undefined4 local_fc;
  undefined4 local_f0;
  undefined4 local_d0;
  int local_c0;
  undefined1 local_b0 [80];
  undefined1 local_60 [92];
  
  iVar2 = *(int *)(this + 0x58); // +0x58: player's entity pointer
  if (*(int *)(iVar2 + 0xff0) == 0) { // +0xff0: some component pointer
    iVar6 = 0;
  }
  else {
    iVar6 = *(int *)(iVar2 + 0xff0) + -0x48; // offset to component base
  }
  if (iVar2 == 0) {
    return;
  }
  if (iVar6 == 0) {
    return;
  }
  local_1ac = this;
  FUN_007f63e0(6); // some debug/log function
  FUN_007f63e0(6);
  *(uint *)(iVar6 + 0x4a4) = *(uint *)(iVar6 + 0x4a4) | 1; // +0x4a4: flags
  local_1d0 = 0;
  local_1c8 = CONCAT31(local_1c8._1_3_,0xff); // default alpha = 255
  if ((char)damageType == '\0') { // damage type 0 = none?
    *(undefined1 *)(iVar2 + 0xff9) = 0;
    *(undefined1 *)(iVar6 + 0xff9) = 0;
  }
  else if (((((((char)damageType == '\x02') || ((char)damageType == '\x03')) || ((char)damageType == '\x04'))
            || ((((char)damageType == '\x05' || ((char)damageType == '\x06')) ||
                (((char)damageType == '\a' || (((char)damageType == '\b' || ((char)damageType == '\n'))))))))
           || ((char)damageType == '\v')) ||
          ((((((char)damageType == '\f' || ((char)damageType == '\r')) || ((char)damageType == '\x0e')) ||
            (((char)damageType == '\t' || ((char)damageType == '\x10')))) ||
           (((char)damageType == '\x0f' || ((char)damageType == '\x11')))))) {
    // Various damage types that clear the flag
    *(undefined1 *)(iVar2 + 0xff9) = 0;
    *(undefined1 *)(iVar6 + 0xff9) = 0;
    *(uint *)(iVar2 + 0x4a4) = *(uint *)(iVar2 + 0x4a4) | 1;
    *(uint *)(iVar6 + 0x4a4) = *(uint *)(iVar6 + 0x4a4) | 1;
  }
  else {
    if ((char)damageType != '\x01') goto LAB_007b0ad1; // damage type 1 = special
    *(undefined1 *)(iVar2 + 0xff9) = 1;
    *(undefined1 *)(iVar6 + 0xff9) = 1;
  }
  local_1d0 = _DAT_00d5c458; // some global color value
LAB_007b0ad1:
  iVar2 = FUN_00471610(); // get some object (maybe player position)
  iVar3 = FUN_00471610(); // get another object (maybe attacker position)
  local_1e0._0_4_ = *(float *)(iVar3 + 0x30) - *(float *)(iVar2 + 0x30); // delta X
  local_1e0._4_4_ = *(float *)(iVar3 + 0x34) - *(float *)(iVar2 + 0x34); // delta Y
  local_1d8 = *(float *)(iVar3 + 0x38) - *(float *)(iVar2 + 0x38); // delta Z
  FUN_0043a210(&local_1e0,&local_1e0); // normalize vector
  pfVar4 = (float *)FUN_00471610(); // get something
  local_1cc = (float)FUN_00471610(); // get something else
  iVar2 = FUN_00471610();
  local_1cc = *(float *)((int)local_1cc + 4) * local_1e0._4_4_ + *pfVar4 * (float)local_1e0 +
              *(float *)(iVar2 + 8) * local_1d8; // dot product with direction
  local_1d4 = _DAT_00d5780c; // some speed/force value
  if ((*(char *)(iVar6 + 0x1b8c) == '\x03') || (*(char *)(iVar6 + 0x1b8c) == '\x02')) {
    local_1d4 = DAT_00d5eee4; // different value for certain states
  }
  iVar2 = FUN_00471610(); // get something
  if ((char)damageType == '\x01') {
    // Special damage type: use global offset
    local_1d8 = DAT_00e44564 - *(float *)(iVar2 + 0x28);
    local_1e0 = CONCAT44(DAT_00e44564 - *(float *)(iVar2 + 0x24),
                         DAT_00e44564 - *(float *)(iVar2 + 0x20));
  }
  else {
    local_1e0 = *(undefined8 *)(iVar2 + 0x20); // position vector
    local_1d8 = *(float *)(iVar2 + 0x28);
  }
  iVar2 = FUN_00471610(); // get something
  local_1b0 = *(float *)(iVar2 + 0x38);
  fStack_1b4 = (float)((ulonglong)*(undefined8 *)(iVar2 + 0x30) >> 0x20);
  fStack_1b4 = fStack_1b4 + DAT_00d5ef50; // add some offset
  local_1b8 = (float)*(undefined8 *)(iVar2 + 0x30);
  local_1c4 = (float)local_1e0 * local_1d4 + local_1b8; // calculate new position
  local_1c0 = local_1e0._4_4_ * local_1d4 + fStack_1b4;
  local_1bc = local_1d8 * local_1d4 + local_1b0;
  local_fc = 0xffffffff;
  local_f0 = 0xffffffff;
  local_120 = &PTR_FUN_00e32a8c; // some vtable
  local_c0 = 0;
  local_100 = _DAT_00d5780c;
  local_d0 = 0;
  local_11c = _DAT_00d5780c;
  FUN_00542650(&local_1b8,&local_1c4,0x40122,0x80000000,0,0); // some physics/raycast function
  FUN_009e5ed0(local_60,&local_120); // copy result
  if ((((*(char *)(iVar6 + 0x1b8c) == '\x03') || (*(char *)(iVar6 + 0x1b8c) == '\x02')) &&
      ((char)damageType == '\0')) && (local_1cc < 0.0)) {
    // Special case: certain state + damage type 0 + negative dot product
    puVar5 = (undefined8 *)FUN_00471610(); // get something
    uVar1 = *puVar5;
    local_194 = *(float *)(puVar5 + 1);
    local_19c._0_4_ = (float)uVar1;
    local_19c._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
    local_1d8 = (DAT_00e44564 - local_194) + local_1d8;
    local_1e0 = CONCAT44((DAT_00e44564 - local_19c._4_4_) + local_1e0._4_4_,
                         (DAT_00e44564 - (float)local_19c) + (float)local_1e0);
    local_19c = uVar1;
    FUN_0043a210(&local_1e0,&local_1e0); // re-normalize
    local_1d4 = local_1d4 - DAT_00d5ef88; // reduce force
  }
  iVar2 = FUN_00471610(); // get something
  local_1a0 = *(undefined4 *)(iVar2 + 0x38);
  fStack_1a4 = (float)((ulonglong)*(undefined8 *)(iVar2 + 0x30) >> 0x20);
  _local_1a8 = CONCAT44(fStack_1a4 + DAT_00d5ef50,(int)*(undefined8 *)(iVar2 + 0x30));
  iVar2 = FUN_00471610(); // get something
  local_1c4 = (float)local_1e0 * local_1d4 + *(float *)(iVar2 + 0x30);
  local_1c0 = local_1e0._4_4_ * local_1d4 + *(float *)(iVar2 + 0x34) + DAT_00d5ef50;
  local_1bc = local_1d8 * local_1d4 + *(float *)(iVar2 + 0x38);
  local_16c = 0xffffffff;
  local_160 = 0xffffffff;
  local_190 = &PTR_FUN_00e32a8c;
  local_130 = 0;
  local_170 = _DAT_00d5780c;
  local_140 = 0;
  local_18c = _DAT_00d5780c;
  FUN_00542650(&local_1a8,&local_1c4,0x40122,0x80000000,0,0); // second physics check
  FUN_009e5ed0(local_b0,&local_190); // copy result
  if ((local_c0 != 0) || (local_130 != 0)) {
    // Hit something
    local_1c8 = CONCAT31(local_1c8._1_3_,2); // set alpha to 2
    if (((char)damageType != '\x01') && (local_1cc <= _DAT_00d577a0)) {
      local_1c8 = CONCAT31(local_1c8._1_3_,1); // set alpha to 1
    }
  }
  FUN_00805810(damageType,local_1d0,local_1c8); // apply damage effect
  FUN_007ab730(); // cleanup/update
  return;
}