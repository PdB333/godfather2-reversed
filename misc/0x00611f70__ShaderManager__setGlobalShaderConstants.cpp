// FUNC_NAME: ShaderManager::setGlobalShaderConstants
void ShaderManager::setGlobalShaderConstants(void)

{
  // Copy 16 floats (4x4 matrix?) from source pointer (unaff_ESI) to global shader constants at 0x011f67f0
  // These are likely world/view/projection matrices or lighting parameters
  _DAT_011f67f0 = *unaff_ESI;
  uRam011f67f4 = unaff_ESI[1];
  uRam011f67f8 = unaff_ESI[2];
  uRam011f67fc = unaff_ESI[3];
  _DAT_011f6800 = unaff_ESI[4];
  uRam011f6804 = unaff_ESI[5];
  uRam011f6808 = unaff_ESI[6];
  uRam011f680c = unaff_ESI[7];
  _DAT_011f6810 = unaff_ESI[8];
  uRam011f6814 = unaff_ESI[9];
  uRam011f6818 = unaff_ESI[10];
  uRam011f681c = unaff_ESI[0xb];
  _DAT_011f6820 = unaff_ESI[0xc];
  uRam011f6824 = unaff_ESI[0xd];
  uRam011f6828 = unaff_ESI[0xe];
  uRam011f682c = unaff_ESI[0xf];

  // If there's an active effect/technique manager (DAT_012058e8)
  if (DAT_012058e8 != 0) {
    // Update vertex shader constants (if handle exists at +0x28)
    if (*(int *)(DAT_012058e8 + 0x28) != 0) {
      FUN_0060b020(*(undefined4 *)(DAT_012058e8 + 0x10),  // Effect instance (?)
                   *(int *)(DAT_012058e8 + 0x28));       // VS constant buffer handle
    }
    // Update pixel shader constants (if handle exists at +0x2c)
    if ((DAT_012058e8 != 0) && (*(int *)(DAT_012058e8 + 0x2c) != 0)) {
      FUN_0060aea0(*(undefined4 *)(DAT_012058e8 + 0x10),  // Effect instance (?)
                   *(int *)(DAT_012058e8 + 0x2c));       // PS constant buffer handle
    }
  }
  return;
}