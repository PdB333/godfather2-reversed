// FUN_NAME: ParticleManager::setAllParticlesActive
void __thiscall ParticleManager::setAllParticlesActive(bool enabled)
{
  int particleArrayStart;  // Pointer to first particle struct in list
  int particleArrayEnd;    // End pointer (start + count * 0xB0)
  uint particleFlags;      // Flags at offset +0x08 within each 0xB0-byte particle
  byte currentEnabledBit;  // Bit 0 of this->bEnabledAll (offset 0xB2)

  // Check if the requested state is different from the current stored state (bit 0 of byte at +0xB2)
  currentEnabledBit = *(byte *)(this + 0xB2) & 1;
  if (enabled != currentEnabledBit) {
    // Dereference: this->particleListManager (at +0xA0) -> then read array start at +0x50 and count at +0x34
    particleArrayStart = *(int *)(*(int *)(this + 0xA0) + 0x50);
    particleArrayEnd = *(int *)(*(int *)(this + 0xA0) + 0x34) * 0xB0 + particleArrayStart;

    // Iterate over each particle structure (stride = 0xB0 bytes)
    for (particleArrayStart; particleArrayStart != particleArrayEnd; particleArrayStart += 0xB0) {
      if (enabled == false) {
        // Clear bit 1 (value 0x02) – e.g., "active" flag
        *(uint *)(particleArrayStart + 8) &= 0xFFFFFFFD;
      } else {
        // Set bit 1 (value 0x02) – e.g., "active" flag
        *(uint *)(particleArrayStart + 8) |= 2;
      }
    }

    // Update the cached enabled state in this->bEnabledAll (offset 0xB2)
    *(byte *)(this + 0xB2) =
      *(byte *)(this + 0xB2) ^ (*(byte *)(this + 0xB2) ^ (byte)enabled) & 1;
  }
}