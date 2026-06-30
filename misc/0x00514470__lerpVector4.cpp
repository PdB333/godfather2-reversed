// FUNC_NAME: lerpVector4
void __thiscall lerpVector4(float *start, float t, float *result)
{
  float startY;
  float startZ;
  float startW;
  float endY;
  float endZ;
  float endW;
  float *end;

  // +0x0: x
  // +0x4: y
  // +0x8: z
  // +0xC: w
  startY = end[1];          // end.y
  startZ = end[2];          // end.z
  startW = end[3];          // end.w
  endY = start[1];          // start.y
  endZ = start[2];          // start.z
  endW = start[3];          // start.w
  result[0] = (start[0] - end[0]) * t + end[0];  // result.x = (start.x - end.x) * t + end.x
  result[1] = (endY - startY) * t + startY;      // result.y = (start.y - end.y) * t + end.y
  result[2] = (endZ - startZ) * t + startZ;      // result.z = (start.z - end.z) * t + end.z
  result[3] = (endW - startW) * t + startW;      // result.w = (start.w - end.w) * t + end.w
  return;
}