// FUN_008529a0: SoundZone::processSoundSource
// Address: 0x008529a0
// Role: Distance-based volume scaling for sound sources within a zone
// Parameters:
//   - this (ECX): Pointer to SoundZone object (offsets: +0x50 maxDistSq, +0x54 volumeMultiplier)
//   - soundSource (stack): Pointer to sound source (offsets: +0x14,+0x18,+0x1c position, +0x2c currentVolume)
// Calls FUN_00471610 to get listener transform (likely camera/player position at +0x30,+0x34,+0x38)

void __thiscall SoundZone::processSoundSource(SoundSource* soundSource)
{
    // Retrieve listener position from global singleton (e.g., CameraManager or Player)
    void* listenerTransform = FUN_00471610(); // +0x30 position
    float listenerX = *(float*)(listenerTransform + 0x30);
    float listenerY = *(float*)(listenerTransform + 0x34);
    float listenerZ = *(float*)(listenerTransform + 0x38);

    // Calculate vector from sound source to listener
    float dx = listenerX - *(float*)(soundSource + 0x14); // source position X
    float dy = listenerY - *(float*)(soundSource + 0x18); // source position Y
    float dz = listenerZ - *(float*)(soundSource + 0x1c); // source position Z

    // Squared distance
    float distSq = dx*dx + dy*dy + dz*dz;

    // If source is within the zone's max distance (squared), apply volume multiplier
    if (distSq <= *(float*)(this + 0x50)) { // SoundZone::maxDistanceSq
        *(float*)(soundSource + 0x2c) *= *(float*)(this + 0x54); // multiply current volume by zone's volumeMultiplier
    }
}