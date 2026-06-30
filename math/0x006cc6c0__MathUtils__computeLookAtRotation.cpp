// FUNC_NAME: MathUtils::computeLookAtRotation
void MathUtils::computeLookAtRotation(float *fromPos, float *toPos, float upY, undefined4 *outQuat)
{
  float deltaX;
  float deltaZ;
  float local_50;
  undefined4 local_4c;
  float local_48;
  undefined4 local_44;
  float local_40 [3];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_20 [28];
  
  deltaX = *toPos - *fromPos;
  deltaZ = toPos[2] - fromPos[2];
  // Check if distance is below threshold (DAT_00d5f168)
  if (SQRT(deltaZ * deltaZ + deltaX * deltaX) < DAT_00d5f168) {
    *outQuat = _DAT_00d5780c; // identity quaternion
    outQuat[1] = 0;
    outQuat[2] = 0;
    return;
  }
  local_4c = 0;
  local_44 = 0;
  // Normalize the horizontal direction vector
  FUN_0056afa0(&deltaX, &deltaX);
  // Build rotation from horizontal direction and up vector
  FUN_0056d2c0(deltaX, local_4c, deltaZ, upY, local_20);
  local_40[0] = deltaZ;
  local_40[1] = 0.0;
  local_40[2] = DAT_00e44564 - deltaX; // 90-degree offset?
  local_34 = _DAT_00d5780c;
  // Convert to quaternion
  FUN_0056ce80(local_20, local_40, &local_30);
  *outQuat = local_30;
  outQuat[1] = local_2c;
  outQuat[2] = local_28;
  return;
}