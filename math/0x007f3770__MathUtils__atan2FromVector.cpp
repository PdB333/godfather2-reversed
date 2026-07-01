// FUNC_NAME: MathUtils::atan2FromVector
float MathUtils::atan2FromVector(float *vec) {
  float fVar1;
  
  if (((float)((uint)*vec & DAT_00e44680) < DAT_00d5ef84) &&
     ((float)((uint)vec[2] & DAT_00e44680) < DAT_00d5ef84)) {
    return 0.0f;
  }
  fVar1 = fpatan((float10)*vec, (float10)vec[2]); // atan2(y, x) - note: param_1[2] is z component, but used as x in atan2
  return fVar1;
}