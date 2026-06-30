// FUNC_NAME: Matrix4x4::transformVectorAndNormalize
void Matrix4x4::transformVectorAndNormalize(float *mat, float *inVec, float *outVec)
{
  float temp[4];
  float normVec[3]; // only 3 components used for normalization

  // Compute translation and subtract from input vector? Looks like a view/transform operation
  float tx = DAT_00e44564 - mat[0];   // Some global constant (might be 0.0 or 1.0)
  float ty = DAT_00e44564 - mat[1];
  float tz = DAT_00e44564 - mat[2];
  float tw = mat[3];                  // Unused in normalization

  // First transform: multiply matrix by input vector (using the matrix columns? Actually 
  // this looks like multiplying a 3x4 transform matrix by a vector with homogeneous w=1)
  FUN_0056cba0(mat, inVec, temp);     // temp = mat * inVec

  // Second transform: multiply matrix by the "normalized" vector? This is applying 
  // the same transformation to a vector formed from the translation offsets
  // Uses the computed offsets as a "pseudo-vector"
  FUN_0056cba0(temp, &tx, outVec);    // outVec = temp * (tx,ty,tz,tw) ??? Actually FUN_0056cba0 takes 3 args
  return;
}