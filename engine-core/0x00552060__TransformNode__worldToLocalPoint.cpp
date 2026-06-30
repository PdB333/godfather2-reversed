// FUNC_NAME: TransformNode::worldToLocalPoint
void __thiscall TransformNode::worldToLocalPoint(int this, float *worldPos, float *localPos)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  // Get rotation matrix columns from object (likely a 3x3 rotation matrix stored at +0x1b0, +0x1b4, +0x1b8)
  fVar2 = *(float *)(this + 0x1b0); // rotation column 0
  fVar4 = *worldPos - *(float *)(this + 0x130); // worldPos.x - translation.x
  fVar6 = worldPos[2] - *(float *)(this + 0x138); // worldPos.z - translation.z
  fVar5 = worldPos[1] - *(float *)(this + 0x134); // worldPos.y - translation.y
  
  // Compute cross product components for rotation
  fVar3 = *(float *)(this + 0x1b8) * fVar4 - fVar2 * fVar6; // rotation column 2 * dx - rotation column 0 * dz
  fVar1 = *(float *)(this + 0x1b4); // rotation column 1
  
  // Transform world point to local space using inverse rotation
  *localPos = fVar1 * fVar6 - *(float *)(this + 0x1b8) * fVar5; // localPos.x = rotation col1 * dz - rotation col2 * dy
  localPos[3] = 0.0; // w component (homogeneous coordinate)
  localPos[1] = fVar3; // localPos.y = rotation col2 * dx - rotation col0 * dz
  fVar2 = fVar2 * fVar5 - fVar1 * fVar4; // localPos.z = rotation col0 * dy - rotation col1 * dx
  localPos[2] = fVar2;
  
  // Add translation offset (object's world position)
  *localPos = *localPos + *(float *)(this + 0x1a0); // localPos.x += translation.x
  localPos[1] = *(float *)(this + 0x1a4) + fVar3; // localPos.y += translation.y
  localPos[2] = *(float *)(this + 0x1a8) + fVar2; // localPos.z += translation.z
  localPos[3] = *(float *)(this + 0x1ac); // localPos.w = translation.w (usually 1.0)
}