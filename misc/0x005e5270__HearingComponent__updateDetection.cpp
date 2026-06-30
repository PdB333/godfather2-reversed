// FUNC_NAME: HearingComponent::updateDetection
undefined4 __thiscall HearingComponent::updateDetection(char *this, float *outClosestDistance, float *outFactor, float *outUnused, float *outSomething, undefined4 *outPointer)
{
  float fVar1;
  float *pfVar2;
  undefined4 uVar3;
  bool bVar4;
  float fVar5;
  char cVar6;
  float *in_EAX;
  float fVar7;
  float *pfVar8;
  float fVar9;
  int iVar10;
  byte bVar11;
  float *pfVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float local_138;
  float local_134;
  float local_130;
  float fStack_12c;
  float fStack_128;
  float fStack_124;
  float local_118;
  float local_114;
  float local_110 [4];
  float local_100 [12];
  float local_d0 [4];
  float afStack_c0 [7];
  byte abStack_a4 [160];

  fVar18 = 0.0f;
  fVar16 = 1.0f; // DAT_00e2b1a4 likely 1.0
  if (this[1] == '\0') goto LAB_005e55bb;
  // Construct 4 EarPoint objects (size 0x30 each)
  _vector_constructor_iterator_(local_d0, 0x30, 4, (_func_void_ptr_void_ptr *)&LAB_005e4280);
  fVar7 = (float)FUN_005e45d0(local_d0); // Returns number of valid ear points?
  fVar5 = fStack_124;
  fVar16 = 1.0f;
  fVar17 = *in_EAX; // Input position X
  fVar18 = 0.0f;
  fVar15 = in_EAX[1]; // Input position Y
  fVar1 = in_EAX[2]; // Input position Z
  local_134 = 0.0f;
  local_138 = 0.0f;
  local_130 = fVar17;
  fStack_12c = fVar15;
  fStack_128 = fVar1;
  if (fVar7 != 0.0f)
  {
    pfVar8 = local_100 + 1;
    pfVar12 = local_d0;
    fVar13 = fVar7;
    do
    {
      pfVar2 = (float *)pfVar12[8]; // pointer to transform matrix at offset 0x20
      if (pfVar2 == (float *)0x0)
      {
        pfVar8[-1] = FLT_MAX;
        *pfVar8 = FLT_MAX;
        pfVar8[1] = FLT_MAX;
      }
      else
      {
        local_110[0] = fVar17 - *pfVar12;     // delta X to ear position
        local_110[1] = fVar15 - pfVar12[1];   // delta Y
        local_110[2] = fVar1 - pfVar12[2];    // delta Z
        local_110[3] = 0.0f;                  // w component

        // Transform delta to ear local space using first three rows of 4x4 matrix
        local_130 = local_110[1] * pfVar2[4] + local_110[0] * *pfVar2 + local_110[2] * pfVar2[8];
        fStack_12c = local_110[1] * pfVar2[5] + local_110[0] * pfVar2[1] + local_110[2] * pfVar2[9];
        fStack_128 = local_110[1] * pfVar2[6] + local_110[0] * pfVar2[2] + local_110[2] * pfVar2[10];
        fStack_124 = local_110[1] * pfVar2[7] + local_110[0] * pfVar2[3] + local_110[2] * pfVar2[0xb];

        pfVar8[-1] = local_130;
        *pfVar8 = fStack_12c;
        pfVar8[1] = fStack_128;
      }
      pfVar12 += 0xc; // next ear (12 floats = 48 bytes)
      pfVar8 += 3;
      fVar13 -= 1.0f;
    } while (fVar13 != 0.0f);

    if (fVar7 != 0.0f)
    {
      local_138 = 0.0f;
      bVar11 = 0;
      fVar9 = 0.0f;
      fVar13 = 3.402823e+38f; // DAT_00e2e50c (FLT_MAX)
      do
      {
        // local_100 stores transformed coordinates (3 floats per ear)
        fVar14 = SQRT(local_100[(int)fVar9 * 3 + 2] * local_100[(int)fVar9 * 3 + 2] +
                      local_100[(int)fVar9 * 3 + 1] * local_100[(int)fVar9 * 3 + 1] +
                      local_100[(int)fVar9 * 3] * local_100[(int)fVar9 * 3]);
        local_110[(int)fVar9] = fVar14; // store distance
        if (fVar14 < fVar13)
        {
          local_138 = fVar9; // index of closest ear
          fVar13 = fVar14;
        }
        bVar11 = bVar11 + 1;
        fVar9 = (float)(uint)bVar11;
      } while ((uint)fVar9 < (uint)fVar7);
      local_134 = local_110[(int)local_138]; // minimum distance
    }
  }
  fVar13 = local_134;
  if ((fVar7 != 0.0f) && ((abStack_a4[(int)local_138 * 0x30] & 1) != 0))
  {
    // If ear is active, compute distance to original position (afStack_c0 stores the source positions?)
    local_130 = fVar17 - afStack_c0[(int)local_138 * 0xc];
    fStack_12c = fVar15 - afStack_c0[(int)local_138 * 0xc + 1];
    fStack_128 = fVar1 - afStack_c0[(int)local_138 * 0xc + 2];
    fStack_124 = fVar5 - afStack_c0[(int)local_138 * 0xc + 3];
    fVar13 = SQRT(fStack_12c * fStack_12c + fStack_128 * fStack_128 + local_130 * local_130);
  }
  if (DAT_00e44598 <= fVar13 - *(float *)(this + 0xc))
  {
    *outFactor = 0.0f;
    goto LAB_005e55bb;
  }
  if (fVar13 < 0.0f)
  {
LAB_005e550d:
    fVar18 = 0.0f;
  }
  else
  {
    fVar17 = *(float *)(this + 0xc) - *(float *)(this + 8); // outerRadius - innerRadius
    fVar13 = fVar13 - *(float *)(this + 8); // distance - innerRadius
    fVar18 = 1.0f;
    if ((0.0f < fVar17) && (0.0f < fVar13))
    {
      fVar15 = 1.0f;
      if (DAT_00e44598 < fVar17)
      {
        fVar15 = DAT_00e39f98 / fVar17; // Some constant / radius difference
      }
      fVar15 = fVar15 * fVar13;
      if (fVar15 <= DAT_00e2dd14)
      {
        if (DAT_00e2b04c < fVar15)
        {
          fVar18 = 1.0f - (fVar15 - DAT_00e2b04c) * DAT_00e35654;
        }
      }
      else
      {
        fVar18 = DAT_00e35654 - (fVar15 - DAT_00e2dd14) * DAT_00e2b334;
        if (fVar18 < 0.0f) goto LAB_005e550d;
      }
    }
  }
  *outFactor = fVar18;
  if (fVar7 == 1.4013e-45f)
  {
    local_138 = 0.0f;
    cVar6 = FUN_005e5980(1); // Some query function
    fVar16 = 1.0f;
    if (cVar6 != '\0')
    {
      *outUnused = local_138;
    }
  }
  fVar18 = 0.0f;
  if (*this != '\0')
  {
    FUN_005e5c60(local_110, *outClosestDistance, *(undefined4 *)(this + 4), outSomething);
  }
  *outClosestDistance = local_134;
LAB_005e55bb:
  uVar3 = *(undefined4 *)(this + 0x14);
  bVar4 = false;
  local_138 = fVar18;
  local_134 = fVar16;
  if ((this[0x18] & 4U) == 0)
  {
    iVar10 = FUN_005dc670(*(undefined4 *)(this + 0x10));
    fVar16 = local_138;
    fVar18 = local_134;
    if ((((iVar10 != 0) &&
         (FUN_005dd8a0(uVar3, &local_134), fVar16 = local_138, fVar18 = local_134, 0.0f <= local_134))
        && (local_134 <= 1.0f)) && (0.0f <= local_138))
    {
      bVar4 = true;
    }
  }
  else
  {
    iVar10 = FUN_005dc670(*(undefined4 *)(this + 0x10));
    fVar16 = local_138;
    fVar18 = local_134;
    if (iVar10 != 0)
    {
      bVar4 = true;
      FUN_005dd8a0(0, &local_134);
      FUN_005dd8a0(DAT_012056c0, &local_138);
      fVar16 = local_114 * 0.0f + local_118;
      fVar18 = local_134 * 0.0f + local_138;
    }
  }
  if (bVar4)
  {
    cVar6 = *this;
    *outFactor = *outFactor * fVar18;
    if (cVar6 == '\0')
    {
      *outSomething = fVar16;
    }
    else
    {
      *outSomething = *outSomething * fVar16;
    }
  }
  uVar3 = *(undefined4 *)(this + 0x10);
  *outPointer = 0;
  iVar10 = FUN_005dc670(uVar3);
  if (iVar10 != 0)
  {
    *outPointer = *(undefined4 *)(iVar10 + 0x280);
  }
  return 1;
}