// FUNC_NAME: Transform::addTransform
undefined4 * Transform::addTransform(undefined4 *this, int srcTransform, int addTransform)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  FUN_0081f9f0(srcTransform);
  *this = &PTR_LAB_00d736c0;
  // Copy position from source transform (offset +0x4c, +0x50, +0x54)
  this[0x13] = *(undefined4 *)(srcTransform + 0x4c);
  this[0x14] = *(undefined4 *)(srcTransform + 0x50);
  this[0x15] = *(undefined4 *)(srcTransform + 0x54);
  // Copy rotation/scale from source transform (offset +0x60, +0x64, +0x68, +0x6c)
  uVar4 = *(undefined4 *)(srcTransform + 100);
  uVar5 = *(undefined4 *)(srcTransform + 0x68);
  uVar6 = *(undefined4 *)(srcTransform + 0x6c);
  this[0x18] = *(undefined4 *)(srcTransform + 0x60);
  this[0x19] = uVar4;
  this[0x1a] = uVar5;
  this[0x1b] = uVar6;
  // Add position from addTransform
  this[0x13] = *(float *)(addTransform + 0x4c) + (float)this[0x13];
  this[0x14] = *(float *)(addTransform + 0x50) + (float)this[0x14];
  this[0x15] = *(float *)(addTransform + 0x54) + (float)this[0x15];
  // Add rotation/scale from addTransform
  fVar1 = *(float *)(addTransform + 100);
  fVar2 = *(float *)(addTransform + 0x68);
  fVar3 = *(float *)(addTransform + 0x6c);
  this[0x18] = *(float *)(addTransform + 0x60) + (float)this[0x18];
  this[0x19] = fVar1 + (float)this[0x19];
  this[0x1a] = fVar2 + (float)this[0x1a];
  this[0x1b] = fVar3 + (float)this[0x1b];
  return this;
}