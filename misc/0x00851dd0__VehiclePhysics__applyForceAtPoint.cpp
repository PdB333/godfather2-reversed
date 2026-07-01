// FUNC_NAME: VehiclePhysics::applyForceAtPoint
void VehiclePhysics::applyForceAtPoint(int *this, float *force, float *point)
{
  code *pcVar1;
  int iVar2;
  double dVar3;
  float diffX;
  float diffY;
  float diffZ;
  undefined4 local_144;
  float fStack_138;
  float fStack_134;
  float fStack_130;
  float local_12c;
  float local_128;
  float local_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
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
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  // Check direction flag at this+8 (byte)
  if ((char)this[2] == '\0') {
    diffX = *force - *point;
    diffY = force[1] - point[1];
    diffZ = force[2] - point[2];
  }
  else {
    diffX = *point - *force;
    diffY = point[1] - force[1];
    diffZ = point[2] - force[2];
  }
  local_144 = 0;
  // Normalize the difference vector
  FUN_0056afa0(&diffX, &diffX);
  // Get physics body pointer from this[0]
  this = (int *)*this;
  local_12c = diffX;
  local_128 = diffY;
  local_124 = diffZ;
  // Get rigid body via vtable+0x28
  iVar2 = (**(code **)(*this + 0x28))();
  // Read position from rigid body at +0x20, +0x24, +0x28
  fStack_138 = *(float *)(iVar2 + 0x20);
  fStack_134 = *(float *)(iVar2 + 0x24);
  fStack_130 = *(float *)(iVar2 + 0x28);
  // Initialize matrix/transform data with global constant _DAT_00d5780c
  uStack_d4 = 0;
  uStack_c4 = 0;
  uStack_b4 = 0;
  uStack_20 = _DAT_00d5780c;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0;
  uStack_120 = _DAT_00d5780c;
  uStack_11c = 0;
  uStack_118 = 0;
  uStack_114 = 0;
  uStack_110 = 0;
  uStack_10c = _DAT_00d5780c;
  uStack_108 = 0;
  uStack_104 = 0;
  uStack_100 = 0;
  uStack_fc = 0;
  uStack_f8 = _DAT_00d5780c;
  uStack_f4 = 0;
  uStack_a4 = _DAT_00d5780c;
  uStack_f0 = 0;
  uStack_ec = 0;
  uStack_e8 = 0;
  uStack_e4 = _DAT_00d5780c;
  // Build first transform from direction and point
  FUN_00851a40(&uStack_120, &local_12c, point);
  uStack_a0 = uStack_120;
  uStack_90 = uStack_110;
  uStack_9c = uStack_11c;
  uStack_8c = uStack_10c;
  uStack_98 = uStack_118;
  uStack_88 = uStack_108;
  uStack_94 = 0;
  uStack_84 = 0;
  uStack_80 = uStack_100;
  uStack_74 = 0;
  uStack_7c = uStack_fc;
  uStack_70 = uStack_f0;
  uStack_78 = uStack_f8;
  uStack_6c = uStack_ec;
  uStack_68 = uStack_e8;
  uStack_64 = _DAT_00d5780c;
  uStack_e0 = uStack_20;
  uStack_dc = uStack_1c;
  uStack_d8 = uStack_18;
  uStack_d4 = uStack_14;
  uStack_d0 = uStack_14;
  uStack_cc = uStack_20;
  uStack_c8 = uStack_14;
  uStack_c4 = uStack_14;
  uStack_c0 = uStack_14;
  uStack_bc = uStack_14;
  uStack_b8 = uStack_20;
  uStack_b4 = uStack_14;
  uStack_b0 = uStack_14;
  uStack_ac = uStack_14;
  uStack_a8 = uStack_14;
  uStack_a4 = uStack_20;
  // Build second transform from rigid body position and point
  FUN_00851a40(&uStack_e0, &fStack_138, point);
  uStack_60 = uStack_e0;
  uStack_5c = uStack_dc;
  uStack_58 = uStack_d8;
  uStack_50 = uStack_d0;
  uStack_54 = 0;
  uStack_44 = 0;
  uStack_34 = 0;
  uStack_4c = uStack_cc;
  uStack_30 = uStack_b0;
  uStack_48 = uStack_c8;
  uStack_2c = uStack_ac;
  uStack_40 = uStack_c0;
  uStack_28 = uStack_a8;
  uStack_3c = uStack_bc;
  uStack_24 = _DAT_00d5780c;
  uStack_38 = uStack_b8;
  // Compute dot product of force and direction, masked with global constant
  dVar3 = (double)(float)((uint)(diffZ * fStack_130 + diffY * fStack_134 +
                                diffX * fStack_138) & DAT_00e44680);
  FUN_00b9b988();
  pcVar1 = *(code **)(*this + 0x20);
  // Store result at this+0xA0 (0x28 * 4)
  this[0x28] = (int)(float)dVar3;
  // Apply force via vtable+0x20 and vtable+0x24
  (*pcVar1)(&uStack_60);
  (**(code **)(*this + 0x24))(&uStack_a4);
  return;
}