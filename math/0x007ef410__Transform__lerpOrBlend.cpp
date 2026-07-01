// FUNC_NAME: Transform::lerpOrBlend
void Transform::lerpOrBlend(float *outTransform, int param_2, float *inTransform, byte flags)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  
  if ((flags & 1) == 0) {
    // No blend: direct copy or add
    if ((flags & 2) != 0) {
      if ((flags & 4) != 0) {
        // Copy position (first 4 floats)
        uVar7 = inTransform[1];
        uVar8 = inTransform[2];
        uVar9 = inTransform[3];
        *outTransform = *inTransform;
        outTransform[1] = uVar7;
        outTransform[2] = uVar8;
        outTransform[3] = uVar9;
      }
      if ((flags & 8) != 0) {
        // Copy rotation (next 4 floats)
        uVar7 = inTransform[5];
        uVar8 = inTransform[6];
        uVar9 = inTransform[7];
        outTransform[4] = inTransform[4];
        outTransform[5] = uVar7;
        outTransform[6] = uVar8;
        outTransform[7] = uVar9;
      }
    }
  }
  else {
    // Blend mode: lerp position, add rotation
    if ((flags & 4) != 0) {
      // Lerp position using FUN_0056cba0 (likely a quaternion/vector lerp)
      FUN_0056cba0(param_2, inTransform, &local_40);
      *outTransform = local_40;
      outTransform[1] = uStack_3c;
      outTransform[2] = uStack_38;
      outTransform[3] = uStack_34;
    }
    if ((flags & 8) != 0) {
      // Add rotation (quaternion addition)
      fVar1 = *(float *)(param_2 + 0x14);
      fVar2 = *(float *)(param_2 + 0x18);
      fVar3 = *(float *)(param_2 + 0x1c);
      fVar4 = (float)inTransform[5];
      fVar5 = (float)inTransform[6];
      fVar6 = (float)inTransform[7];
      outTransform[4] = *(float *)(param_2 + 0x10) + (float)inTransform[4];
      outTransform[5] = fVar1 + fVar4;
      outTransform[6] = fVar2 + fVar5;
      outTransform[7] = fVar3 + fVar6;
      return;
    }
  }
  return;
}