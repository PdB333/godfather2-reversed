// FUNC_NAME: ColorAdjustment::computeClampedComponents
undefined4 __thiscall ColorAdjustment::computeClampedComponents(ColorAdjustment *this)
{
  float fVar1;
  bool bVar2;
  float fVar3;
  float *pfVar4;
  undefined3 uVar5;
  float *pfVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float local_c[3];
  
  // Constants; likely range limits and scaling factors
  float rangeMax = DAT_00d5ccf8;          // e.g., 1.0 or 255.0
  float rangeMin = _DAT_00d5780c;        // e.g., 0.0
  float scaleA = _DAT_00d6bad8;          // multiplier for field at +0x20
  float scaleB = _DAT_00d6bad4;          // multiplier for field at +0x1c
  float threshold = _DAT_00d6bad0;       // some threshold for branch
  float adjustmentConst1 = DAT_00e44720; // constant for fallback
  float adjustmentConst2 = DAT_00e448f0; // used in interpolation
  float adjustmentConst3 = DAT_00e448f4; // used in another branch
  float interpolationScale = DAT_00d5ef9c; // scale factor for interpolation
  float upperBound = DAT_00d5f4b4;       // final clamping upper bound
  
  // First median clamp: compute clamped value for field at +0x20
  local_c[0] = *(float *)(this + 0x20) * scaleA;
  local_c[1] = rangeMin;
  local_c[2] = rangeMax;
  if (local_c[0] <= rangeMin) {
    pfVar4 = local_c + 2;
    if (rangeMax <= local_c[0]) {
      pfVar4 = local_c;
    }
  } else {
    pfVar4 = local_c + 1;
  }
  fVar1 = *pfVar4;  // median of {inputA*scaleA, min, max}
  *(float *)(this + 0x50) = fVar1;  // stored as clamped channel A

  // Second median clamp: for field at +0x1c
  local_c[0] = *(float *)(this + 0x1c) * scaleB;
  local_c[2] = rangeMin;
  local_c[1] = rangeMax;
  if (local_c[0] <= rangeMin) {
    pfVar4 = local_c + 1;
    if (rangeMax <= local_c[0]) {
      pfVar4 = local_c;
    }
  } else {
    pfVar4 = local_c + 2;
  }
  fVar7 = *pfVar4;  // median of {inputB*scaleB, min, max}
  bVar2 = local_c[0] == fVar7;  // flag if direct equal

  // Convert floats to integer bit pattern, mask with constant (maybe extract exponent/sign?)
  fVar9 = (float)((uint)fVar1 & DAT_00e44680);
  fVar8 = (float)((uint)fVar7 & DAT_00e44680);
  fVar10 = fVar8;
  if (fVar8 <= fVar9) {
    fVar10 = fVar9;
  }
  *(float *)(this + 0x28) = fVar10;  // store max of masked values

  if (fVar10 <= threshold) {
    // If masked value is below threshold, use a predefined constant
    *(float *)(this + 0x2c) = adjustmentConst1;
    return CONCAT31(CONCAT21((short)((uint)pfVar4 >> 0x10),
                             bVar2 << 6 | (NAN(local_c[0]) || NAN(fVar7)) << 2 | 2U |
                             local_c[0] < fVar7), bVar2);
  }

  // Interpolation based on comparison of fVar1 and fVar8
  if (fVar1 < fVar8) {
    if (DAT_00e44564 - fVar8 < fVar1) {
      if (fVar9 <= fVar7) {
        *(float *)(this + 0x2c) = (fVar1 / fVar10) * interpolationScale + adjustmentConst2;
        goto LAB_007ac926;
      }
      fVar7 = interpolationScale - (fVar1 / fVar10) * interpolationScale;
    } else {
      fVar7 = (fVar7 / fVar10) * interpolationScale + adjustmentConst1;
    }
    *(float *)(this + 0x2c) = fVar7;
  } else {
    *(float *)(this + 0x2c) = adjustmentConst3 - (fVar7 / fVar10) * interpolationScale;
  }

LAB_007ac926:
  // Clamp final result to [0, upperBound]
  pfVar4 = (float *)(this + 0x2c);
  local_c[2] = upperBound;
  local_c[1] = 0.0;
  uVar5 = (undefined3)((uint)pfVar4 >> 8);
  if (upperBound < *pfVar4) {
    *pfVar4 = upperBound;
    return CONCAT31(uVar5, bVar2);
  }
  pfVar6 = local_c + 1;
  if (0.0 <= *pfVar4) {
    pfVar6 = pfVar4;
  }
  *pfVar4 = *pfVar6;
  return CONCAT31(uVar5, bVar2);
}