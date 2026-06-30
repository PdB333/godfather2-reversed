// FUNC_NAME: AnimationBlendNode::blendAnimations
int AnimationBlendNode::blendAnimations(int animA, int animB, float blendFactor)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  int *dst;
  float *pfVar10;
  int *srcA;
  int *srcB;
  float *pfVar11;
  int iVar12;
  size_t sVar13;
  int iVar14;
  uint uVar15;
  float *pfVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  int minFrames;
  int local_48;
  void *ptrA;
  float *pfA;
  float *pfB;
  void *ptrResult;
  float *pfResult;
  float *pfResult2;
  void *ptrA2;
  float *pfA2;
  float *pfB2;
  float local_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  if ((animB == 0) || (iVar9 = FUN_0056fdd0(), iVar9 == 0)) {
    return 0;
  }
  iVar1 = *(int *)(*(int *)(animA + 0x38) + 0xc); // animA->frameCount
  iVar2 = *(int *)(*(int *)(animB + 0x38) + 0xc); // animB->frameCount
  minFrames = iVar1;
  if (iVar2 <= iVar1) {
    minFrames = iVar2;
  }
  FUN_0056f800(animB); // lockAnimation
  FUN_0056f800(animA); // lockAnimation
  iVar14 = animB;
  if (iVar2 <= iVar1) {
    iVar14 = animA;
  }
  FUN_0056f800(iVar14); // lockAnimation
  fVar17 = blendFactor;
  if (*(int *)(iVar9 + 0x3c) == 0) { // no secondary blend data
    ptrA = (void *)(*(int *)(animA + 0x34) + 0x14); // animA->boneData + 0x14
    ptrB = (void *)(*(int *)(animB + 0x34) + 0x14); // animB->boneData + 0x14
    pfA = (float *)(*(int *)(animB + 0x38) + 0x10); // animB->frameData + 0x10
    pfVar16 = (float *)(*(int *)(animA + 0x38) + 0x10); // animA->frameData + 0x10
    ptrResult = (void *)(*(int *)(iVar9 + 0x34) + 0x14); // result->boneData + 0x14
    pfVar11 = (float *)(*(int *)(iVar9 + 0x38) + 0x10); // result->frameData + 0x10
    iVar14 = minFrames;
    if ((*(char *)(*(int *)(animA + 0x34) + 0x10) == '\0') || // animA->hasAdditive
       (*(char *)(*(int *)(animB + 0x34) + 0x10) == '\0')) { // animB->hasAdditive
      for (; pfResult = pfVar11, pfA2 = pfVar16, 0 < iVar14; iVar14 = iVar14 + -1) {
        FUN_005859d0(&ptrB, blendFactor); // blendBoneData
        pfA = pfA + 8;
        ptrA = (void *)((int)ptrA + 1);
        ptrB = (void *)((int)ptrB + 1);
        ptrResult = (void *)((int)ptrResult + 1);
        pfVar16 = pfA2 + 8;
        pfVar11 = pfResult + 8;
      }
    }
    else {
      pfResult = pfVar11;
      pfA2 = pfVar16;
      FUN_0056f620(); // preBlendSetup
      local_48 = minFrames;
      if (0 < minFrames) {
        ptrA = (void *)((int)ptrA + minFrames);
        ptrResult = (void *)((int)ptrResult + minFrames);
        ptrB = (void *)((int)ptrB + minFrames);
        do {
          FUN_005781f0(pfVar11, blendFactor); // blendFrameData
          pfA = pfA + 8;
          local_48 = local_48 + -1;
          pfVar16 = pfVar16 + 8;
          pfVar11 = pfVar11 + 8;
          fVar17 = blendFactor;
        } while (0 < local_48);
      }
    }
    if (minFrames < iVar1) {
      _memcpy(ptrResult, ptrA, iVar1 - minFrames);
      sVar13 = (iVar1 - minFrames) * 0x20;
    }
    else {
      if (iVar2 <= minFrames) goto LAB_00585e3b;
      _memcpy(ptrResult, ptrB, iVar2 - minFrames);
      sVar13 = (iVar2 - minFrames) * 0x20;
      pfVar16 = pfA;
    }
  }
  else { // has secondary blend data
    ptrB = (void *)(*(int *)(animA + 0x34) + 0x14); // animA->boneData + 0x14
    pfB = (float *)(*(int *)(animA + 0x3c) + 0x10); // animA->secondaryFrameData + 0x10
    ptrA = (void *)(*(int *)(animB + 0x34) + 0x14); // animB->boneData + 0x14
    pfA = (float *)(*(int *)(animB + 0x38) + 0x10); // animB->frameData + 0x10
    pfB2 = (float *)(*(int *)(animB + 0x3c) + 0x10); // animB->secondaryFrameData + 0x10
    ptrResult = (void *)(*(int *)(iVar9 + 0x34) + 0x14); // result->boneData + 0x14
    pfVar16 = (float *)(*(int *)(animA + 0x38) + 0x10); // animA->frameData + 0x10
    pfVar11 = (float *)(*(int *)(iVar9 + 0x38) + 0x10); // result->frameData + 0x10
    pfResult = (float *)(*(int *)(iVar9 + 0x3c) + 0x10); // result->secondaryFrameData + 0x10
    iVar14 = minFrames;
    if ((*(char *)(*(int *)(animA + 0x34) + 0x10) == '\0') || // animA->hasAdditive
       (*(char *)(*(int *)(animB + 0x34) + 0x10) == '\0')) { // animB->hasAdditive
      for (; pfResult2 = pfVar16, pfResult = pfVar11, 0 < iVar14; iVar14 = iVar14 + -1) {
        FUN_005867d0(&ptrResult, &ptrB, &ptrA, blendFactor); // blendBoneAndFrameData
        pfA = pfA + 8;
        ptrB = (void *)((int)ptrB + 1);
        ptrA = (void *)((int)ptrA + 1);
        ptrResult = (void *)((int)ptrResult + 1);
        pfB = pfB + 4;
        pfB2 = pfB2 + 4;
        pfResult = pfResult + 4;
        pfVar16 = pfResult2 + 8;
        pfVar11 = pfResult + 8;
      }
    }
    else {
      pfResult2 = pfVar16;
      pfResult = pfVar11;
      FUN_0056f620(); // preBlendSetup
      local_48 = minFrames;
      if (0 < minFrames) {
        ptrB = (void *)((int)ptrB + minFrames);
        ptrResult = (void *)((int)ptrResult + minFrames);
        ptrA = (void *)((int)ptrA + minFrames);
        local_20 = fVar17;
        fStack_1c = fVar17;
        fStack_18 = fVar17;
        fStack_14 = fVar17;
        do {
          FUN_005781f0(pfVar11, blendFactor); // blendFrameData
          fVar17 = pfB[1];
          fVar5 = pfB[2];
          fVar19 = pfB[3];
          fVar18 = pfB2[1];
          fVar6 = pfB2[2];
          fVar7 = pfB2[3];
          pfA = pfA + 8;
          local_48 = local_48 + -1;
          *pfResult = (*pfB2 - *pfB) * local_20 + *pfB;
          pfResult[1] = (fVar18 - fVar17) * fStack_1c + fVar17;
          pfResult[2] = (fVar6 - fVar5) * fStack_18 + fVar5;
          pfResult[3] = (fVar7 - fVar19) * fStack_14 + fVar19;
          pfB = pfB + 4;
          pfB2 = pfB2 + 4;
          pfResult = pfResult + 4;
          pfVar16 = pfVar16 + 8;
          pfVar11 = pfVar11 + 8;
          fVar17 = blendFactor;
        } while (0 < local_48);
      }
    }
    if (minFrames < iVar1) {
      sVar13 = iVar1 - minFrames;
      _memcpy(ptrResult, ptrB, sVar13);
      _memcpy(pfVar11, pfVar16, sVar13 * 0x20);
      pfVar16 = pfB;
    }
    else {
      if (iVar2 <= minFrames) goto LAB_00585e3b;
      sVar13 = iVar2 - minFrames;
      _memcpy(ptrResult, ptrA, sVar13);
      _memcpy(pfVar11, pfA, sVar13 * 0x20);
      pfVar16 = pfB2;
    }
    sVar13 = sVar13 << 4;
    pfVar11 = pfResult;
  }
  _memcpy(pfVar11, pfVar16, sVar13);
  fVar17 = blendFactor;
