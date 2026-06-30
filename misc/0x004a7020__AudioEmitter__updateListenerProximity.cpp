// FUNC_NAME: AudioEmitter::updateListenerProximity

void AudioEmitter::updateListenerProximity(float *listenerPos)
{
  // param_1 is 'this' pointer (AudioEmitter*)
  // Member layout:
  // +0x00: PhysicalObject* physicalObject
  // +0x0c: float rangePairs[] (pairs of min/max distances, count at +0x4d)
  // +0x13: byte currentMask
  // +0x4d: byte rangeCount

  PhysicalObject *phys = *reinterpret_cast<PhysicalObject**>(this);        // +0x00
  float sumRadii = (phys->field_0x2c + phys->field_0x30) * DAT_0110a440; // DAT_0110a440 is global attenuation factor
  float dx = phys->position.x - listenerPos[0];                           // position at +0x20
  float dy = phys->position.y - listenerPos[1];                           // +0x24
  float dz = phys->position.z - listenerPos[2];                           // +0x28
  float distSq = dx*dx + dy*dy + dz*dz;
  float adjusted = distSq - sumRadii * sumRadii;
  if (adjusted < 0.0f) {
    adjusted = 0.0f;
  }
  float dist = __builtin_sqrtf(adjusted);   // approximated SQRT

  byte count = *reinterpret_cast<byte*>(reinterpret_cast<int>(this) + 0x4d); // +0x4d
  float *ranges = reinterpret_cast<float*>(reinterpret_cast<int>(this) + 0x0c); // +0x0c
  byte newMask = 0;
  for (uint i = 0; i < count; i++) {
    if (ranges[2*i] <= dist && dist <= ranges[2*i+1]) {
      newMask |= (1 << i);
    }
  }

  byte *currentMask = reinterpret_cast<byte*>(reinterpret_cast<int>(this) + 0x13); // +0x13
  if (*currentMask != newMask) {
    *currentMask = newMask;
    // Virtual call at +0x4c of PhysicalObject vtable
    // Event ID 0x1f32d7d5 (likely hash for "occlusion change")
    (phys->vtable->onProximityChanged)(0x1f32d7d5, dist);
  }
}