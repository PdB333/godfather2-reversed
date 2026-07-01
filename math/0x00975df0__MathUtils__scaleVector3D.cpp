// FUNC_NAME: MathUtils::scaleVector3D
void __fastcall MathUtils::scaleVector3D(float *outVec, float *inVec, float scale)
{
  float y = inVec[1]; // +0x04
  float z = inVec[2]; // +0x08
  float w = inVec[3]; // +0x0C (homogeneous component)
  float outW = outVec[3]; // preserve original w component

  outVec[0] = scale * inVec[0]; // +0x00
  outVec[1] = scale * y;        // +0x04
  outVec[2] = scale * z;        // +0x08
  outVec[3] = scale * w;        // +0x0C
  outVec[3] = outW;             // restore original w (homogeneous coordinate preservation)
}