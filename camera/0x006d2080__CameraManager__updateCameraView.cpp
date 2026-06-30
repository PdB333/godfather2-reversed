// FUNC_NAME: CameraManager::updateCameraView

void __thiscall CameraManager::updateCameraView(CameraManager *this, undefined4 param_2, bool isReset)
{
  // Fields:
  // this+0x20: position x (float)
  // this+0x24: position y
  // this+0x28: position z
  // this+0x2c: position w (unused)
  // this+0x30: rotation x (quaternion or axis)
  // this+0x34: rotation y
  // this+0x38: rotation z
  // this+0x3c: rotation w
  // this+0x40: some offset x
  // this+0x44: offset y
  // this+0x48: offset z
  // this+0x4c: offset w?
  // this+0x50: some velocity/scale
  // this+0x60: timer
  // this+0x90-0x9c: raw transform (4x4 matrix row?)
  // this+0xb0-0xbc: output transform (4x4 matrix)
  // this+0xd0: arg2 stored
  // this+0xd4: some index for list?
  // this+0xd8: function pointer?
  // this+0xe0: accumulated offset?
  // this+0xe8: blend factor

  float accumOffset;

  // Reset timers
  *(undefined4 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 100) = 0;

  // Global DAT_0112a862 is a flag
  if (DAT_0112a862 == '\0') {
    *(undefined4 *)(this + 0xe8) = 0;
  } else {
    *(float *)(this + 0xe8) = DAT_00e5116c + DAT_00d58cbc;
    DAT_0112a862 = '\0';
  }

  // Copy global speed/scaling
  DAT_00e510d0 = DAT_00e510cc;
  DAT_0112a860 = 0;

  // Store the target/goal
  *(undefined4 *)(this + 0xd0) = param_2;

  // Apply global speed multiplier
  *(float *)(this + 0x50) = DAT_00e51104 * DAT_00e445c8;  // speed = frameTime * speedScale

  // Accumulated offset from global
  *(float *)(this + 0xe0) = DAT_0112a870;

  // Get current camera world transform (4x4 matrix)
  float *rawMatrix = (float *)FUN_00471610();  // returns 16 floats
  local_90 = rawMatrix[0];
  uStack_8c = rawMatrix[1];
  uStack_88 = rawMatrix[2];
  uStack_84 = rawMatrix[3];
  local_80 = rawMatrix[4];
  uStack_7c = rawMatrix[5];
  uStack_78 = rawMatrix[6];
  uStack_74 = rawMatrix[7];
  local_70 = rawMatrix[8];
  uStack_6c = rawMatrix[9];
  uStack_68 = rawMatrix[10];
  uStack_64 = rawMatrix[11];
  local_60 = rawMatrix[12];
  fStack_5c = *(float *)(this + 0xe0) + (float)rawMatrix[13];

  if (isReset == '\0') {
    // Non-reset path: interpolate towards target
    int listBase = *(int *)(DAT_012233a0 + 4);  // some global array
    int index = *(int *)(this + 0xd4);          // index into list
    int itemPtr = *(int *)(listBase + index * 4);

    bool foundBoneType2 = false;
    if (itemPtr == 0) {
      itemPtr = 0;
    } else {
      itemPtr = itemPtr + -0x1f30;  // adjust offset
    }

    undefined4 uVar1 = *(undefined4 *)(&DAT_00002494 + itemPtr);

    bool firstIter = false;
    int iteratorState = 0;
    int maxCount = 0;
    int *iteratorPtr = (int *)0x0;

    do {
      int funcRet = FUN_00424c90(uVar1);  // check type?
      if (funcRet == 4) goto LAB_006d224d;
      if (firstIter) {
        iteratorState = FUN_00425030(uVar1, &iteratorPtr, &iteratorState);
        if (maxCount == iteratorState) goto LAB_006d224d;
      } else {
        iteratorState = FUN_00425030(uVar1, &iteratorPtr, 0);
        firstIter = true;
        maxCount = iteratorState;
      }
    } while ((iteratorPtr == (int *)0x0) ||
             (char *)(**(code **)(*iteratorPtr + 0x10))() != &DAT_00e078fa);

    if (iteratorPtr[0x52] == 2) {  // bone type 2?
      foundBoneType2 = true;
    }

LAB_006d224d:
    // Get target offsets from param_2
    float *targetOffset = (float *)FUN_00425060(&local_a0, param_2);
    *(undefined4 *)(this + 0x40) = targetOffset[0];
    *(undefined4 *)(this + 0x44) = targetOffset[1];
    float fVar12 = _DAT_00d5780c;  // maybe up vector?
    *(float *)(this + 0x4c) = fVar12;
    *(undefined4 *)(this + 0x48) = targetOffset[2];

    if (foundBoneType2 && DAT_0112a8dc == _DAT_00d577a0) {
      DAT_0112a8dc = DAT_00e511bc;
    }

    // Add global offset to target
    *(float *)(this + 0x40) = DAT_0112a8dc * DAT_00e445c8 + *(float *)(this + 0x40);
    DAT_0112a8dc = 0.0;

    // Transform target offsets
    FUN_0056b8a0(*(undefined4 *)(this + 0x44), *(undefined4 *)(this + 0x40),
                 *(undefined4 *)(this + 0x48), &fStack_50);

    // Compute forward vector in local space
    local_a0 = fStack_40 * 0.0 + fStack_50 * 0.0 + _DAT_00d5780c * fStack_30;
    fStack_9c = fStack_3c * 0.0 + fStack_4c * 0.0 + _DAT_00d5780c * fStack_2c;
    fStack_98 = fStack_38 * 0.0 + fStack_48 * 0.0 + _DAT_00d5780c * fStack_28;
    fStack_94 = 0.0;

    // Get another matrix (maybe view matrix?)
    int viewMat = FUN_00471610();
    uVar1 = *(undefined4 *)(viewMat + 0x34);
    uVar2 = *(undefined4 *)(viewMat + 0x38);
    uVar3 = *(undefined4 *)(viewMat + 0x3c);
    *(undefined4 *)(this + 0x90) = *(undefined4 *)(viewMat + 0x30);
    *(undefined4 *)(this + 0x94) = uVar1;
    *(undefined4 *)(this + 0x98) = uVar2;
    *(undefined4 *)(this + 0x9c) = uVar3;

    float yPos = *(float *)(this + 0x94) + DAT_0112a870;
    *(float *)(this + 0x94) = yPos;
    yPos = yPos + DAT_00e51128;

    // Set raw rotation from matrix rows
    *(undefined4 *)(this + 0x30) = *(undefined4 *)(this + 0x90);
    *(float *)(this + 0x34) = yPos;
    *(float *)(this + 0x3c) = _DAT_00d5780c;
    *(undefined4 *)(this + 0x38) = *(undefined4 *)(this + 0x98);

    float blend = DAT_00e44564 - DAT_00e51178;
    *(float *)(this + 0x20) = blend * local_a0 + *(float *)(this + 0x30);
    *(float *)(this + 0x24) = blend * fStack_9c + *(float *)(this + 0x34);
    *(float *)(this + 0x28) = blend * fStack_98 + *(float *)(this + 0x38);
    *(float *)(this + 0x2c) = blend * fStack_94 + *(float *)(this + 0x3c);

  } else {
    // Reset path: copy from stored backup (maybe 0x70-0x7c, 0xc0-0xcc)
    FUN_006d1f00();
    *(undefined4 *)(this + 0x20) = *(undefined4 *)(this + 0x70);
    *(undefined4 *)(this + 0x24) = *(undefined4 *)(this + 0x74);
    *(undefined4 *)(this + 0x28) = *(undefined4 *)(this + 0x78);
    *(undefined4 *)(this + 0x2c) = *(undefined4 *)(this + 0x7c);
    *(undefined4 *)(this + 0x30) = *(undefined4 *)(this + 0xc0);
    *(undefined4 *)(this + 0x34) = *(undefined4 *)(this + 0xc4);
    *(undefined4 *)(this + 0x38) = *(undefined4 *)(this + 200);
    *(undefined4 *)(this + 0x3c) = *(undefined4 *)(this + 0xcc);
  }

  float diff_x = *(float *)(this + 0x20) - _DAT_0112a850;
  float diff_y = *(float *)(this + 0x24) - fRam0112a854;
  float diff_z = *(float *)(this + 0x28) - fRam0112a858;
  float diff_w = *(float *)(this + 0x2c) - fRam0112a85c;

  // If close enough to a global target and flag set, snap to global target
  if ((SQRT(diff_y * diff_y + diff_z * diff_z + diff_x * diff_x) < DAT_00e446f4) &&
     (DAT_0112a861 != '\0')) {
    *(float *)(this + 0x20) = _DAT_0112a850;
    *(float *)(this + 0x24) = fRam0112a854;
    *(float *)(this + 0x28) = fRam0112a858;
    *(float *)(this + 0x2c) = fRam0112a85c;
    *(undefined4 *)(this + 0x30) = _DAT_0112a840;
    *(undefined4 *)(this + 0x34) = uRam0112a844;
    *(undefined4 *)(this + 0x38) = uRam0112a848;
    *(undefined4 *)(this + 0x3c) = uRam0112a84c;
  }

  DAT_0112a861 = 0;

  // Call function pointer at this+0xd8, passing position and rotation, store result in output matrix
  (**(code **)(**(undefined4 **)(this + 0xd8)))(&local_a0, (undefined4 *)(this + 0x30), &local_60);
  *(undefined4 *)(this + 0xb0) = uStack_6c;
  *(undefined4 *)(this + 0xb4) = uStack_68;
  *(undefined4 *)(this + 0xb8) = uStack_64;
  *(undefined4 *)(this + 0xbc) = local_60;

  return;
}