// FUNC_NAME: FSMatrix::copyAndTransformPoint
void FSMatrix::copyAndTransformPoint(FSMatrix *src, FSMatrix *dst)
{
  // Copy the 4x3 transformation matrix (12 float components) from src to dst
  // Offsets: 0x00-0x0B are the matrix rows (each row is 3 floats + 1 padding)
  dst->m[0][0] = src->m[0][0];
  dst->m[0][1] = src->m[0][1];
  dst->m[0][2] = src->m[0][2];
  dst->m[0][3] = src->m[0][3];
  
  dst->m[1][0] = src->m[1][0];
  dst->m[1][1] = src->m[1][1];
  dst->m[1][2] = src->m[1][2];
  dst->m[1][3] = src->m[1][3];
  
  dst->m[2][0] = src->m[2][0];
  dst->m[2][1] = src->m[2][1];
  dst->m[2][2] = src->m[2][2];
  dst->m[2][3] = src->m[2][3];
  
  // Now transform a point using the copied matrix
  // The point is stored as 4 floats: x, y, z, w (w usually 1.0)
  // DAT_00e2b1a4 appears to be a global constant (likely 0.0f or identity-related)
  float globalConst = *(float*)0x00e2b1a4;  // likely 0.0f
  
  FSVector4 point;
  point.x = 0.0f;
  point.y = 0.0f;
  point.z = 0.0f;
  point.w = globalConst;  // w component set to global constant
  
  // Second point for transform
  FSVector4 point2;
  point2.x = 0.0f;
  point2.y = 0.0f;
  point2.z = 0.0f;
  point2.w = globalConst;
  
  // Third point
  FSVector4 point3;
  point3.x = 0.0f;
  point3.y = 0.0f;
  point3.z = 0.0f;
  point3.w = globalConst;
  
  // Call transform function with the local point array
  FUN_0056c3f0(&point);  // This likely transforms the point(s) by the matrix
}