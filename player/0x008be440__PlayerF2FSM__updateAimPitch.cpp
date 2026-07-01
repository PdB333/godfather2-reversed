// FUNC_NAME: PlayerF2FSM::updateAimPitch
void __thiscall PlayerF2FSM::updateAimPitch(int thisPtr, int deltaTimeMs)
{
  float fVar1;
  float fVar2;
  
  // Accumulate total time (likely for animation or input smoothing)
  *(int *)(thisPtr + 0x13c) = *(int *)(thisPtr + 0x13c) + deltaTimeMs;
  
  // Check if there's a weapon/aiming target object at +0x1d0
  if (*(int *)(thisPtr + 0x1d0) == 0) {
    fVar1 = 0.0;
  }
  else {
    // Get aim sensitivity from weapon object (+0x58) multiplied by aim speed modifier (+0x188)
    fVar1 = *(float *)(*(int *)(thisPtr + 0x1d0) + 0x58) * *(float *)(thisPtr + 0x188);
  }
  
  fVar2 = (float)deltaTimeMs;
  // Handle negative delta (frame time wrap-around) using a constant
  if (deltaTimeMs < 0) {
    fVar2 = fVar2 + DAT_00e44578; // 0x00e44578 is likely 0xFFFFFFFF as float or a large constant
  }
  
  // If aiming is active (+0x230 non-zero), apply recoil via FUN_00892490 (likely applyRecoil)
  if (*(int *)(thisPtr + 0x230) != 0) {
    FUN_00892490(-(fVar2 * fVar1), 6); // param 6 might be weapon index or recoil type
  }
  
  // Calculate new pitch angle (+0x104) with clamping
  fVar2 = *(float *)(thisPtr + 0x104) + -(fVar2 * fVar1);
  fVar1 = DAT_00d7bcac; // min pitch limit (likely -89 degrees or similar)
  if ((fVar2 <= DAT_00d7bcac) || (fVar1 = DAT_00d7bca8, DAT_00d7bca8 <= fVar2)) {
    fVar2 = fVar1; // Clamp to min or max
  }
  *(float *)(thisPtr + 0x104) = fVar2;
  
  return;
}