LAB_00585e3b:
  if (*(int *)(iVar9 + 0x40) != 0) { // has extra blend data
    uVar15 = *(uint *)(*(int *)(iVar9 + 0x40) + 0xc); // extraData->count
    pfVar16 = (float *)(*(int *)(iVar9 + 0x40) + 0x10); // result->extraData
    pfVar11 = (float *)(*(int *)(animA + 0x40) + 0x10); // animA->extraData
    pfVar10 = (float *)(*(int *)(animB + 0x40) + 0x10); // animB->extraData
    for (iVar14 = (int)uVar15 >> 2; 0 < iVar14; iVar14 = iVar14 + -1) {
      fVar5 = pfVar11[1];
      fVar19 = pfVar11[2];
      fVar18 = pfVar11[3];
      fVar6 = pfVar10[1];
      fVar7 = pfVar10[2];
      fVar8 = pfVar10[3];
      *pfVar16 = (*pfVar10 - *pfVar11) * fVar17 + *pfVar11;
      pfVar16[1] = (fVar6 - fVar5) * fVar17 + fVar5;
      pfVar16[2] = (fVar7 - fVar19) * fVar17 + fVar19;
      pfVar16[3] = (fVar8 - fVar18) * fVar17 + fVar18;
      pfVar11 = pfVar11 + 4;
      pfVar10 = pfVar10 + 4;
      pfVar16 = pfVar16 + 4;
    }
    uVar15 = uVar15 & 3;
    if (3 < uVar15) {
      iVar14 = (uVar15 - 4 >> 2) + 1;
      uVar15 = uVar15 + iVar14 * -4;
      do {
        *pfVar16 = (*pfVar10 - *pfVar11) * fVar17 + *pfVar11;
        pfVar16[1] = (pfVar10[1] - pfVar11[1]) * fVar17 + pfVar11[1];
        pfVar16[2] = (pfVar10[2] - pfVar11[2]) * fVar17 + pfVar11[2];
        pfVar16[3] = (pfVar10[3] - pfVar11[3]) * fVar17 + pfVar11[3];
        pfVar11 = pfVar11 + 4;
        pfVar10 = pfVar10 + 4;
        pfVar16 = pfVar16 + 4;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
    }
    for (; 0 < (int)uVar15; uVar15 = uVar15 - 1) {
      *pfVar16 = (*pfVar10 - *pfVar11) * fVar17 + *pfVar11;
      pfVar11 = pfVar11 + 1;
      pfVar10 = pfVar10 + 1;
      pfVar16 = pfVar16 + 1;
    }
  }
  fVar5 = DAT_00e2b1a4; // some constant threshold
  if (*(int *)(iVar9 + 0x44) != 0) { // has integer blend data
    srcA = (int *)(*(int *)(animA + 0x44) + 0x10); // animA->intData
    srcB = (int *)(*(int *)(animB + 0x44) + 0x10); // animB->intData
    dst = (int *)(*(int *)(iVar9 + 0x44) + 0x10); // result->intData
    iVar14 = minFrames;
    if (3 < minFrames) {
      iVar12 = (minFrames - 4U >> 2) + 1;
      iVar14 = minFrames + iVar12 * -4;
      do {
        iVar3 = *srcB;
        iVar4 = *srcA;
        fVar19 = (float)srcA[1];
        fVar18 = (float)srcB[1];
        *dst = iVar3;
        if (0.0 < fVar17) {
          if (fVar5 <= fVar17) {
LAB_00585ff5:
            *dst = iVar3;
          }
          else if (iVar4 != iVar3) {
            fVar19 = 0.0;
            if (iVar3 != -1) goto LAB_00585ff5;
            *dst = 7;
            fVar18 = fVar5;
          }
        }
        else {
          *dst = iVar4;
        }
        dst[1] = (int)((fVar18 - fVar19) * fVar17 + fVar19);
        iVar3 = srcB[2];
        iVar4 = srcA[2];
        fVar19 = (float)srcA[3];
        fVar18 = (float)srcB[3];
        dst[2] = iVar3;
        if (0.0 < fVar17) {
          if (fVar5 <= fVar17) {
LAB_00586042:
            dst[2] = iVar3;
          }
          else if (iVar4 != iVar3) {
            fVar19 = 0.0;
            if (iVar3 != -1) goto LAB_00586042;
            dst[2] = 7;
            fVar18 = fVar5;
          }
        }
        else {
          dst[2] = iVar4;
        }
        dst[3] = (int)((fVar18 - fVar19) * fVar17 + fVar19);
        iVar3 = srcB[4];
        iVar4 = srcA[4];
        fVar19 = (float)srcA[5];
        fVar18 = (float)srcB[5];
        dst[4] = iVar3;
        if (0.0 < fVar17) {
          if (fVar5 <= fVar17) {
LAB_00586090:
            dst[4] = iVar3;
          }
          else if (iVar4 != iVar3) {
            fVar19 = 0.0;
            if (iVar3 != -1) goto LAB_00586090;
            dst[4] = 7;
            fVar18 = fVar5;
          }
        }
        else {
          dst[4] = iVar4;
        }
        dst[5] = (int)((fVar18 - fVar19) * fVar17 + fVar19);
        iVar3 = srcB[6];
        iVar4 = srcA[6];
        fVar19 = (float)srcA[7];
        fVar18 = (float)srcB[7];
        dst[6] = iVar3;
        if (0.0 < fVar17) {
          if (fVar5 <= fVar17) {
LAB_005860de:
            dst[6] = iVar3;
          }
          else if (iVar4 != iVar3) {
            fVar19 = 0.0;
            if (iVar3 != -1) goto LAB_005860de;
            dst[6] = 7;
            fVar18 = fVar5;
          }
        }
        else {
          dst[6] = iVar4;
        }
        dst[7] = (int)((fVar18 - fVar19) * fVar17 + fVar19);
        srcA = srcA + 8;
        srcB = srcB + 8;
        dst = dst + 8;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    for (; 0 < iVar14; iVar14 = iVar14 + -1) {
      iVar12 = *srcB;
      iVar3 = *srcA;
      fVar19 = (float)srcA[1];
      fVar18 = (float)srcB[1];
      *dst = iVar12;
      if (0.0 < fVar17) {
        if (fVar5 <= fVar17) {
LAB_00586145:
          *dst = iVar12;
        }
        else if (iVar3 != iVar12) {
          fVar19 = 0.0;
          if (iVar12 != -1) goto LAB_00586145;
          *dst = 7;
          fVar18 = fVar5;
        }
      }
      else {
        *dst = iVar3;
      }
      dst[1] = (int)((fVar18 - fVar19) * fVar17 + fVar19);
      srcA = srcA + 2;
      srcB = srcB + 2;
      dst = dst + 2;
    }
    if (minFrames < iVar1) {
      _memcpy(dst, srcA, (iVar1 - minFrames) * 8);
      return iVar9;
    }
    if (minFrames < iVar2) {
      _memcpy(dst, srcB, (iVar2 - minFrames) * 8);
    }
  }
  return iVar9;
}