// FUNC_NAME: CameraSystem::calculateCameraCollision
uint CameraSystem::calculateCameraCollision(int *param_1, int *param_2, float *outDistance, float *outPos1, float *outPos2)
{
  code *vtableEntry;
  int *somePtr;
  int result;
  float *floatPtr;
  undefined1 byteResult;
  float diff1, diff2, diff3, diff4, diff5;
  float stackVals[6]; // fStack_50, fStack_4c, local_48, fStack_44, fStack_40, local_3c
  float tempVals[6]; // fStack_38, fStack_34, fStack_30, fStack_28, fStack_24, fStack_20
  
  vtableEntry = *(code **)(*param_1 + 0x3c); // vtable offset 0x3c - likely getCameraTransform or similar
  *outDistance = 0.0f;
  somePtr = (int *)(*vtableEntry)(&stackVals[3], &stackVals[0]); // call vtable method, get some transform/box
  
  // Check if all three axis differences are <= 0 (i.e., no collision detected)
  if ((((((float)((uint)(stackVals[1] - stackVals[5]) & DAT_00e44680) <= 0.0f) &&
        ((float)((uint)(stackVals[2] - stackVals[4]) & DAT_00e44680) <= 0.0f)) &&
       ((float)((uint)(stackVals[3] - stackVals[0]) & DAT_00e44680) <= 0.0f)) &&
      ((somePtr = param_2, param_2 != (int *)0x0 && ((int *)*param_2 != (int *)0x0))) &&
     (somePtr = (int *)param_2[2], somePtr != (int *)0x0)) {
    // Get some transform from param_2 (likely a collision object)
    somePtr = (int *)(**(code **)(*(int *)*param_2 + 0x1c))(somePtr, DAT_00d58cbc, &tempVals[0]);
    // Copy transformed values back to stackVals
    stackVals[3] = tempVals[2]; // fStack_30
    stackVals[4] = tempVals[4]; // fStack_24
    stackVals[1] = tempVals[0]; // fStack_38
    stackVals[2] = tempVals[3]; // fStack_34
    stackVals[5] = tempVals[5]; // fStack_28
    stackVals[0] = tempVals[6]; // fStack_20
  }
  
  byteResult = 0;
  // Check again if all axis differences are <= 0 (no collision)
  if ((((float)((uint)(stackVals[1] - stackVals[5]) & DAT_00e44680) <= 0.0f) &&
      ((float)((uint)(stackVals[2] - stackVals[4]) & DAT_00e44680) <= 0.0f)) &&
     ((float)((uint)(stackVals[3] - stackVals[0]) & DAT_00e44680) <= 0.0f)) {
    *outDistance = DAT_00d757b8; // Some default distance value
    return (uint)somePtr & 0xffffff00;
  }
  
  // Calculate differences along two axes
  fVar6 = stackVals[0] - stackVals[3]; // diff on axis 0
  fVar9 = stackVals[5] - stackVals[1]; // diff on axis 1
  
  if ((fVar6 * DAT_00d5fb68 <= fVar9) || (fVar9 * DAT_00d5fb68 <= fVar6)) {
    // One axis is significantly larger - handle edge/side collision
    byteResult = 1;
    result = FUN_00471610(); // Get some global state (likely player/camera position)
    floatPtr = (float *)(result + 0x30); // +0x30: position vector start
    
    float zeroVal = 0.0f;
    if (fVar6 <= fVar9) {
      // X axis is smaller - use Y axis difference
      float scaledDiff = fVar6 * _DAT_00d5c458; // Scale factor
      *outDistance = scaledDiff;
      float diffA = (float)((uint)(stackVals[5] - *floatPtr) & DAT_00e44680); // Absolute difference on axis 0
      float diffB = (float)((uint)(stackVals[1] - *floatPtr) & DAT_00e44680); // Absolute difference on axis 0
      fVar6 = _DAT_00d5780c; // Some constant
    }
    else {
      // Y axis is smaller - use X axis difference
      float scaledDiff = fVar9 * _DAT_00d5c458;
      *outDistance = scaledDiff;
      float diffA = (float)((uint)(stackVals[0] - *(float *)(result + 0x38)) & DAT_00e44680); // Absolute diff on axis 2
      float diffB = (float)((uint)(stackVals[3] - *(float *)(result + 0x38)) & DAT_00e44680);
      fVar6 = 0.0f;
      fVar10 = _DAT_00d5780c;
    }
    // Calculate two output positions (likely near and far collision points)
    float adjustedDiff = diffA - scaledDiff;
    *outPos1 = fVar6 * adjustedDiff + *floatPtr;
    outPos1[1] = adjustedDiff * 0.0f + *(float *)(result + 0x34);
    float otherDiff = DAT_00e44564 - (diffB - scaledDiff);
    outPos1[2] = fVar10 * adjustedDiff + *(float *)(result + 0x38);
    *outPos2 = otherDiff * fVar6 + *floatPtr;
    outPos2[1] = otherDiff * 0.0f + *(float *)(result + 0x34);
    outPos2[2] = otherDiff * fVar10 + *(float *)(result + 0x38);
  }
  else {
    // No significant axis difference - just scale and return
    if (fVar6 <= fVar9) {
      *outDistance = fVar9 * _DAT_00d5c458;
    }
    else {
      *outDistance = fVar6 * _DAT_00d5c458;
    }
    result = FUN_00471610(); // Get global state
    floatPtr = (float *)(result + 0x30); // +0x30: position vector
    *(undefined8 *)outPos1 = *(undefined8 *)(result + 0x30); // Copy position
    outPos1[2] = *(float *)(result + 0x38); // +0x38: Z component
  }
  
  *outDistance = *outDistance * _DAT_00d63484; // Final scale factor
  return CONCAT31((int3)((uint)floatPtr >> 8), byteResult);
}