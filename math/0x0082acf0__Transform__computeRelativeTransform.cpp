// FUNC_NAME: Transform::computeRelativeTransform
undefined4 * Transform::computeRelativeTransform(undefined4 *this, int parentTransform, int childTransform)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  FUN_0081f9f0(parentTransform); // likely identity or copy
  *this = &PTR_LAB_00d736c0; // vtable pointer
  // Copy position (offset 0x4c, 0x50, 0x54) from parent
  this[0x13] = *(undefined4 *)(parentTransform + 0x4c);
  this[0x14] = *(undefined4 *)(parentTransform + 0x50);
  this[0x15] = *(undefined4 *)(parentTransform + 0x54);
  // Copy rotation/scale (offset 0x64, 0x68, 0x6c) from parent
  uVar4 = *(undefined4 *)(parentTransform + 100); // 0x64
  uVar5 = *(undefined4 *)(parentTransform + 0x68);
  uVar6 = *(undefined4 *)(parentTransform + 0x6c);
  this[0x18] = *(undefined4 *)(parentTransform + 0x60);
  this[0x19] = uVar4;
  this[0x1a] = uVar5;
  this[0x1b] = uVar6;
  // Subtract child transform position (offset 0x4c, 0x50, 0x54)
  this[0x13] = (float)this[0x13] - *(float *)(childTransform + 0x4c);
  this[0x14] = (float)this[0x14] - *(float *)(childTransform + 0x50);
  this[0x15] = (float)this[0x15] - *(float *)(childTransform + 0x54);
  // Subtract child transform rotation/scale (offset 0x60, 0x64, 0x68, 0x6c)
  fVar1 = *(float *)(childTransform + 100); // 0x64
  fVar2 = *(float *)(childTransform + 0x68);
  fVar3 = *(float *)(childTransform + 0x6c);
  this[0x18] = (float)this[0x18] - *(float *)(childTransform + 0x60);
  this[0x19] = (float)this[0x19] - fVar1;
  this[0x1a] = (float)this[0x1a] - fVar2;
  this[0x1b] = (float)this[0x1b] - fVar3;
  return this;
}