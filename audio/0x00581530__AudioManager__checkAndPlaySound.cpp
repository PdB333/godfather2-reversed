// FUNC_NAME: AudioManager::checkAndPlaySound
void AudioManager::checkAndPlaySound(int param_1, int param_2, float param_3, float param_4)
{
  uint in_EAX;
  uint uVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int local_c;
  
  if ((*(uint *)(param_1 + 4) & 0xff) < 10) {
    local_c = *(int *)(param_1 + 0x28); // +0x28: soundCount for low priority
  }
  else {
    local_c = *(int *)(param_1 + 0x30); // +0x30: soundCount for high priority
  }
  if (local_c != 0) {
    uVar1 = in_EAX >> 5;
    if ((((uVar1 & 1) != 0) || (DAT_00e2e210 <= (float)((uint)(param_4 - param_3) & DAT_00e44680)))
       && ((((byte)(*(uint *)(param_2 + 0x10) >> 0x17) | (byte)(in_EAX >> 9)) & 1) == 0)) {
      if ((~(byte)(*(uint *)(param_2 + 0x10) >> 0x12) & ~(byte)(in_EAX >> 1) & 1) == 0) {
        if (param_4 < param_3) {
          local_c = local_c + -1;
          if (-1 < local_c) {
            iVar3 = local_c * 0x10;
            do {
              if ((*(uint *)(param_1 + 4) & 0xff) < 10) {
                iVar2 = *(int *)(param_1 + 0x2c); // +0x2c: soundArray for low priority
              }
              else {
                iVar2 = *(int *)(param_1 + 0x34); // +0x34: soundArray for high priority
              }
              fVar4 = *(float *)(iVar2 + iVar3) + DAT_00e2b1a4;
              if ((uVar1 & 1) == 0) {
                if ((param_3 <= fVar4) || (fVar4 < param_4)) {
LAB_00581792:
                  FUN_00571c30(); // playSound
                }
              }
              else if ((param_3 <= fVar4) || (fVar4 <= param_4)) goto LAB_00581792;
              local_c = local_c + -1;
              iVar3 = iVar3 + -0x10;
            } while (-1 < local_c);
          }
        }
        else {
          local_c = local_c + -1;
          if (-1 < local_c) {
            iVar3 = local_c * 0x10;
            do {
              if ((*(uint *)(param_1 + 4) & 0xff) < 10) {
                iVar2 = *(int *)(param_1 + 0x2c);
              }
              else {
                iVar2 = *(int *)(param_1 + 0x34);
              }
              fVar4 = *(float *)(iVar2 + iVar3) + DAT_00e2b1a4;
              if ((uVar1 & 1) == 0) {
                if ((param_3 <= fVar4) && (fVar4 < param_4)) {
LAB_00581712:
                  FUN_00571c30();
                }
              }
              else if ((param_3 <= fVar4) && (fVar4 <= param_4)) goto LAB_00581712;
              local_c = local_c + -1;
              iVar3 = iVar3 + -0x10;
              if (local_c < 0) {
                return;
              }
            } while( true );
          }
        }
      }
      else if (param_3 < param_4) {
        if (0 < local_c) {
          iVar3 = 0;
          do {
            if ((*(uint *)(param_1 + 4) & 0xff) < 10) {
              iVar2 = *(int *)(param_1 + 0x2c);
            }
            else {
              iVar2 = *(int *)(param_1 + 0x34);
            }
            fVar4 = *(float *)(iVar2 + iVar3);
            if ((uVar1 & 1) == 0) {
              if ((fVar4 <= param_3) || (param_4 < fVar4)) {
LAB_00581689:
                FUN_00571c30();
              }
            }
            else if ((fVar4 <= param_3) || (param_4 <= fVar4)) goto LAB_00581689;
            iVar3 = iVar3 + 0x10;
            local_c = local_c + -1;
            if (local_c == 0) {
              return;
            }
          } while( true );
        }
      }
      else if (0 < local_c) {
        iVar3 = 0;
        do {
          if ((*(uint *)(param_1 + 4) & 0xff) < 10) {
            iVar2 = *(int *)(param_1 + 0x2c);
          }
          else {
            iVar2 = *(int *)(param_1 + 0x34);
          }
          fVar4 = *(float *)(iVar2 + iVar3);
          if ((uVar1 & 1) == 0) {
            if ((fVar4 <= param_3) && (param_4 < fVar4)) {
LAB_0058161a:
              FUN_00571c30();
            }
          }
          else if ((fVar4 <= param_3) && (param_4 <= fVar4)) goto LAB_0058161a;
          iVar3 = iVar3 + 0x10;
          local_c = local_c + -1;
          if (local_c == 0) {
            return;
          }
        } while( true );
      }
    }
  }
  return;
}