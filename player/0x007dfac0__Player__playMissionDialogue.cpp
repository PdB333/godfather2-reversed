// FUNC_NAME: Player::playMissionDialogue
void __thiscall Player::playMissionDialogue(int this, undefined4 param_2)
{
  bool bVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 local_c;
  uint local_8;
  
  *(undefined4 *)(this + 0x78) = param_2; // +0x78: dialogue ID
  *(undefined1 *)(this + 0x7c) = 1; // +0x7c: dialogue playing flag
  uVar7 = *(uint *)(*(int *)(this + 0x58) + 0x8e0) >> 1; // +0x58: player data, +0x8e0: flags
  local_8 = 0xffffffff;
  local_c = 0;
  FUN_007ab540(); // getCurrentMission
  iVar5 = FUN_007ab1e0(); // getMissionState
  if (iVar5 == 0) {
    return;
  }
  iVar5 = FUN_00701050(); // getMissionType
  if (((uVar7 & 1) == 0) || (iVar6 = *(int *)(this + 0x58), *(int *)(iVar6 + 0x24f8) != 0)) {
    if (((((*(uint *)(*(int *)(this + 0x58) + 0x8e0) >> 9 & 1) != 0) &&
         ((cVar3 = FUN_007ab500(3), cVar3 != '\0' &&
          (iVar6 = FUN_007ab160(), (*(byte *)(iVar6 + 4) & 0x80) != 0)))) ||
        ((*(uint *)(*(int *)(this + 0x58) + 0x8e8) >> 2 & 1) != 0)) ||
       ((*(uint *)(*(int *)(this + 0x58) + 0x8e0) >> 0x19 & 1) != 0)) {
      iVar6 = *(int *)(this + 0x58);
      iVar8 = *(int *)(iVar6 + 0x24f8); // +0x24f8: mission sub-type
      bVar4 = (byte)((uint)*(undefined4 *)(iVar6 + 0x8e0) >> 0x19) & 1;
      if ((((*(uint *)(iVar6 + 0x249c) >> 0x17 & 1) != 0) ||
          ((*(uint *)(iVar6 + 0x8e0) >> 9 & 1) != 0)) || (bVar1 = false, bVar4 != 0)) {
        bVar1 = true;
      }
      if (((*(uint *)(iVar6 + 0x8e8) >> 1 & 1) == 0) || (bVar2 = true, bVar4 != 0)) {
        bVar2 = false;
      }
      if ((iVar8 != 0) || (DAT_00d5ef84 < (float)(*(uint *)(iVar6 + 0x2890) & DAT_00e44680))) {
        if ((bVar1) || (iVar5 != 1)) {
          local_8 = *(uint *)(iVar6 + 0x6e8); // +0x6e8: some ID
          *(undefined1 *)(this + 0x7c) = 0;
        }
        else if ((iVar8 == 3) || (iVar8 == 4)) {
          local_8 = *(uint *)(iVar6 + 0x309c); // +0x309c: alternate ID
        }
        else {
          local_8 = *(uint *)(iVar6 + 0x6e8);
        }
        local_8 = local_8 >> 2;
        if ((iVar8 < 0) || (4 < iVar8)) {
          iVar8 = 0;
        }
      }
      else {
        *(undefined1 *)(this + 0x7c) = 1;
      }
      iVar5 = FUN_00701050();
      if (iVar5 == 2) {
        if ((uVar7 & 1) == 0) {
          if (bVar1) {
            if (bVar2) {
              iVar5 = (&DAT_00e53308)[iVar8];
            }
            else {
              iVar5 = (&DAT_00e532e0)[iVar8];
            }
          }
          else if (bVar2) {
            iVar5 = (&DAT_00e532f4)[iVar8];
          }
          else {
            iVar5 = (&DAT_00e532b8)[iVar8];
          }
        }
        else {
          iVar5 = (&DAT_00e532cc)[iVar8];
        }
      }
      else {
        iVar5 = FUN_00701050();
        if (iVar5 == 3) {
          if ((uVar7 & 1) == 0) {
            if (bVar1) {
              if (bVar2) {
                iVar5 = (&DAT_00e5336c)[iVar8];
              }
              else {
                iVar5 = (&DAT_00e53344)[iVar8];
              }
            }
            else if (bVar2) {
              iVar5 = (&DAT_00e53358)[iVar8];
            }
            else {
              iVar5 = (&DAT_00e5331c)[iVar8];
            }
          }
          else {
            iVar5 = (&DAT_00e53330)[iVar8];
          }
        }
        else {
          iVar5 = FUN_00701050();
          if (iVar5 == 4) {
            if ((uVar7 & 1) == 0) {
              if (bVar1) {
                if (bVar2) {
                  iVar5 = (&DAT_00e533bc)[iVar8];
                }
                else {
                  iVar5 = (&DAT_00e53394)[iVar8];
                }
              }
              else if (bVar2) {
                iVar5 = (&DAT_00e533a8)[iVar8];
              }
              else {
                iVar5 = (&DAT_00e53380)[iVar8];
              }
            }
            else {
              iVar5 = (&DAT_00e532cc)[iVar8];
            }
          }
          else if ((uVar7 & 1) == 0) {
            if (bVar1) {
              if (bVar2) {
                iVar5 = (&DAT_00e532a4)[iVar8];
              }
              else {
                iVar5 = (&DAT_00e53290)[iVar8];
              }
            }
            else if (bVar2) {
              iVar5 = (&DAT_00e5327c)[iVar8];
            }
            else {
              iVar5 = (&DAT_00e53254)[iVar8];
            }
          }
          else {
            iVar5 = (&DAT_00e53268)[iVar8];
          }
        }
      }
      if (iVar5 == 0) {
        return;
      }
      goto LAB_007dfea0;
    }
    iVar5 = FUN_00701050();
    if (iVar5 != 2) {
      iVar5 = FUN_00701050();
      local_c = 1;
      if (iVar5 == 3) {
        iVar5 = -0x13775e8;
        goto LAB_007dfea0;
      }
      goto LAB_007dfbcd;
    }
  }
  else {
    local_8 = *(uint *)(iVar6 + 0x6e8);
    *(undefined1 *)(this + 0x7c) = 1;
    local_8 = local_8 >> 2;
    if (((((*(uint *)(iVar6 + 0x8e0) >> 9 & 1) == 0) || (cVar3 = FUN_007ab500(3), cVar3 == '\0')) ||
        (iVar6 = FUN_007ab160(), (*(byte *)(iVar6 + 4) & 0x80) == 0)) &&
       ((*(uint *)(*(int *)(this + 0x58) + 0x8e8) >> 2 & 1) == 0)) {
      if (iVar5 != 2) {
        local_c = 1;
        if (iVar5 == 3) {
          iVar5 = -0x13775e8;
          goto LAB_007dfea0;
        }
LAB_007dfbcd:
        local_c = 1;
        iVar5 = 0x29bafc2e;
        goto LAB_007dfea0;
      }
    }
    else {
      if (*(int *)(*(int *)(this + 0x58) + 0x24f8) == 0) {
        if (iVar5 == 2) {
          iVar5 = 0x7ce0253;
        }
        else if ((iVar5 == 3) || (iVar5 == 4)) {
          iVar5 = 0x1652518c;
        }
        else {
          iVar5 = 0x77c66174;
        }
        goto LAB_007dfea0;
      }
      if (iVar5 != 2) {
        if ((iVar5 == 3) || (iVar5 == 4)) {
          local_c = 1;
          iVar5 = -0x13775e8;
          goto LAB_007dfea0;
        }
        goto LAB_007dfbcd;
      }
    }
  }
  iVar5 = 0x41c9df40;
LAB_007dfea0:
  FUN_004ac480(iVar5,0,local_8,1,1,1,local_c,0x3f800000); // playDialogue
  return;
}