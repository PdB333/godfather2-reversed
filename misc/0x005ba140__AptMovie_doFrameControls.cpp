// Xbox PDB: AptMovie::doFrameControls
// FUNC_NAME: AptMovie::renderFrame
void AptMovie::renderFrame(int *this, uint param_2, uint param_3, int nFrame)
{
  int *piVar1;
  undefined4 *puVar2;
  code *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int unaff_FS_OFFSET;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  if ((nFrame < 0) || (*this <= nFrame)) {
    local_14 = "nFrame >= 0 && nFrame < nFrames";
    local_10 = "..\\source\\Apt\\AptMovie.cpp";
    local_c = 0x87;
    local_8 = 2;
    local_4 = &DAT_01129153;
    if (DAT_01129153 != '\0') {
      piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
      uVar4 = 1;
      if (((piVar1 == (int *)0x0) ||
          (uVar4 = (**(code **)(*piVar1 + 8))(&local_14,"nFrame >= 0 && nFrame < nFrames"),
          local_4 != (undefined1 *)0x0)) && ((uVar4 & 2) != 0)) {
        *local_4 = 0;
      }
      if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
         (((uVar4 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
    }
  }
  if (param_2 < 0x1000) {
    local_c = 0x89;
    local_4 = &DAT_01129154;
  }
  else if (param_3 < 0x1000) {
    local_c = 0x8a;
    local_4 = &DAT_01129155;
  }
  else {
    if ((-1 < nFrame) && (nFrame < *this)) {
      iVar6 = 0;
      iVar5 = this[1] + nFrame * 8; // this[1] is frameData array pointer
      if (*(int *)(this[1] + nFrame * 8) < 1) {
        return;
      }
      do {
        puVar2 = *(undefined4 **)(*(int *)(iVar5 + 4) + iVar6 * 4);
        switch(*puVar2) {
        case 1:
        case 2:
        case 7:
          break;
        case 3:
          FUN_005b2e20(param_2,puVar2 + 1,param_3);
          break;
        case 4:
          FUN_005b3070(param_2);
          break;
        case 5:
          (*DAT_0119cb00)(puVar2[1]);
          break;
        case 6:
          (*DAT_0119cb4c)(*(undefined4 *)
                           (*(int *)(*(int *)(*(int *)(*(int *)(*(int *)(param_3 + 0x58) + 8) + 4) +
                                             0x18) + puVar2[1] * 4) + 8),0);
          break;
        case 8:
          if (-1 < (int)puVar2[1]) {
            FUN_005af370(puVar2[2],param_3,0xffffffff);
            puVar2[1] = 0xffffffff;
          }
          break;
        default:
          local_14 = "0";
          local_10 = "..\\source\\Apt\\AptMovie.cpp";
          local_c = 0xcd;
          local_8 = 2;
          local_4 = &DAT_01129157;
          FUN_0059bf00();
        }
        iVar6 = iVar6 + 1;
        iVar5 = this[1] + nFrame * 8;
      } while (iVar6 < *(int *)(this[1] + nFrame * 8));
      return;
    }
    local_c = 0x8b;
    local_4 = &DAT_01129156;
  }
  local_14 = "0";
  local_10 = "..\\source\\Apt\\AptMovie.cpp";
  local_8 = 2;
  FUN_0059bf00();
  return;
}