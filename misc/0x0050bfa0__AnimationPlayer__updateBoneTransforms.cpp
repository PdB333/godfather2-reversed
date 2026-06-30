// FUNC_NAME: AnimationPlayer::updateBoneTransforms
void AnimationPlayer::updateBoneTransforms(float *outMatrix, float param2, float param3)
{
  float *pfVar1;
  float *pfVar2;
  uint uVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  int iVar9;
  int unaff_ESI;
  int unaff_FS_OFFSET;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fInterpX;
  float fInterpY;
  float fInterpZ;
  float local_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  
  iVar5 = DAT_0119478c + -1;
  iVar9 = DAT_0119478c + 2;
  if (iVar5 < 0) {
    iVar5 = 0x13; // wrap around ring buffer
  }
  else if (0x13 < iVar9) {
    iVar9 = DAT_0119478c + -0x12; // wrap around ring buffer
  }
  (&DAT_01194790)[iVar5] = (&DAT_01194790)[iVar5] + (&DAT_01194790)[iVar9]; // combine noise values
  fVar12 = DAT_00e2b1a4; // ~1.0f
  uVar6 = *(uint *)(*(int *)(unaff_ESI + 0x24) + 0x108); // flags at +0x108
  uVar3 = (&DAT_01194790)[iVar5]; // noise random value
  if ((uVar6 & 8) == 0) {
    fVar10 = *(float *)(*(int *)(unaff_ESI + 0x24) + 0xd4); // base rotation X
  }
  else {
    fVar10 = ((float)(uVar3 & 0x7fffff | 0x3f800000) - DAT_00e2b1a4) *
             *(float *)(*(int *)(unaff_ESI + 0x24) + 0xd8) +
             *(float *)(*(int *)(unaff_ESI + 0x24) + 0xd4); // base rotation + noise * amplitude
  }
  if ((uVar6 & 0x20) == 0) {
    if ((uVar6 & 0x20000) == 0) {
      fInterpZ = *(float *)(unaff_ESI + 0x90); // idle z rotation
    }
    else {
      fInterpZ = *(float *)(*(int *)(unaff_ESI + 0x24) + 0xe0) * param2 +
                 *(float *)(unaff_ESI + 0x90);
    }
  }
  else {
    fVar11 = (float)((uVar3 & 0x7f) << 0x10 | uVar3 >> 0x10 | 0x3f800000) - DAT_00e2b1a4;
    if ((uVar6 & 0x10) != 0) {
      fVar11 = SQRT(fVar11);
    }
    fInterpZ = *(float *)(*(int *)(unaff_ESI + 0x24) + 0xe0) * fVar11 + *(float *)(unaff_ESI + 0x90);
  }
  DAT_0119478c = iVar5 + -1;
  iVar9 = iVar5 + 2;
  if (DAT_0119478c < 0) {
    DAT_0119478c = 0x13;
  }
  else if (0x13 < iVar9) {
    iVar9 = iVar5 + -0x12;
  }
  (&DAT_01194790)[DAT_0119478c] = (&DAT_01194790)[DAT_0119478c] + (&DAT_01194790)[iVar9];
  iVar9 = *(int *)(unaff_ESI + 0x24);
  uVar6 = *(uint *)(iVar9 + 0x10c);
  uVar3 = (&DAT_01194790)[DAT_0119478c];
  if ((uVar6 & 0x2000) == 0) {
    fInterpY = ((float)(uVar3 & 0x7fffff | 0x3f800000) - fVar12) * *(float *)(iVar9 + 0x148);
  }
  else {
    fInterpY = *(float *)(iVar9 + 0x148) * param2;
  }
  if ((*(byte *)(iVar9 + 0x108) & 0x40) == 0) {
    if ((uVar6 & 0x4000) == 0) {
      fInterpX = *(float *)(iVar9 + 0xe4); // idle X rotation
    }
    else {
      fInterpX = *(float *)(iVar9 + 0xe8) * param2 + *(float *)(iVar9 + 0xe4);
    }
  }
  else {
    fInterpX = ((float)((uVar3 & 0x7f) << 0x10 | uVar3 >> 0x10 | 0x3f800000) - fVar12) *
               *(float *)(iVar9 + 0xe8) + *(float *)(iVar9 + 0xe4);
  }
  if ((uVar6 & 0x8000) != 0) {
    fInterpY = *(float *)(iVar9 + 0x148);
    dVar15 = (double)*(float *)(iVar9 + 0xe4);
    FUN_00b99fcb(); // sin?
    dVar16 = (double)(*(float *)(iVar9 + 0xe8) + *(float *)(iVar9 + 0xe4));
    FUN_00b99fcb(); // cos?
    fVar11 = (float)dVar16 - (float)dVar15;
    fVar12 = (float)((uint)(fVar11 * fInterpY * param3) & DAT_00e44680);
    if (fVar12 <= DAT_00e44848) {
      fInterpX = 0.0;
      fInterpY = 0.0;
    }
    else {
      fVar19 = DAT_00e2b1a4 / SQRT(fVar12 + (float)PTR_FUN_00e4462c);
      fVar12 = fVar19 * fVar11 * param2;
      fVar19 = fVar19 * fInterpY * param2;
      fInterpY = (fVar12 - (float)(int)fVar12) * fInterpY;
      fVar11 = (fVar19 - (float)(int)fVar19) * fVar11 + (float)dVar15;
      fVar12 = DAT_00e2eff4;
      if ((DAT_00e2eff4 < fVar11) && (fVar12 = fVar11, DAT_00e2b1a4 <= fVar11)) {
        fVar12 = DAT_00e2b1a4;
      }
      dVar15 = (double)fVar12;
      FUN_00b9c766(); // atan?
      fInterpX = (float)dVar15;
    }
  }
  dVar15 = (double)fInterpY;
  FUN_00b99fcb(); // sin
  dVar16 = (double)fInterpY;
  FUN_00b99e20(); // cos?
  dVar17 = (double)fInterpX;
  FUN_00b99fcb(); // sin
  dVar18 = (double)fInterpX;
  FUN_00b99e20(); // cos?
  fVar12 = (float)dVar18 * fInterpZ;
  *outMatrix = fVar12 * (float)dVar16;
  outMatrix[1] = (float)dVar17 * fInterpZ;
  pfVar1 = outMatrix + 4;
  outMatrix[2] = fVar12 * (float)dVar15;
  outMatrix[3] = DAT_00e2b1a4;
  fVar11 = (float)dVar18 * fVar10;
  *pfVar1 = fVar11 * (float)dVar16;
  fVar19 = 0.0;
  outMatrix[5] = (float)dVar17 * fVar10;
  outMatrix[6] = fVar11 * (float)dVar15;
  outMatrix[7] = 0.0;
  uVar6 = *(uint *)(*(int *)(unaff_ESI + 0x24) + 0x108);
  if ((uVar6 & 0x200) != 0) {
    if ((uVar6 & 0x400) == 0) {
      uVar7 = FUN_004e9200(); // noise generator
      uVar6 = uVar7 << 8;
      uVar3 = uVar6 >> 0x18;
      iVar9 = *(int *)(unaff_ESI + 0x24);
      fVar21 = (float)(uVar7 & 0x7fffff | 0x3f800000) - fVar12;
      fInterpZ = (float)(uVar6 & 0x7fffff | uVar7 >> 0x18 | 0x3f800000) - fVar12;
      fVar11 = (float)((uVar6 & 0x7fff | uVar7 >> 0x18) << 8 | uVar3 | 0x3f800000) - fVar12;
      if ((((((*(uint *)(iVar9 + 0x10c) & 0x10000) != 0) &&
            (fVar10 = *(float *)(iVar9 + 0x84), fVar10 != fVar19)) &&
           (*(float *)(iVar9 + 0xe0) < fVar10)) &&
          ((fVar10 = *(float *)(iVar9 + 0xe0) / fVar10, fVar21 < fVar10 && (fInterpZ < fVar10)))) &&
         (fVar11 < fVar10)) {
        fVar20 = fVar12 - fVar10;
        if ((uVar3 & 1) == 0) {
          if ((uVar3 & 2) == 0) {
            fVar11 = fVar20 * fVar11 + fVar10;
          }
          else {
            fVar21 = fVar20 * fVar21 + fVar10;
          }
        }
        else {
          fInterpZ = fVar20 * fInterpZ + fVar10;
        }
      }
      uVar6 = FUN_004e9200();
      fVar21 = (float)(int)((uVar6 & 2) - 1) * fVar21;
      fInterpZ = (float)(int)((uVar6 >> 0x18 & 2) - 1) * fInterpZ;
      fVar11 = (float)(int)(((uVar6 << 8) >> 0x18 & 2) - 1) * fVar11;
      if ((*(uint *)(*(int *)(unaff_ESI + 0x24) + 0x108) & 0x20000) != 0) {
        fInterpZ = param2 * DAT_00e2b04c - fVar12;
      }
    }
    else {
      uVar6 = FUN_004e9200();
      fInterpZ = fVar12 - ((float)(uVar6 & 0x7fffff | 0x3f800000) - fVar12) * DAT_00e2b04c;
      fVar20 = SQRT(fVar12 - fInterpZ * fInterpZ);
      fVar12 = ((float)((uVar6 & 0x7f) << 0x10 | uVar6 >> 0x10 | 0x3f800000) - fVar12) *
               DAT_00e2a848;
      dVar15 = (double)fVar12;
      FUN_00b99fcb(); // sin
      fVar11 = (float)dVar15;
      dVar15 = (double)fVar12;
      FUN_00b99e20(); // cos
      iVar9 = *(int *)(unaff_ESI + 0x24);
      fVar19 = 0.0;
      fVar21 = (float)dVar15;
      if (*(float *)(iVar9 + 0x84) == 0.0) {
        fInterpZ = 0.0;
      }
      else {
        fVar21 = fVar21 * fVar20;
        fVar11 = fVar11 * fVar20;
      }
      if ((*(uint *)(iVar9 + 0x108) & 0x800) != 0) {
        fVar20 = fInterpZ;
        fVar14 = fVar21;
        fVar22 = fVar11;
        uVar6 = FUN_004e9200();
        iVar9 = *(int *)(unaff_ESI + 0x24);
        fVar12 = *(float *)(iVar9 + 0x84);
        fVar13 = (float)(uVar6 & 0x7fffff | 0x3f800000) - DAT_00e2b1a4;
        if (fVar12 == fVar19) {
          fVar13 = SQRT(fVar13);
        }
        else {
          dVar15 = (double)fVar13;
          FUN_00b9af10(); // tan?
          fVar19 = 0.0;
          fVar13 = (float)dVar15;
          fVar20 = fInterpZ;
          fVar14 = fVar21;
          fVar22 = fVar11;
        }
        if ((((*(uint *)(iVar9 + 0x10c) & 0x10000) != 0) && (fVar12 != fVar19)) &&
           ((*(float *)(iVar9 + 0xe0) < fVar12 &&
            (fVar12 = *(float *)(iVar9 + 0xe0) / fVar12, fVar13 < fVar12)))) {
          fVar13 = (DAT_00e2b1a4 - fVar12) * fVar13 + fVar12;
        }
        fVar21 = fVar13 * fVar14;
        fInterpZ = fVar13 * fVar20;
        fVar11 = fVar13 * fVar22;
      }
      if ((*(byte *)(iVar9 + 0x108) & 0x40) == 0) {
        *pfVar1 = fVar21 * fVar10;
        outMatrix[5] = fInterpZ * fVar10;
        outMatrix[6] = fVar11 * fVar10;
        outMatrix[7] = fVar19;
      }
    }
    *outMatrix = *(float *)(*(int *)(unaff_ESI + 0x24) + 0x80) * fVar21 + *outMatrix;
    outMatrix[1] = *(float *)(*(int *)(unaff_ESI + 0x24) + 0x84) * fInterpZ + outMatrix[1];
    outMatrix[2] = *(float *)(*(int *)(unaff_ESI + 0x24) + 0x88) * fVar11 + outMatrix[2];
  }
  if (((*(uint *)(*(int *)(unaff_ESI + 0x24) + 0x108) & 0x2000) == 0) ||
     (*(int *)(*(int *)(unaff_ESI + 4) + 0xb0) != 4)) {
    iVar9 = *(int *)(unaff_ESI + 0xa0);
    if (iVar9 == 0) goto LAB_0050c803;
    iVar5 = *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8);
    fVar12 = *(float *)(iVar5 + 0x2c + iVar9);
    fVar10 = *(float *)(iVar5 + 0x28 + iVar9);
    fVar11 = fVar12 - fVar10;
    if (fVar11 < fVar19) {
      fVar11 = fVar19;
      fVar10 = fVar12;
    }
    if ((*(uint *)(*(int *)(unaff_ESI + 0x24) + 0x108) & 0x20000) == 0) {
      FUN_004e41b0(); // randomize?
      param2 = fVar12;
    }
    cVar4 = FUN_00519540(param2 * fVar10 + fVar11);
    if (cVar4 == '\\0') goto LAB_0050c803;
  }
  else {
    FUN_00537020(*(undefined2 *)(unaff_ESI + 0x5e)); // play sound?
  }
  fVar12 = outMatrix[3];
  *outMatrix = *outMatrix + local_30;
  outMatrix[1] = outMatrix[1] + fStack_2c;
  outMatrix[2] = outMatrix[2] + fStack_28;
  outMatrix[3] = outMatrix[3] + fStack_24;
  outMatrix[3] = fVar12;
