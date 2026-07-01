// FUNC_NAME: renderQuadFromScreenCoords
void renderQuadFromScreenCoords(float *inputVerts, float *outputVerts, float aspectRatio)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = inputVerts[2];  // input z
  fVar2 = *inputVerts;     // input x
  // Normalize by dividing magnitude by aspect ratio
  aspectRatio = SQRT(fVar1 * fVar1 + fVar2 * fVar2) / aspectRatio;
  // Scale factor from global and some horizontal FOV adjustment
  fVar3 = _DAT_00d5780c / aspectRatio;  // +0x780c - some scale constant
  // Compute vertical offset with FOV correction
  fVar4 = DAT_00e44564 -  // +0x4564 - vertical FOV center
          (aspectRatio - (inputVerts[1] * fVar3 * _DAT_00d74f54 + aspectRatio * _DAT_00d5c458)) * DAT_00e4499c; // +0x4f54, +0x4c458, +0x499c - FOV/zoom parameters
  // Output normalized screen coordinates
  outputVerts[2] = fVar3 * fVar1;  // output z
  *outputVerts = fVar3 * fVar2;    // output x
  outputVerts[1] = fVar4;          // output y
  outputVerts[3] = 0.0;            // w = 0
  return;
}