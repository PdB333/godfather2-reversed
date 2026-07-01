// FUNC_NAME: Physics::computeRelativeTransform
undefined4 * Physics::computeRelativeTransform(undefined4 *outTransform, int entityA, int entityB)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined4 uVar7;
  
  FUN_008334a0(); // likely memset or zero-initialization helper
  uVar7 = _DAT_00d5780c; // likely 0.0f constant
  *outTransform = &PTR_LAB_00d73454; // vtable pointer
  outTransform[0x18] = uVar7; // +0x60: translation.x
  outTransform[0x19] = uVar7; // +0x64: translation.y
  outTransform[0x1a] = uVar7; // +0x68: translation.z
  outTransform[0x1b] = uVar7; // +0x6c: translation.w (unused)
  outTransform[0x1c] = uVar7; // +0x70: rotation.x
  outTransform[0x1d] = uVar7; // +0x74: rotation.y
  outTransform[0x1e] = uVar7; // +0x78: rotation.z
  outTransform[0x1f] = uVar7; // +0x7c: rotation.w
  outTransform[0x14] = DAT_00d5d7b8; // +0x50: scale.x
  outTransform[0x15] = DAT_00e44620; // +0x54: scale.y
  outTransform[0x16] = DAT_00d5ef88; // +0x58: scale.z
  outTransform[0x17] = DAT_00e44980; // +0x5c: scale.w (unused)
  
  // Compute translation difference
  fVar1 = *(float *)(entityA + 100); // +0x64: entityA translation.y
  fVar2 = *(float *)(entityA + 0x68); // +0x68: entityA translation.z
  fVar3 = *(float *)(entityA + 0x6c); // +0x6c: entityA translation.w
  fVar4 = *(float *)(entityB + 100); // +0x64: entityB translation.y
  fVar5 = *(float *)(entityB + 0x68); // +0x68: entityB translation.z
  fVar6 = *(float *)(entityB + 0x6c); // +0x6c: entityB translation.w
  outTransform[0x18] = *(float *)(entityA + 0x60) - *(float *)(entityB + 0x60); // translation.x diff
  outTransform[0x19] = fVar1 - fVar4; // translation.y diff
  outTransform[0x1a] = fVar2 - fVar5; // translation.z diff
  outTransform[0x1b] = fVar3 - fVar6; // translation.w diff
  
  // Compute rotation difference
  fVar1 = *(float *)(entityA + 0x74); // +0x74: entityA rotation.y
  fVar2 = *(float *)(entityA + 0x78); // +0x78: entityA rotation.z
  fVar3 = *(float *)(entityA + 0x7c); // +0x7c: entityA rotation.w
  fVar4 = *(float *)(entityB + 0x74); // +0x74: entityB rotation.y
  fVar5 = *(float *)(entityB + 0x78); // +0x78: entityB rotation.z
  fVar6 = *(float *)(entityB + 0x7c); // +0x7c: entityB rotation.w
  outTransform[0x1c] = *(float *)(entityA + 0x70) - *(float *)(entityB + 0x70); // rotation.x diff
  outTransform[0x1d] = fVar1 - fVar4; // rotation.y diff
  outTransform[0x1e] = fVar2 - fVar5; // rotation.z diff
  outTransform[0x1f] = fVar3 - fVar6; // rotation.w diff
  
  // Compute scale difference
  fVar1 = *(float *)(entityA + 0x54); // +0x54: entityA scale.y
  fVar2 = *(float *)(entityA + 0x58); // +0x58: entityA scale.z
  fVar3 = *(float *)(entityA + 0x5c); // +0x5c: entityA scale.w
  fVar4 = *(float *)(entityB + 0x54); // +0x54: entityB scale.y
  fVar5 = *(float *)(entityB + 0x58); // +0x58: entityB scale.z
  fVar6 = *(float *)(entityB + 0x5c); // +0x5c: entityB scale.w
  outTransform[0x14] = *(float *)(entityA + 0x50) - *(float *)(entityB + 0x50); // scale.x diff
  outTransform[0x15] = fVar1 - fVar4; // scale.y diff
  outTransform[0x16] = fVar2 - fVar5; // scale.z diff
  outTransform[0x17] = fVar3 - fVar6; // scale.w diff
  
  return outTransform;
}