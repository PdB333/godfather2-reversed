// FUNC_NAME: Entity::setMovementTarget
void __thiscall Entity::setMovementTarget(float *targetPos)
{
  float dx;
  float dz;
  float dist;

  // Clear unknown fields (possibly y components or flags)
  *(int *)(this + 0x54) = 0;
  *(int *)(this + 0x5c) = 0;

  // Compute relative offset in XZ plane (x and z)
  dx = *targetPos - *(float *)(this + 0x30);          // +0x30: m_positionX
  dz = targetPos[2] - *(float *)(this + 0x38);        // +0x38: m_positionZ

  dist = SQRT(dz * dz + dx * dx);
  if (0.0 < dist) {
    // Normalize and scale by global speed factor (g_movementSpeed at 0x00d5780c)
    float invDist = g_movementSpeed / dist;
    *(float *)(this + 0x50) = invDist * dx;           // +0x50: m_velocityX
    *(float *)(this + 0x58) = invDist * dz;           // +0x58: m_velocityZ
  }
}