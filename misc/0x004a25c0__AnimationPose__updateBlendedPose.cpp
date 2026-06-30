// FUNC_NAME: AnimationPose::updateBlendedPose
void AnimationPose::updateBlendedPose(float *pose) {
  int baseIndex;
  float weightThreshold = *(float *)0x00e2e210; // global threshold
  float one = *(float *)0x00e2b1a4;            // constant 1.0f
  float indexFloat = pose[0x46];               // index into animation targets
  int baseOffset = (int)indexFloat * 12;       // 12-byte stride per target

  // Accumulators for blended position, velocity etc.
  float blendedPosX = 0.0f, blendedPosY = 0.0f, blendedPosZ = 0.0f;
  float prevBlendedPosX = 0.0f, prevBlendedPosY = 0.0f, prevBlendedPosZ = 0.0f;
  float interpolatedRot[4] = {0.0f, 0.0f, 0.0f, 0.0f}; // quaternion accumulator? (size overrun)
  float totalWeight = 0.0f;
  float newWeightFactor = 0.0f; // local_264
  int iterCount = 12;

  do {
    int correctedOffset = baseOffset;
    if (12 < (uint)indexFloat) {
      correctedOffset = baseOffset - 0x90; // wrap around for large indices
    }

    // Pointer to target animation node at offset +0x88 + correctedOffset
    float *targetNode = *(float **)((int)pose + correctedOffset + 0x88);
    float targetWeight = *(float *)((int)pose + correctedOffset + 0x8c);
    float currentWeight = totalWeight;

    if ((targetNode != 0) && (weightThreshold < targetWeight)) {
      float blendFactor = pose[0x4a]; // flag/type of blending

      // Weighted sum of total weights
      totalWeight = targetWeight + currentWeight;
      float targetWeightNorm = (one / totalWeight) * targetWeight;
      float currentWeightNorm = (one / totalWeight) * currentWeight;

      // Accumulate new weight factor from target node's own weight at offset 0x50
      newWeightFactor = *(float *)(targetNode + 0x50) * targetWeightNorm + currentWeightNorm * newWeightFactor;

      // Check if it's a special blend type (using denormalized float flags)
      if ((blendFactor == 5.60519e-45f) ||
          ((blendFactor == 8.40779e-45f || blendFactor == 9.80909e-45f) || blendFactor == 7.00649e-45f)) {
        // Full matrix-based blending (skinning)
        float localMatrix1[6]; // 4x3? actually 6 floats + placeholder
        float localMatrix2[6];
        // Initialize matrices with identity-like values using 'one'
        // ... (initialization omitted for brevity, but follows pattern)
        // Multiply target node's orientation matrix into local matrix1
        // (called FUN_0056b8a0 which likely does matrix multiplication)
        // Then perform blend: newBlend = targetWeightNorm * targetDelta + currentWeightNorm * previousBlend
        // Update blended positions/etc.
        // Then slerp quaternion? (FUN_004a2c80)
        // Then final accumulation of blended position
      } else {
        // Simple linear interpolation via FUN_004a1500
        // and quaternion interpolation via FUN_004a2c80
      }
    }
    baseOffset += 12;
    indexFloat += 1.0f;
    iterCount--;
    currentWeight = totalWeight;
  } while (iterCount != 0);

  // Write final blended pose back to the pose structure
  pose[0] = blendedPosX;
  pose[1] = blendedPosY;
  pose[2] = blendedPosZ;
  pose[3] = 0.0f; // unused? ?
  pose[4] = prevBlendedPosX;
  pose[5] = prevBlendedPosY;
  pose[6] = prevBlendedPosZ;
  pose[7] = 0.0f;
  // Store some intermediate values
  pose[8] = interpolatedRot[0];
  pose[9] = interpolatedRot[1];
  pose[10] = interpolatedRot[2];
  pose[11] = interpolatedRot[3];
  pose[12] = newWeightFactor;

  // Handle additional target pointers at offset +0x22 + index*3
  float *extraPointer = pose + (int)pose[0x46] * 3 + 0x22;
  if (*extraPointer != 0.0f) {
    pose[13] = *(float *)(*(int *)extraPointer + 0x54);
    pose[14] = *(float *)(*(int *)extraPointer + 0x58);
  }
  // Call virtual method on extra pointer if weight condition
  if ((*(int *)extraPointer != 0) && (extraPointer[1] < one)) {
    (**(code (__thiscall **)(float *, float, float))*(int *)*(int *)extraPointer + 0xc)
        (pose, pose[0x4a], extraPointer[1]);
  }

  // Compute a damping factor using some global timer
  float globalTimer = *(float *)0x01206800; // global deltaTime or similar
  // One-time initialization of damping timer
  if ((*(int *)0x01225d44 & 1) == 0) {
    *(int *)0x01225d44 |= 1;
    *(float *)0x01225d40 = *(float *)0x01217ab8;
  }
  *(float *)0x01225d40 = *(float *)0x01225d40 * *(float *)0x011286a8 + globalTimer * *(float *)0x00e44784;
  if (*(float *)0x01225d40 <= 0.0f) {
    pose[16] = 0.0f;
  } else {
    float timeDiff = pose[9] - interpolatedRot[1]; // note: reused variable? careful
    pose[16] = sqrtf(timeDiff) / *(float *)0x01225d40;
  }

  // Copy current pose to temporary buffers for blending?
  float tempPose1[16], tempPose2[16];
  memcpy(tempPose1, pose, 16 * sizeof(float));
  memcpy(tempPose2, pose, 16 * sizeof(float));

  // Build a sorted list of secondary blend targets (pointers at +0x4b+step)
  float *secondaryPtrs[4];
  int sortedCount = 0;
  float *current = pose + 0x4b;
  for (int i = 0; i < 4; i++) {
    float ptrFloat = *current;
    if (ptrFloat != 0.0f) {
      // Insert into sorted order based on some ID (offset+0xc)
      uintptr_t thisId = *(uint *)((int)ptrFloat + 0xc);
      int j = 0;
      while (j < sortedCount && *(uint *)(*(int *)secondaryPtrs[j] + 0xc) >= thisId) {
        j++;
      }
      // Shift and insert
      for (int k = sortedCount; k > j; k--) {
        secondaryPtrs[k] = secondaryPtrs[k-1];
      }
      secondaryPtrs[j] = (float *)(int)ptrFloat; // cast from float pointer trick
      sortedCount++;
    }
    current += 2; // step 2 floats
  }

  // Apply secondary blend effects
  for (int i = 0; i < sortedCount; i++) {
    (**(code (__thiscall **)(float, float *, float *))(*((int *)secondaryPtrs[i]) + 8))
        (globalTimer, tempPose1, tempPose2);
  }

  // Copy final result back to pose
  memcpy(pose, tempPose2, 16 * sizeof(float));
}