LAB_0050c803:
  iVar9 = **(int **)(unaff_FS_OFFSET + 0x2c);
  pbVar8 = (byte *)(*(int *)(iVar9 + 8) + *(int *)(unaff_ESI + 0x10));
  if ((*pbVar8 & 4) == 0) {
    FUN_0056b420(pbVar8 + 0x50,outMatrix,outMatrix); // transform point
    FUN_0044c4c0(*(int *)(unaff_ESI + 0x10) + 0x50 + *(int *)(iVar9 + 8),pfVar1,pfVar1);
  }
  if (DAT_00e2fc44 < *(float *)(unaff_ESI + 0x30)) {
    if ((*(uint *)(*(int *)(unaff_ESI + 0x24) + 0x108) & 0x40000000) != 0) {
      pfVar2 = (float *)(*(int *)(unaff_ESI + 0x10) + 0x80 + *(int *)(iVar9 + 8));
      fVar10 = pfVar2[1];
      fVar11 = pfVar2[2];
      fVar19 = *(float *)(unaff_ESI + 0x84);
      fVar21 = *(float *)(unaff_ESI + 0x88);
      fVar14 = *pfVar2 - *(float *)(unaff_ESI + 0x80);
      fVar20 = fVar14;
      FUN_004e41b0(); // randomize
      fVar12 = outMatrix[3];
      fVar20 = DAT_00e44564 - fVar20;
      *outMatrix = fVar20 * fVar14 + *outMatrix;
      outMatrix[1] = fVar20 * (fVar10 - fVar19) + outMatrix[1];
      outMatrix[2] = fVar20 * (fVar11 - fVar21) + outMatrix[2];
      outMatrix[3] = fVar20 * fStack_24 + outMatrix[3];
      outMatrix[3] = fVar12;
    }
    if ((*(uint *)(*(int *)(unaff_ESI + 0x24) + 0x10c) & 0x40000000) != 0) {
      pfVar2 = (float *)(*(int *)(unaff_ESI + 0x10) + 0x80 + *(int *)(iVar9 + 8));
      fVar10 = pfVar2[1];
      fVar11 = pfVar2[2];
      fVar19 = *(float *)(unaff_ESI + 0x84);
      fVar21 = *(float *)(unaff_ESI + 0x88);
      fVar20 = *(float *)(*(int *)(unaff_ESI + 0x24) + 0x150) / *(float *)(unaff_ESI + 0x30);
      fVar12 = outMatrix[7];
      *pfVar1 = fVar20 * (*pfVar2 - *(float *)(unaff_ESI + 0x80)) + *pfVar1;
      outMatrix[5] = fVar20 * (fVar10 - fVar19) + outMatrix[5];
      outMatrix[6] = fVar20 * (fVar11 - fVar21) + outMatrix[6];
      outMatrix[7] = fVar20 * fStack_24 + outMatrix[7];
      outMatrix[7] = fVar12;
    }
  }
  return;
}