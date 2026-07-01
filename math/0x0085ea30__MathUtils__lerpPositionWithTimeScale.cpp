// FUNC_NAME: MathUtils::lerpPositionWithTimeScale
void MathUtils::lerpPositionWithTimeScale(float deltaTime, float timeScale)
{
  bool bVar1;
  float *unaff_ESI; // this (source position)
  float *unaff_EDI; // destination position
  double dVar2;
  double dVar3;
  
  bVar1 = timeScale != _DAT_00d577a0; // check if timeScale is not zero (global zero constant)
  unaff_EDI[1] = unaff_ESI[1]; // copy Y component directly (no interpolation on Y)
  if (bVar1) {
    dVar2 = (double)deltaTime;
    FUN_00b99e20(); // likely some math helper (e.g., sin/cos or clamp)
    dVar3 = (double)deltaTime;
    *unaff_EDI = *unaff_ESI - (float)dVar2 * timeScale; // interpolate X: source - delta * timeScale
    FUN_00b99fcb(); // likely another math helper
    unaff_EDI[2] = (float)dVar3 * timeScale + unaff_ESI[2]; // interpolate Z: source + delta * timeScale
    return;
  }
  *unaff_EDI = *unaff_ESI; // no time scale: copy X directly
  unaff_EDI[2] = unaff_ESI[2]; // copy Z directly
  return;
}