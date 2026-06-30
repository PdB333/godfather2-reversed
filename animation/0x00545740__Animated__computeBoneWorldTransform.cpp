// FUNC_NAME: Animated::computeBoneWorldTransform

/**
 * Function at 0x00545740
 * Role: Computes the world transform (4x4 matrix) for a given bone index.
 * Returns the matrix in outTransform (16 floats). Only rows 0, 1, 2 diagonal and row 3 (translation) are set.
 */
void __thiscall Animated::computeBoneWorldTransform(void *this, int boneIndex, float *outTransform)
{
  // Check if the animation system is ready
  bool isReady = (**(code **)(*(int *)this + 0x19c))();  // vtable offset 0x19c -> isAnimationReady or similar
  if (!isReady) {
    // Default: identity matrix with no translation
    outTransform[0] = DAT_00e2b1a4;   // likely 1.0f
    outTransform[5] = DAT_00e2b1a4;   // likely 1.0f
    outTransform[10] = DAT_00e2b1a4;  // likely 1.0f
    outTransform[12] = 0.0f;
    outTransform[13] = 0.0f;
    outTransform[14] = 0.0f;
    outTransform[15] = 0.0f;
    return;
  }

  // Retrieve bone data structure (size 0xC0 per bone)
  int boneDataBase = *(int *)(*(int *)((char *)this + 0xd8) + 0x48);  // +0x48 offset from skeleton data
  int boneData = boneDataBase + boneIndex * 0xc0;

  // Update local bone rotation (quaternion) using angular velocity and time delta
  // FUN_00aa36a0 integrates angular velocity
  FUN_00aa36a0(boneData + 0x70, DAT_00e44564 - *(float *)(boneData + 0xa4));  // offset 0x70: angular velocity? 0xa4: something

  // Extract current local rotation quaternion (Q_bone)
  float qx = *(float *)(boneData + 0x90);
  float qy = *(float *)(boneData + 0x94);
  float qz = *(float *)(boneData + 0x98);
  float qw = *(float *)(boneData + 0x9c);

  // Compose with parent transform? The product below seems to do quaternion multiplication with parent's rotation
  // The parent's rotation is passed via fStack_30, fStack_2c, fStack_28, fStack_24 (probably set before call)
  // Since they are uninitialized in this scope, they must be from the calling context? But the function is standalone.
  // Actually, these stack locals are not set before use – that's likely a misrepresentation by Ghidra.
  // Possibly the function receives additional implicit parameters or uses global state.
  // For reconstruction, we'll assume they represent the parent's rotation quaternion.
  // The multiplication: product = Q_bone * Q_parent (or parent * bone?)
  // The code:
  // fStack_20 = qx * parentRotation.s + qw * parentRotation.x + (qy * parentRotation.z - qz * parentRotation.y)
  // etc. That's exactly quaternion multiplication formula: Q_bone * Q_parent = (qw*parentRot.x + qx*parentRot.w + qy*parentRot.z - qz*parentRot.y, ...)
  // Important: the output quaternion is stored in fStack_20..fStack_14.

  // But the parent rotation is not in the function signature. This is a bug in Ghidra's decompilation because those stack variables are not defined.
  // They must be passed as parameters or derived from this. Most likely this function is part of a matrix stack and the parent transform is stored elsewhere.
  // To make the code compile, we'll assume we get parent Quaternion from a member or global.
  // However, the caller would have set those before the call. Since we don't have that, we note it's incomplete.

  // Normalize the resulting quaternion
  FUN_00aa5450(&fStack_20);  // in-place normalization

  // Get another object for interpolation base (animation state machine?)
  int animState = (**(code **)(*(int *)this + 0x230))();  // vtable offset 0x230 -> getAnimationState or similar
  float *interpBase = (float *)(*(int *)(animState + 8) + boneIndex * 0x30);  // each bone has 12 floats (3x4 matrix?) Actually 0x30 = 12 floats
  float interpFactor = *(float *)(boneData + 0x50);  // interpolation blend factor

  // Check global comparison threshold (likely stored in DAT_00e2b05c)
  if (DAT_00e2b05c < interpFactor) {
    // Interpolate between two sets of translation components
    outTransform[12] = interpBase[0] + interpFactor * interpBase[4];
    outTransform[13] = interpBase[1] + interpFactor * interpBase[5];
    outTransform[14] = interpBase[2] + interpFactor * interpBase[6];
    outTransform[15] = interpBase[3] + interpFactor * interpBase[7];
  } else {
    // Use base translation
    outTransform[12] = interpBase[0];
    outTransform[13] = interpBase[1];
    outTransform[14] = interpBase[2];
    outTransform[15] = interpBase[3];
  }

  // Note: the rotation part (columns 0-2) is not set in this function.
  // The actual matrix is likely assembled elsewhere, possibly using the computed quaternion from fStack_20..fStack_14.
}