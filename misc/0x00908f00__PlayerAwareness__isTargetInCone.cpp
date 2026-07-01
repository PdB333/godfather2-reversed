// FUNC_NAME: PlayerAwareness::isTargetInCone
undefined1 __thiscall isTargetInCone(int this, float *targetPos, float *facingDir, int sentientObj)
{
  float deltaX, deltaY, deltaZ;
  float dotProduct;
  
  // Vector from sentient position to target position
  deltaX = *(float *)(sentientObj + 0xb4) - targetPos[0]; // +0xB4 = position x
  deltaY = *(float *)(sentientObj + 0xb8) - targetPos[1]; // +0xB8 = position y
  deltaZ = *(float *)(sentientObj + 0xbc) - targetPos[2]; // +0xBC = position z
  
  // Project delta onto facing direction to get distance along facing axis
  dotProduct = facingDir[1] * deltaY + facingDir[0] * deltaX + facingDir[2] * deltaZ;
  
  dotProduct = dotProduct * dotProduct;
  
  // Check if dot product (squared) is within maxDot (e.g., cos(angle)^2 * dist^2)
  // And squared distance to target minus squared forward distance <= maxLateralDistSq
  if ((dotProduct <= *(float *)(this + 0xb8)) && // +0xB8 = awareness cone max forward distance squared
     ((deltaY * deltaY + deltaX * deltaX + deltaZ * deltaZ) - dotProduct <= *(float *)(this + 0xbc))) { // +0xBC = max lateral offset squared
    return 1; // Target is within cone
  }
  return 0; // Target is outside cone
}