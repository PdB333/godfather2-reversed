// FUNC_NAME: Entity::isInZoneRange
uint __thiscall Entity::isInZoneRange(Entity *this, ZoneParams *zone)
{
  float diffX;
  float diffY;
  float diffZ;
  float distSq;
  float rangeMin;
  float rangeMax;
  float scaledRange;

  // +0x0C: flags field, bit0 = disabled?
  if ((this->flags & 1) != 0) {
    // Early exit, returning 0 (in_EAX & 0xFFFFFF00 is likely a decompiler artifact)
    return 0;
  }

  void *target = getTargetPosition(); // FUN_00471610 returns global position provider
  // Target position at target+0x30,0x34,0x38
  diffX = *(float *)(target + 0x30) - *(float *)(zone + 0x0C); // zone->posX
  diffY = *(float *)(target + 0x34) - *(float *)(zone + 0x10); // zone->posY
  diffZ = *(float *)(target + 0x38) - *(float *)(zone + 0x14); // zone->posZ

  // +0x1C: distance scale factor (int converted to float)
  float rawScale = (float)*(int *)(zone + 0x1C);
  if (*(int *)(zone + 0x1C) < 0) {
    rawScale = rawScale + DAT_00e44578; // Adjust for negative? Likely float constant (e.g., 2.0f PI)
  }

  float globalRange = (float)DAT_00e5175c; // Global max range scaling
  if (DAT_00e5175c < 0) {
    globalRange = globalRange + DAT_00e44578;
  }

  // +0x18: zone type index (2 bytes per entry in min/max arrays)
  int zoneType = *(int *)(zone + 0x18);
  rangeMin = (float)(&DAT_0112aca0)[zoneType * 2]; // Minimum distance for this zone type
  rangeMax = (float)(&DAT_0112aca4)[zoneType * 2]; // Maximum distance for this zone type

  // Linear interpolation based on rawScale and globalRange
  scaledRange = (rawScale * (rangeMax - rangeMin)) / globalRange + rangeMin;

  distSq = diffZ * diffZ + diffY * diffY + diffX * diffX;
  if (distSq < scaledRange * scaledRange) {
    return 1;
  }
  return 0;
}