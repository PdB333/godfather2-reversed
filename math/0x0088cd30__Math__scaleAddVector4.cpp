// FUNC_NAME: Math::scaleAddVector4
void __fastcall Math::scaleAddVector4(float *result, float *vecA, float *vecB, float scale)
{
  float ax, ay, az, aw;
  float bx, by, bz, bw;

  ax = vecA[1];
  ay = vecA[2];
  az = vecA[3];
  aw = result[3];           // +0x0C: store original W component of result before overwriting
  bx = vecB[1];
  by = vecB[2];
  bz = vecB[3];

  *result = scale * *vecA + *vecB;          // result.x = scale * vecA.x + vecB.x
  result[1] = scale * ax + bx;               // result.y = scale * vecA.y + vecB.y
  result[2] = scale * ay + by;               // result.z = scale * vecA.z + vecB.z
  result[3] = scale * az + bz;               // result.w = scale * vecA.w + vecB.w
  result[3] = aw;                            // restore original W component (preserve homogeneous coord)
}