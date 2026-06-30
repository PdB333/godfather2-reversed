// FUNC_NAME: ParticleManager::renderParticles
void ParticleManager::renderParticles(void)
{
  bool bSkipOptimization;
  char cResult;
  float fWidth;
  float fHeight;
  float *pParticleData;
  int iParticleIndex;
  
  if (DAT_00f15a1c == 0x15) { // Check if particle system is active
    cResult = FUN_0060f540(); // Check for particle optimization/skip
    bSkipOptimization = false;
    if (cResult == '\0') goto LAB_006078dd;
  }
  bSkipOptimization = true;
LAB_006078dd:
  iParticleIndex = 0;
  if (0 < DAT_00f15a6c) { // Number of active particles
    pParticleData = (float *)&DAT_01205778; // Start of particle data array (+0x0)
    do {
      if (bSkipOptimization) {
        if (*(char *)(pParticleData + -2) == '\0') { // Check particle type flag (+0x? offset)
          fWidth = pParticleData[-3]; // Direct width value
        }
        else {
          fWidth = (float)(int)((float)DAT_01205880 * *pParticleData); // Scaled width from multiplier (+0x??)
          if ((int)fWidth < 1) {
            fWidth = 1.4013e-45; // Min width (FLT_MIN)
          }
        }
        if (*(char *)(pParticleData + -2) == '\0') { // Same type check
          fHeight = pParticleData[-4]; // Direct height value
        }
        else {
          fHeight = (float)(int)((float)DAT_0120587c * pParticleData[-1]); // Scaled height from multiplier
          if ((int)fHeight < 1) {
            fHeight = 1.4013e-45; // Min height
          }
        }
      }
      else {
        fWidth = 1.4013e-45; // Default minimal size
        fHeight = 1.4013e-45; // Default minimal size
      }
      // Call render draw call with particle data (vtable+0x70 = drawQuad or similar)
      (**(code **)(*DAT_01205750 + 0x70))(DAT_01205750, fHeight, fWidth, DAT_00f15a1c, 0, 0, 0, pParticleData + 1, 0);
      iParticleIndex = iParticleIndex + 1;
      pParticleData = pParticleData + 6; // Advance to next particle (6 floats per particle)
    } while (iParticleIndex < DAT_00f15a6c);
  }
  return;
}