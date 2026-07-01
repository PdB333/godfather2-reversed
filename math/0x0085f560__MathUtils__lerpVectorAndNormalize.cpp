// FUNC_NAME: MathUtils::lerpVectorAndNormalize
void MathUtils::lerpVectorAndNormalize(float *result, float *from, float *to, float t, float *outNormalized)
{
  float diffX = *to - *from;
  float diffY = to[1] - from[1];
  float diffZ = to[2] - from[2];
  
  // Compute lerp: result = from + t * (to - from)
  // Then normalize the result vector
  FUN_004a10f0(result, &diffX, &DAT_00d75690); // likely normalize(lerp(from, to, t))
}