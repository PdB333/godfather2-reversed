// FUNC_NAME: Matrix4x4::scaleAndSetFromTransform
undefined4 * Matrix4x4::scaleAndSetFromTransform(undefined4 *this, int transform, float scale)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  
  FUN_008334a0();
  uVar4 = _DAT_00d5780c;
  *this = &PTR_LAB_00d73454;
  this[0x18] = uVar4;
  this[0x19] = uVar4;
  this[0x1a] = uVar4;
  this[0x1b] = uVar4;
  this[0x1c] = uVar4;
  this[0x1d] = uVar4;
  this[0x1e] = uVar4;
  this[0x1f] = uVar4;
  this[0x14] = DAT_00d5d7b8;
  this[0x15] = DAT_00e44620;
  this[0x16] = DAT_00d5ef88;
  this[0x17] = DAT_00e44980;
  fVar1 = *(float *)(transform + 100);
  fVar2 = *(float *)(transform + 0x68);
  fVar3 = *(float *)(transform + 0x6c);
  this[0x18] = *(float *)(transform + 0x60) * scale;
  this[0x19] = fVar1 * scale;
  this[0x1a] = fVar2 * scale;
  this[0x1b] = fVar3 * scale;
  fVar1 = *(float *)(transform + 0x74);
  fVar2 = *(float *)(transform + 0x78);
  fVar3 = *(float *)(transform + 0x7c);
  this[0x1c] = *(float *)(transform + 0x70) * scale;
  this[0x1d] = fVar1 * scale;
  this[0x1e] = fVar2 * scale;
  this[0x1f] = fVar3 * scale;
  fVar1 = *(float *)(transform + 0x54);
  fVar2 = *(float *)(transform + 0x58);
  fVar3 = *(float *)(transform + 0x5c);
  this[0x14] = *(float *)(transform + 0x50) * scale;
  this[0x15] = fVar1 * scale;
  this[0x16] = fVar2 * scale;
  this[0x17] = fVar3 * scale;
  return this;
}