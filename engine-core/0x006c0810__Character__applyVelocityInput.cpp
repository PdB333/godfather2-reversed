// FUNC_NAME: Character::applyVelocityInput
void __thiscall Character::applyVelocityInput(float *inputVec) {
  float speedMultiplier;
  float scaledX, scaledY, scaledZ;
  float clampedY;

  // Determine speed multiplier based on running flag at +0x3A
  if (*(bool *)(this + 0x3A)) {
    speedMultiplier = g_fRunSpeed;       // 0x00d5eea0
  } else {
    speedMultiplier = g_fWalkSpeed;       // 0x00d5780c
  }

  // Scale input vector
  scaledX = inputVec[0] * speedMultiplier;
  scaledY = inputVec[1] * speedMultiplier;
  scaledZ = inputVec[2] * speedMultiplier;

  // If vertical clamp threshold is positive, clamp Y component
  if (g_fYClampMax > 0.0f) {             // 0x0112a6f4
    float lowerBound = g_fYClampUpper - g_fYClampMax; // 0x00e44564 - 0x0112a6f4
    // Clamp scaledY to [lowerBound, g_fYClampMax]
    if (scaledY < lowerBound) {
      clampedY = lowerBound;
    } else if (scaledY > g_fYClampMax) {
      clampedY = g_fYClampMax;
    } else {
      clampedY = scaledY;
    }

    // Only store if resulting vector has non‑zero length
    float vec[3] = {scaledX, clampedY, scaledZ};
    if (mathUtils::vectorLengthSquared(vec) > 0.0f) {
      *(float *)(this + 0x40) = scaledX;
      *(float *)(this + 0x44) = clampedY;
      *(float *)(this + 0x48) = scaledZ;
    }
  } else {
    // No clamping – store scaled vector directly
    *(float *)(this + 0x40) = scaledX;
    *(float *)(this + 0x44) = scaledY;
    *(float *)(this + 0x48) = scaledZ;
  }
}