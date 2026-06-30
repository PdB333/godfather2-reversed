// FUNC_NAME: MetaModelInstance::updateSkinning

void __thiscall MetaModelInstance::updateSkinning(int this, char forceUpdate, char param_3, undefined4 param_4)
{
  ushort uVar1;
  int iVar2;
  float fVar3, fVar4, fVar5, fVar6, fVar7, fVar8, fVar9, fVar10, fVar11, fVar12;
  float fVar23, fVar24, fVar25, fVar26, fVar27, fVar28, fVar29, fVar30, fVar31, fVar32, fVar33, fVar34, fVar35;
  undefined4 *puVar13;
  char cVar14;
  int iVar15;
  float *pfVar16;
  undefined4 *puVar17;
  int *piVar18;
  uint uVar19;
  ushort *puVar20;
  int iVar21;
  undefined4 *puVar22;
  float in_XMM0_Da;
  float local_120;
  char local_119;
  float local_118;
  float *local_114;
  int *local_110;
  ushort *puStack_10c;
  undefined4 *local_108;
  uint local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  float local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  float local_e4;
  float *pfStack_b4;
  float local_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  undefined1 local_50[76];

  // +0x130 = flags (bit 1: visible flag)
  // +0x132 = frame counter for waiting
  if (forceUpdate != 0 && ((*(byte *)(this + 0x130) >> 1 & 1) == 0))
  {
    cVar14 = FUN_0051eca0(); // likely isVisible() or visibility check
    if (cVar14 == 0)
    {
      *(short *)(this + 0x132) = *(short *)(this + 0x132) + 1;
      if (*(ushort *)(this + 0x132) < 6)
        return;
      // After 6 frames, apply previous offset?
      *(float *)(this + 0x14) = *(float *)(*(int *)(this + 0x10) + 0x6c) + *(float *)(this + 0x14);
      return;
    }
    FUN_00524c80(); // likely setVisibility(true)
    *(ushort *)(this + 0x130) = *(ushort *)(this + 0x130) | 2; // set visible flag
  }

  // +0x124 = state enum? (0=?, 4=special)
  // +0xd0 = pointer to bone data container
  // +0x10 = parent object/transform
  if ((((*(int *)(this + 0x124) != 0) && (*(int *)(this + 0x124) != 4)) &&
       (iVar15 = *(int *)(this + 0xd0), iVar15 != 0) &&
       (*(int *)(iVar15 + 0xc) != 0)) &&
      // some global condition
      (FUN_0049f870(), // likely getTime() or delta time
       local_118 = in_XMM0_Da * DAT_00e2b04c - DAT_00e2b1a4,
       local_118 < 0.0 ? (local_118 = 0.0) : local_118,
       local_118 = *(float *)(this + 0x18) * local_118, // +0x18 = blend weight?
       (DAT_00e2af44 <= local_118) &&
       (cVar14 = FUN_0066ea50(), iVar21 = DAT_0110ab30, cVar14 != 0)))
  {
    piVar18 = *(int **)(iVar15 + 0x14); // linked list of bones/groups
    local_119 = 1;
    do
    {
      // Check if bone group has specific id and no "skip" flag
      if ((*(int *)(piVar18[1] + 0x30) == iVar21) && ((*(byte *)(piVar18[1] + 0x24) & 8) == 0))
      {
        FUN_004599d0(); // likely reset some animation data
      }
      else
      {
        local_119 = 0;
      }
      piVar18 = (int *)*piVar18;
    } while (piVar18 != (int *)0x0);

    if (local_119 != 0)
    {
      // Get state index
      if (*(int *)(this + 0x124) == 0)
        iVar15 = 0;
      else
        iVar15 = *(int *)(this + 0x124) + -4;

      FUN_00414c90(iVar15 + 0x30, local_50); // likely compute world transform matrix
      FUN_006131d0(&DAT_01218d40, &local_100); // get object-to-world matrix?
      FUN_00417560(); // matrix operations?
      FUN_0053b5e0(); // maybe set skinning matrices

      if ((*(byte *)(*(int *)(this + 0x10) + 0x44) & 0x20) != 0) // +0x44 flags
      {
        FUN_00417560();
        FUN_0053b690(DAT_01163840 != 0);
      }

      if ((param_3 != 0) || ((*(byte *)(*(int *)(this + 0x10) + 0x44) & 0x20) != 0))
      {
        FUN_0053b610(); // maybe set additional data
      }

      local_120 = DAT_00e2b1a4; // constant (likely 0.0 or 1.0)
      if (*(char *)(*(int *)(this + 0x10) + 0x48) == 1) // +0x48 bool?
      {
        local_120 = 0.0;
      }

      FUN_0053b780(param_4, local_120); // maybe set camera transform
      FUN_0053b550(); // finalize skinning setup?

      if (param_3 != 0)
      {
        // Store position from this
        local_b0 = *(float *)(this + 0x50);
        fStack_ac = *(float *)(this + 0x54);
        fStack_a8 = *(float *)(this + 0x58);
        fStack_a4 = *(float *)(*(int *)(this + 0x10) + 0x40); // parent scale?
        FUN_0053b520(); // maybe push to GPU
      }

      // Allocate matrix buffer: 3 matrices per bone (blend shapes?)
      local_108 = (undefined4 *)FUN_0060cd00(4,
        *(int *)(*(int *)(this + 0xd0) + 0xc) * 3, 0, 1, 0);
      if (local_108 != (undefined4 *)0x0)
      {
        local_110 = *(int **)(*(int *)(this + 0xd0) + 0x14); // bone list head
        local_f8 = 0;
        local_fc = 0;
        local_100 = 0;
        local_e4 = 0.0;
        local_e8 = 0;
        local_ec = 0;
        local_f0 = 0;
        local_120 = 0.0;
        local_f4 = local_118; // blend weight stored here
        fVar23 = DAT_00e2b1a4;

        do
        {
          fVar3 = local_120;
          local_114 = (float *)local_110[1]; // pointer to bone data
          local_118 = (float)(uint)*(byte *)((int)local_114 + 0x2d); // +0x2d = blend shape count?
          pfVar16 = local_114;

          if (local_114 != (float *)local_120) // if previous bone group exists
          {
            iVar15 = 0;
            if (local_120 != 0.0)
            {
              piVar18 = (int *)((int)local_120 + 0x34);
              local_104 = (uint)*(byte *)((int)local_120 + 0x2d);
              local_120 = 0.0;
              if (*piVar18 != 0)
              {
                iVar21 = 0;
                do
                {
                  iVar2 = *(int *)((int)fVar3 + 0x50);
                  puVar22 = *(undefined4 **)
                    (iVar2 + 100 +
                      ((-(uint)(*(char *)(iVar21 + 6 + iVar2) != '\0') & local_104) +
                       iVar15) * 4);
                  if (*(char *)(puVar22 + 7) == '\0')
                  {
                    *(undefined1 *)((int)puVar22 + 0x1d) = 0;
                  }
                  else
                  {
                    (**(code **)(*(int *)*puVar22 + 0x30))((int *)*puVar22);
                    fVar23 = DAT_00e2b1a4;
                  }
                  local_120 = (float)((int)local_120 + 1);
                  iVar21 = iVar21 + 0xb0;
                  iVar15 = iVar15 + 0x2c;
                } while ((uint)local_120 < (uint)*(float *)((int)fVar3 + 0x34));
              }
            }

            uVar19 = 0;
            pfVar16 = local_114;
            local_120 = (float)local_114;
            if (*(int *)((int)local_114 + 0x34) != 0)
            {
              iVar15 = 0;
              iVar21 = 0;
              do
              {
                puVar22 = *(undefined4 **)
                  (*(int *)((int)pfVar16 + 0x50) + 100 +
                    ((-(uint)(*(char *)(iVar21 + 6 + *(int *)((int)pfVar16 + 0x50)) != '\0')
                      & (uint)local_118) + iVar15) * 4);
                if (*(char *)(puVar22 + 7) == '\0')
                {
                  local_120 = (float)puVar22[4];
                  *(undefined1 *)((int)puVar22 + 0x1d) = 1;
                }
                else
                {
                  local_120 = 0.0;
                  (**(code **)(*(int *)*puVar22 + 0x2c))((int *)*puVar22, 0, 0, &local_120, 0x10);
                  pfVar16 = local_114;
                  fVar23 = DAT_00e2b1a4;
                }
                (&DAT_01227060)[uVar19] = local_120;
                uVar19 = uVar19 + 1;
                iVar21 = iVar21 + 0xb0;
                iVar15 = iVar15 + 0x2c;
                local_120 = (float)pfVar16;
              } while (uVar19 < *(uint *)((int)pfVar16 + 0x34));
            }
          }

          local_104 = *(uint *)((int)pfVar16 + 0x50);
          puVar20 = (ushort *)(local_110 + 4); // offset to face indices?
          puStack_10c = (ushort *)(local_110 + local_110[3] * 8 + 4);
          puVar22 = local_108 + 4;

          do
          {
            iVar15 = (&DAT_01227060)[*puVar20];
            uVar1 = puVar20[1];
            iVar21 = (uint)*puVar20 * 0xb0 + local_104;
            pfVar16 = (float *)(iVar15 + (uint)uVar1 * 0x14);
            fStack_60 = *pfVar16;
            fStack_5c = pfVar16[1];
            fStack_58 = pfVar16[2];
            fStack_54 = pfVar16[3];
            local_114 = (float *)(iVar15 + (uint)puVar20[2] * 0x14);
            pfStack_b4 = (float *)(iVar15 + (uint)puVar20[3] * 0x14);
            fStack_70 = *local_114;
            fStack_6c = local_114[1];
            fStack_68 = local_114[2];
            fStack_64 = local_114[3];
            local_b0 = *pfStack_b4;
            fStack_ac = pfStack_b4[1];
            fStack_a8 = pfStack_b4[2];
            fStack_a4 = pfStack_b4[3];
            
            if (*(char *)(iVar21 + 6) == '\0') // if not using base pose
            {
              // Fetch skinning matrix for current blend shape
              pfVar16 = *(float **)(iVar21 + 0x78 + (int)local_118 * 4);
              fVar3 = pfVar16[4];
              fVar4 = pfVar16[5];
              fVar25 = pfVar16[6];
              fVar26 = pfVar16[7];
              fVar5 = *pfVar16;
              fVar28 = pfVar16[1];
              fVar30 = pfVar16[2];
              fVar32 = pfVar16[3];
              fVar6 = pfVar16[8];
              fVar7 = pfVar16[9];
              fVar8 = pfVar16[10];
              fVar24 = pfVar16[0xb];
              fVar9 = pfVar16[0xc];
              fVar10 = pfVar16[0xd];
              fVar11 = pfVar16[0xe];
              fVar12 = pfVar16[0xf];

              // Transform three vertices by matrix (row-major?)
              fVar27 = fStack_60 * fVar28;
              fVar29 = fStack_60 * fVar30;
              fVar31 = fStack_60 * fVar32;
              fVar33 = fStack_5c * fVar25;
              fVar34 = fStack_5c * fVar26;
              fVar35 = fStack_58 * fVar24;
              fStack_60 = fStack_60 * fVar5 + fStack_5c * fVar3 + fStack_58 * fVar6 + fVar23 * fVar9;
              fStack_5c = fVar27 + fStack_5c * fVar4 + fStack_58 * fVar7 + fVar23 * fVar10;
              fStack_58 = fVar29 + fVar33 + fStack_58 * fVar8 + fVar23 * fVar11;
              fStack_54 = fVar31 + fVar34 + fVar35 + fVar23 * fVar12;

              fVar27 = fStack_70 * fVar28;
              fVar29 = fStack_70 * fVar30;
              fVar31 = fStack_70 * fVar32;
              fVar33 = fStack_6c * fVar25;
              fVar34 = fStack_6c * fVar26;
              fVar35 = fStack_68 * fVar24;
              fStack_70 = fStack_70 * fVar5 + fStack_6c * fVar3 + fStack_68 * fVar6 + fVar23 * fVar9;
              fStack_6c = fVar27 + fStack_6c * fVar4 + fStack_68 * fVar7 + fVar23 * fVar10;
              fStack_68 = fVar29 + fVar33 + fStack_68 * fVar8 + fVar23 * fVar11;
              fStack_64 = fVar31 + fVar34 + fVar35 + fVar23 * fVar12;

              fVar28 = local_b0 * fVar28;
              fVar30 = local_b0 * fVar30;
              fVar32 = local_b0 * fVar32;
              fVar25 = fStack_ac * fVar25;
              fVar26 = fStack_ac * fVar26;
              fVar24 = fStack_a8 * fVar24;
              local_b0 = local_b0 * fVar5 + fStack_ac * fVar3 + fStack_a8 * fVar6 + fVar23 * fVar9;
              fStack_ac = fVar28 + fStack_ac * fVar4 + fStack_a8 * fVar7 + fVar23 * fVar10;
              fStack_a8 = fVar30 + fVar25 + fStack_a8 * fVar8 + fVar23 * fVar11;
              fStack_a4 = fVar32 + fVar26 + fVar24 + fVar23 * fVar12;

              // Fill remaining components with identity-like values
              fStack_a0 = fVar23;
              fStack_9c = fVar23;
              fStack_98 = fVar23;
              fStack_94 = fVar23;
              fStack_90 = fVar23;
              fStack_8c = fVar23;
              fStack_88 = fVar23;
              fStack_84 = fVar23;
              fStack_80 = fVar23;
              fStack_7c = fVar23;
              fStack_78 = fVar23;
              fStack_74 = fVar23;
            }

            FUN_00414aa0(); // likely normalize or something

            puVar13 = local_108;
            // Store blend shape weight
            local_e4 = *(float *)(iVar15 + (uint)uVar1 * 0x14 + 0xc);
            local_f0 = *(undefined4 *)(puVar20 + 4);
            local_ec = *(undefined4 *)(puVar20 + 6);
            // Store first set of matrices per vertex
            *local_108 = local_100;
            local_108[1] = local_fc;
            local_108[2] = local_f8;
            local_108[3] = local_f4;
            *puVar22 = local_f0;
            puVar22[1] = local_ec;
            puVar22[2] = local_e8;
            puVar22[3] = local_e4;
            puVar17 = local_108 + 8;
            FUN_00414aa0();

            local_f0 = *(undefined4 *)(puVar20 + 8);
            local_e4 = local_114[3];
            local_ec = *(undefined4 *)(puVar20 + 10);
            *puVar17 = local_100;
            puVar13[9] = local_fc;
            puVar13[10] = local_f8;
            puVar13[0xb] = local_f4;
            puVar22[8] = local_f0;
            puVar22[9] = local_ec;
            puVar22[10] = local_e8;
            puVar22[0xb] = local_e4;
            FUN_00414aa0();

            local_f0 = *(undefined4 *)(puVar20 + 0xc);
            local_e4 = pfStack_b4[3];
            local_ec = *(undefined4 *)(puVar20 + 0xe);
            puVar13[0x10] = local_100;
            puVar13[0x11] = local_fc;
            puVar13[0x12] = local_f8;
            puVar13[0x13] = local_f4;
            puVar22[0x10] = local_f0;
            puVar22[0x11] = local_ec;
            puVar22[0x12] = local_e8;
            puVar22[0x13] = local_e4;

            local_108 = puVar13 + 0x18; // advance 6 floats (24 bytes) per index
            puVar20 = puVar20 + 0x10; // advance 8 ushorts per index
            puVar22 = puVar22 + 0x18; // advance 6 floats
          } while (puVar20 != puStack_10c);

          local_110 = (int *)*local_110; // next bone in linked list
        } while (local_110 != (int *)0x0);

        FUN_0060cde0(); // submit skinning matrices to GPU?

        fVar23 = local_120;
        iVar15 = 0;
        if (local_120 != 0.0)
        {
          puStack_10c = (ushort *)(uint)*(byte *)((int)local_120 + 0x2d);
          local_118 = 0.0;
          if (*(int *)((int)local_120 + 0x34) != 0)
          {
            iVar21 = 0;
            do
            {
              iVar2 = *(int *)((int)fVar23 + 0x50);
              puVar22 = *(undefined4 **)
                (iVar2 + 100 +
                  ((-(uint)(*(char *)(iVar21 + 6 + iVar2) != '\0') & (uint)puStack_10c) +
                   iVar15) * 4);
              if (*(char *)(puVar22 + 7) == '\0')
              {
                *(undefined1 *)((int)puVar22 + 0x1d) = 0;
              }
              else
              {
                (**(code **)(*(int *)*puVar22 + 0x30))((int *)*puVar22);
              }
              local_118 = (float)((int)local_118 + 1);
              iVar21 = iVar21 + 0xb0;
              iVar15 = iVar15 + 0x2c;
            } while ((uint)local_118 < *(uint *)((int)fVar23 + 0x34));
          }
        }
      }
    }
  }
  return;
}