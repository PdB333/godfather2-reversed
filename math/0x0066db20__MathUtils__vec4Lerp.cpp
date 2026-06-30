// FUNC_NAME: MathUtils::vec4Lerp
void __fastcall MathUtils::vec4Lerp(float *result, float *a, float *b, float t)
{
  // Linear interpolation between two 4D vectors: result = a * t + b
  // Note: The last component (index 3) is NOT interpolated; it keeps its original value from a.
  // This is likely used for quaternion interpolation where w is handled differently,
  // or for vector interpolation where w represents a separate parameter (e.g., homogeneous coordinate).
  
  float ax = a[0];
  float ay = a[1];
  float az = a[2];
  float aw = a[3];
  
  float bx = b[0];
  float by = b[1];
  float bz = b[2];
  float bw = b[3];
  
  result[0] = t * ax + bx;
  result[1] = t * ay + by;
  result[2] = t * az + bz;
  result[3] = t * aw + bw;
  result[3] = aw; // Override w with original value from a (no interpolation)
}