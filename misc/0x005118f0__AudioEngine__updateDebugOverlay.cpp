// FUNC_NAME: AudioEngine::updateDebugOverlay
void __thiscall AudioEngine::updateDebugOverlay(uint startIndex)
{
  int *piVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  byte cVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int count; // originally in_EAX
  int iVar9;
  int iVar10;
  bool bVar11;
  int iVar12;
  int iVar13;
  byte bVar14;
  int iVar15;
  uint uVar16;
  int this_edi; // unaff_EDI
  int fs_off; // unaff_FS_OFFSET
  float fVar17;
  byte local_48;
  uint local_44;
  float local_40;
  int local_34;
  float local_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;

  // This function appears to process a number of audio channels (or debug entries)
  // and updates global debug visualization variables.
  // It uses many globals that look like debug overlay state.

  // Get thread-local storage pointer (from FS segment)
  iVar6 = **(int **)(fs_off + 0x2c);

  // Multiply scale factor at this+0x2c by factor at this+0x4c (maybe master volume)
  *(float *)(this_edi + 0x2c) = *(float *)(this_edi + 0x4c) * *(float *)(this_edi + 0x2c);

  // Load some global flags/state
  cVar5 = *(char *)(*(int *)(DAT_012233a8 + 4) + 0x84);
  bVar14 = (byte)((uint)*(undefined4 *)(*(int *)(this_edi + 8) + *(int *)(iVar6 + 8)) >> 0x1a) & 1;

  // Determine if bVar14 is non-zero OR some condition on pointer at this+0x10 offset 0x171
  if ((bVar14 != 0) || (local_48 = 1, *(char *)(*(int *)(this_edi + 0x10) + 0x171) == '\0')) {
    local_48 = 0;
  }

  // Save/restore debug global variables (clamping between 0 and 0x19, 0x1b, etc.)
  if (DAT_012058d0 < 0x19) {
    DAT_012058d0 = 0x19;
  }
  if (0x19 < DAT_00f15988) {
    DAT_00f15988 = 0x19;
  }
  _DAT_011f3a3c = 7;
  if (DAT_012058d0 < 0x18) {
    DAT_012058d0 = 0x18;
  }
  if (0x18 < DAT_00f15988) {
    DAT_00f15988 = 0x18;
  }
  _DAT_011f3a38 = (uint)*(byte *)(*(int *)(this_edi + 0x10) + 0x171);
  if (DAT_012058d0 < 0xf) {
    DAT_012058d0 = 0xf;
  }
  if (0xf < DAT_00f15988) {
    DAT_00f15988 = 0xf;
  }
  _DAT_011f3a14 = (uint)local_48;
  if (DAT_012058d0 < 7) {
    DAT_012058d0 = 7;
  }
  if (7 < DAT_00f15988) {
    DAT_00f15988 = 7;
  }
  _DAT_011f39f4 = (uint)(~*(byte *)(*(int *)(this_edi + 0x10) + 0x10c) & 1);
  if (DAT_012058d0 < 0xe) {
    DAT_012058d0 = 0xe;
  }
  if (0xe < DAT_00f15988) {
    DAT_00f15988 = 0xe;
  }
  _DAT_011f3a10 =
       (uint)((byte)((uint)*(undefined4 *)(*(int *)(this_edi + 0x10) + 0x108) >> 0x1c) & 1);
  if (DAT_012058d0 < 0x1b) {
    DAT_012058d0 = 0x1b;
  }
  if (0x1a < DAT_00f15988) {
    DAT_00f15988 = 0x1b;
  }
  _DAT_011f3a44 = (uint)(bVar14 == 0);

  FUN_004ec7a0(); // Possibly a setup function

  local_44 = startIndex;
  if (bVar14 == 0) {
    // Swap debug function pointers and data
    PTR_FUN_0110ac14 = FUN_006124c0;
    PTR_FUN_0110ac18 = FUN_006124b0;
    _DAT_0110ac24 = DAT_00e2b1a4;
  }

  local_34 = count;
  if (count != 0) {
    do {
      iVar13 = *(int *)(iVar6 + 8);
      uVar16 = local_44 & 7;
      piVar1 = (int *)(this_edi + 0x80 + ((int)local_44 >> 3) * 8); // Bitmap entry for channel group
      iVar7 = *piVar1;
      iVar10 = uVar16 * 0x50 + iVar13; // Offset into channel data (0x50 bytes per channel)
      if ((*(byte *)(iVar7 + iVar10 + 0x54) & 1) == 0) {
        // Transform vectors: probably channel position or orientation
        FUN_0050a810(this_edi + 0x10, piVar1, 0x3f800000); // 1.0f as scalar
        local_20 = *(float *)(this_edi + 0x20) * local_20;
        fStack_1c = *(float *)(this_edi + 0x24) * fStack_1c;
        fStack_18 = *(float *)(this_edi + 0x28) * fStack_18;
        fStack_14 = *(float *)(this_edi + 0x2c) * fStack_14;

        bVar11 = DAT_00e2af44 < fStack_14;
        if (bVar14 != 0) {
          if (fStack_14 <= DAT_00e2af44) goto LAB_00511da4;
          if (cVar5 == '\0') {
            if (DAT_012058d0 < 0x1b) {
              DAT_012058d0 = 0x1b;
            }
            if (0x1a < DAT_00f15988) {
              DAT_00f15988 = 0x1b;
            }
            _DAT_011f3a44 = (uint)(_DAT_0110ac24 > fStack_14);
          }
          else {
            bVar11 = bVar11 && _DAT_0110ac24 <= fStack_14;
          }
        }

        if (bVar11) {
          iVar8 = *piVar1;
          fVar17 = *(float *)(iVar8 + uVar16 * 4 + iVar13); // Some per-channel float (volume?)
          if ((*(uint *)(*(int *)(this_edi + 0x10) + 0x108) & 0x20000000) != 0) {
            fVar17 = fVar17 - (*(float *)(iVar8 + 0x58 + iVar10) - DAT_00e2b1a4) *
                              *(float *)(*(int *)(this_edi + 0x14) + 0xc);
          }

          iVar13 = *(int *)(this_edi + 0x14);
          local_40 = *(float *)(iVar13 + 0x70) * fVar17;
          fVar17 = *(float *)(iVar13 + 0x74) * fVar17;

          if ((*(byte *)(*(int *)(this_edi + 0x10) + 0x10c) & 0x80) == 0) {
            local_40 = (float)(int)((local_40 - (float)(int)local_40) * *(float *)(iVar13 + 0x80)) *
                       *(float *)(iVar13 + 0x88);
            fVar17 = (float)(int)((fVar17 - (float)(int)fVar17) * *(float *)(iVar13 + 0x84)) *
                     *(float *)(iVar13 + 0x8c);
          }

          uVar2 = (uint)local_40 | (*(byte *)(iVar8 + 0x5c + iVar10) & 0xffffff80) << 0x18;
          fVar3 = *(float *)(iVar8 + 0x40 + iVar10);
          fVar4 = *(float *)(this_edi + 0x34);

          if (*(int *)(this_edi + 0x54) != 0) {
            // Access a render/display list via this+0x50 and this+0x54
            iVar8 = *(int *)(*(int *)(this_edi + 0x50) + 0x90);
            _DAT_012278b0 = *(undefined4 *)(iVar13 + 0x88);
            _DAT_012278b4 = *(undefined4 *)(*(int *)(this_edi + 0x14) + 0x8c);
            _DAT_012278b8 = uVar2;
            _DAT_012278bc = fVar17;
            _DAT_012278c0 = local_20;
            _DAT_012278c4 = fStack_1c;
            _DAT_012278c8 = fStack_18;
            _DAT_012278cc = fStack_14;

            if (iVar13 != 0) {
              iVar12 = 0;
              iVar15 = iVar13;
              do {
                iVar9 = *(int *)(iVar8 + 0x50) + iVar12;
                if (*(int *)(iVar9 + 0x80) == 0) {
                  *(undefined **)(iVar9 + 0x80) = &DAT_012278b0;
                }
                iVar12 = iVar12 + 0xb0;
                iVar15 = iVar15 + -1;
              } while (iVar15 != 0);
            }

            FUN_00510b50(this_edi, piVar1, uVar16,
                         *(undefined4 *)(*(int *)(this_edi + 0x54) + (uint)*(ushort *)(iVar7 + iVar10 + 0x56) * 4));
            FUN_00511800(this_edi, fVar3 * fVar4, &local_20);

            if (iVar13 != 0) {
              iVar10 = 0;
              do {
                *(undefined4 *)(*(int *)(iVar8 + 0x50) + 0x80 + iVar10) = 0;
                iVar10 = iVar10 + 0xb0;
                iVar13 = iVar13 + -1;
              } while (iVar13 != 0);
            }
          }
        }
      }
LAB_00511da4:
      local_44 = local_44 + 1;
      if ((int)*(short *)(this_edi + 0x6e) <= (int)local_44) {
        local_44 = local_44 - (int)*(short *)(this_edi + 0x6e);
      }
      local_34 = local_34 + -1;
    } while (local_34 != 0);
  }

  // Restore debug function pointers and data
  if (bVar14 == 0) {
    PTR_FUN_0110ac14 = PTR_FUN_0110ac1c;
    PTR_FUN_0110ac18 = PTR_FUN_0110ac20;
    _DAT_0110ac24 = DAT_0110ac28;
  }

  // Restore debug globals to default values
  if (DAT_012058d0 < 0x1b) {
    DAT_012058d0 = 0x1b;
  }
  if (0x1a < DAT_00f15988) {
    DAT_00f15988 = 0x1b;
  }
  _DAT_011f3a44 = 0;
  if (DAT_012058d0 < 0x19) {
    DAT_012058d0 = 0x19;
  }
  if (0x19 < DAT_00f15988) {
    DAT_00f15988 = 0x19;
  }
  _DAT_011f3a3c = 7;
  if (DAT_012058d0 < 0x18) {
    DAT_012058d0 = 0x18;
  }
  if (0x18 < DAT_00f15988) {
    DAT_00f15988 = 0x18;
  }
  _DAT_011f3a38 = 0;
  if (DAT_012058d0 < 0xf) {
    DAT_012058d0 = 0xf;
  }
  if (0xf < DAT_00f15988) {
    DAT_00f15988 = 0xf;
  }
  _DAT_011f3a14 = 0;
  if (DAT_012058d0 < 7) {
    DAT_012058d0 = 7;
  }
  if (7 < DAT_00f15988) {
    DAT_00f15988 = 7;
  }
  _DAT_011f39f4 = 1;
  if (DAT_012058d0 < 0xe) {
    DAT_012058d0 = 0xe;
  }
  if (0xe < DAT_00f15988) {
    DAT_00f15988 = 0xe;
  }
  _DAT_011f3a10 = 1;

  FUN_00417cf0(1, 5, 6); // Finally call a debug drawing function
  return;
}