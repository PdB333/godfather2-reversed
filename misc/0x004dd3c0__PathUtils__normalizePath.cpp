// FUNC_NAME: PathUtils::normalizePath
void __fastcall PathUtils::normalizePath(uint *pathBuffer)
{
  short sVar1;
  wchar_t wVar2;
  short *psVar3;
  undefined2 *puVar4;
  int iVar5;
  wchar_t *pwVar6;
  short *psVar7;
  short *psVar8;
  short *psVar9;
  short *psVar10;
  wchar_t *pwVar11;
  
  if (*pathBuffer != 0) {
    FUN_004dd0a0(); // likely convertBackslashesToForward or another normalization step
    psVar3 = (short *)*pathBuffer;
    if (*psVar3 != 0) {
      psVar7 = psVar3 + 1;
      sVar1 = psVar3[1];
      while (sVar1 != 0) {
        psVar9 = psVar7 + 1;
        psVar7 = psVar7 + 1;
        if (*psVar9 == 0) break;
        if ((sVar1 == 0x5c) && (*psVar9 == 0x5c)) {
          // Collapse double backslashes "\\" -> "\"
          sVar1 = *psVar7;
          psVar9 = psVar7;
          while (sVar1 != 0) {
            *psVar9 = psVar9[1];
            psVar9 = psVar9 + 1;
            sVar1 = *psVar9;
          }
        }
        sVar1 = *psVar7;
      }
    }
    // Remove duplicate separators detected by some function
    iVar5 = FUN_00b9fa49(*pathBuffer, &DAT_00e36eec);
    while (iVar5 != 0) {
      sVar1 = *(short *)(iVar5 + 6);
      puVar4 = (undefined2 *)(iVar5 + 2);
      // Shift characters left to remove the duplicate separator
      while (sVar1 != 0) {
        *puVar4 = puVar4[2];
        sVar1 = puVar4[3];
        puVar4 = puVar4 + 1;
      }
      *puVar4 = 0;
      iVar5 = FUN_00b9fa49(*pathBuffer, &DAT_00e36eec);
    }
    // Remove leading drive letter colon (e.g. "C:\" -> remove the colon and drive letter)
    pwVar11 = (wchar_t *)*pathBuffer;
    pwVar6 = _wcschr(pwVar11 + 2, L':');
    if ((pwVar6 != (wchar_t *)0x0) && ((wchar_t *)(*pathBuffer + 4) < pwVar6)) {
      pwVar6 = pwVar6 + -1;
      do {
        *pwVar11 = *pwVar6;
        pwVar6 = pwVar6 + 1;
        wVar2 = *pwVar11;
        pwVar11 = pwVar11 + 1;
      } while (wVar2 != L'\0');
    }
    // Resolve ".." (parent directory) components
    psVar7 = (short *)*pathBuffer;
    sVar1 = *psVar7;
    while (sVar1 != 0) {
      psVar9 = psVar7;
      if ((((sVar1 == 0x2e) && (psVar7[1] == 0x2e)) && ((short *)*pathBuffer < psVar7)) &&
         ((psVar10 = psVar7 + 2, psVar7[2] != 0x2e && (psVar7[-1] != 0x2e)))) {
        // We found ".." not at start, preceded by a backslash or other
        if (psVar3 < psVar7) {
          if (psVar7[-1] == 0x5c) {
            psVar7 = psVar7 + -2;
          }
          else {
            psVar7 = psVar7 + -1;
          }
        }
        psVar8 = psVar3;
        if (psVar3 <= psVar7) {
          for (; (psVar8 = psVar7, psVar3 < psVar7 && (*psVar7 != 0x5c)); psVar7 = psVar7 + -1) {
          }
        }
        // Remove the previous segment and the ".." by shifting the remainder
        do {
          *psVar8 = *psVar10;
          sVar1 = *psVar10;
          psVar8 = psVar8 + 1;
          psVar9 = psVar3;
          psVar10 = psVar10 + 1;
        } while (sVar1 != 0);
      }
      psVar7 = psVar9 + 1;
      sVar1 = psVar9[1];
    }
    // Compute the new length (in wchar_t units, stored as short count)
    psVar7 = (short *)*pathBuffer;
    psVar3 = psVar7 + 1;
    do {
      sVar1 = *psVar7;
      psVar7 = psVar7 + 1;
    } while (sVar1 != 0);
    pathBuffer[1] = (int)psVar7 - (int)psVar3 >> 1;
  }
  return;
}