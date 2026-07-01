// FUNC_NAME: ChaseCamera::updateCameraTransform
void __fastcall ChaseCamera::updateCameraTransform(int *this)
{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  float unaff_ESI;
  float fStack_d8;
  float fStack_d4;
  undefined1 local_d0 [4];
  float fStack_cc;
  float fStack_c8;
  float local_c4;
  float fStack_bc;
  float fStack_b8;
  float local_b4;
  float fStack_ac;
  float fStack_a8;
  float local_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 local_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 local_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  float fStack_68;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  local_c4 = 0.0;
  local_b4 = 0.0;
  local_a4 = 0.0;
  local_94 = _DAT_00d5780c; // Identity quaternion or zero vector
  local_84 = 0;
  local_74 = 0;
  local_64 = 0;
  local_54 = _DAT_00d5780c;
  
  // Get world transform from the target object (offset +0x74 = 0x1d * 4)
  (**(code **)(*this + 0x8c))(local_d0, this + 0x1d, 1);
  
  fVar1 = (float)this[0x81]; // Some rotation/angle component
  fVar2 = (float)this[0x80];
  fVar3 = (float)this[0x7f];
  
  // Matrix/vector multiplication for camera orientation
  fStack_ac = fVar2 * fStack_cc + fVar1 * fStack_bc + fVar3 * unaff_ESI + fStack_ac;
  fStack_a8 = fVar2 * fStack_c8 + fVar1 * fStack_b8 + fVar3 * fStack_d8 + fStack_a8;
  local_a4 = fVar2 * local_c4 + fVar1 * local_b4 + fVar3 * fStack_d4 + local_a4;
  
  // Debug rendering if flag set (bit 14 of flags at offset 0x18c = 99*4)
  if (((uint)this[99] >> 0xe & 1) != 0) {
    FUN_0046cf70(&stack0xffffff24, &DAT_00d7b3c0, DAT_00e44600, 1);
  }
  
  // Get parent object (offset +0x68 = 0x1a * 4)
  if (this[0x1a] == 0) {
    piVar6 = (int *)0x0;
  }
  else {
    piVar6 = (int *)(this[0x1a] + -0x48); // Adjust to get base object pointer
  }
  
  // Get another transform from parent
  (**(code **)(*piVar6 + 0x90))(&uStack_9c, this + 0x1c, 1);
  
  uStack_5c = 0;
  uStack_4c = 0;
  uStack_3c = 0;
  uStack_2c = _DAT_00d5780c;
  
  FUN_008b7ed0(&fStack_68); // Some camera calculation function
  
  // Copy results into local transform
  fStack_a8 = fStack_68;
  local_a4 = (float)local_64;
  uStack_a0 = uStack_60;
  uStack_9c = uStack_5c;
  uStack_98 = uStack_58;
  local_94 = local_54;
  uStack_90 = uStack_50;
  uStack_8c = uStack_4c;
  uStack_88 = uStack_48;
  local_84 = uStack_44;
  uStack_80 = uStack_40;
  uStack_7c = uStack_3c;
  uStack_78 = uStack_38;
  local_74 = uStack_34;
  uStack_70 = uStack_30;
  uStack_6c = uStack_2c;
  
  // Set camera transform (vtable +0x2c)
  (**(code **)(*this + 0x2c))(&fStack_a8);
  
  // Get parent again for FOV/zoom
  if (this[0x1a] == 0) {
    piVar6 = (int *)0x0;
  }
  else {
    piVar6 = (int *)(this[0x1a] + -0x48);
  }
  
  iVar4 = *this;
  uVar5 = (**(code **)(*piVar6 + 0x50))(); // Get FOV from parent
  (**(code **)(iVar4 + 0x54))(uVar5); // Set FOV on camera
  
  // Get parent again for near/far clip
  if (this[0x1a] == 0) {
    piVar6 = (int *)0x0;
  }
  else {
    piVar6 = (int *)(this[0x1a] + -0x48);
  }
  
  iVar4 = *this;
  uVar5 = (**(code **)(*piVar6 + 0x58))(0xc0); // Get near clip distance
  (**(code **)(iVar4 + 0x5c))(uVar5); // Set near clip on camera
  
  // Update audio listener position
  if (this[0x1a] != 0) {
    uVar5 = FUN_004709e0(); // Get audio manager
    FUN_00470a10(uVar5); // Update listener position
    return;
  }
  uVar5 = FUN_004709e0();
  FUN_00470a10(uVar5);
  return;
}