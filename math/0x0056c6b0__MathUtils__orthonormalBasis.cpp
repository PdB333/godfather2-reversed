// FUNC_NAME: MathUtils::orthonormalBasis
void MathUtils::orthonormalBasis(float *inVec, float *refVec, float *outBasis)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  // Cross product: outBasis = inVec x refVec
  fVar1 = *refVec;
  fVar2 = refVec[1];
  fVar3 = refVec[2];
  fVar7 = refVec[3];
  fVar8 = *inVec;
  fVar4 = inVec[1];
  fVar5 = inVec[2];
  fVar6 = inVec[3];
  *outBasis = fVar5 * fVar2 - fVar4 * fVar3;
  outBasis[1] = fVar8 * fVar3 - fVar5 * fVar1;
  outBasis[2] = fVar4 * fVar1 - fVar8 * fVar2;
  outBasis[3] = fVar6 * fVar7 - fVar6 * fVar7; // This is always 0 (w component)
  
  // Normalize the cross product result
  fVar1 = outBasis[1];
  fVar2 = *outBasis;
  fVar3 = outBasis[2];
  fVar7 = fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3;
  fVar8 = 0.0;
  if (fVar7 <= DAT_00e2cbe0) { // Small epsilon threshold
    fVar7 = 0.0;
  }
  else {
    fVar7 = DAT_00e2b1a4 / SQRT(fVar7); // 1.0 / length (inverse sqrt)
  }
  *outBasis = fVar2 * fVar7;
  outBasis[1] = fVar1 * fVar7;
  outBasis[2] = fVar3 * fVar7;
  
  // Second cross product: outBasis[4..7] = outBasis x inVec (to form orthonormal basis)
  fVar1 = *inVec;
  fVar2 = inVec[1];
  fVar3 = inVec[2];
  fVar7 = inVec[3];
  outBasis[4] = outBasis[2] * fVar2 - outBasis[1] * fVar3;
  outBasis[5] = *outBasis * fVar3 - outBasis[2] * fVar1;
  outBasis[6] = outBasis[1] * fVar1 - *outBasis * fVar2;
  outBasis[7] = outBasis[3] * fVar7 - outBasis[3] * fVar7; // Also always 0
  
  FUN_00414aa0(); // Likely identity matrix or zero fill for remaining components
  outBasis[0xb] = fVar8; // Set w component of third basis vector to 0
  return;
}