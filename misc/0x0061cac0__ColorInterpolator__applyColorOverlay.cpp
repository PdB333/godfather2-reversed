// FUNC_NAME: ColorInterpolator::applyColorOverlay
void __thiscall ColorInterpolator::applyColorOverlay(float *colorOut, float blendFactor)
{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte *colorIn;
  float fVar4;
  
  bVar1 = colorIn[1];
  bVar2 = colorIn[2];
  bVar3 = colorIn[3];
  fVar4 = (float)*colorIn * blendFactor * DAT_00e44640 * DAT_00e44640;
  *colorOut = fVar4 * (float)*colorIn + *colorOut;
  colorOut[1] = fVar4 * (float)bVar1 + colorOut[1];
  colorOut[2] = fVar4 * (float)bVar2 + colorOut[2];
  colorOut[3] = fVar4 * (float)bVar3 + colorOut[3];
  return;
}