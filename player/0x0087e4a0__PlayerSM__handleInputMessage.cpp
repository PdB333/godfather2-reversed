// FUNC_NAME: PlayerSM::handleInputMessage
void __thiscall PlayerSM::handleInputMessage(uint thisPtr, int *messageData)
{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined4 local_40;
  undefined ***local_3c;
  undefined1 local_38;
  undefined **local_34;
  undefined8 local_30;
  undefined4 local_28;
  undefined1 uStack_1c;
  float fStack_18;
  undefined **ppuStack_14;
  undefined4 uStack_4;
  
  iVar4 = *messageData;
  if (iVar4 == DAT_0112fddc) {
    // Handle "attack" input
    iVar4 = messageData[1];
    if (iVar4 != 0) {
      fVar6 = (float10)(**(code **)(*(int *)(thisPtr - 0x3c) + 0xc0))();
      if ((float10)0 < fVar6) {
        (**(code **)(*(int *)(thisPtr - 0x3c) + 0x2b8))(iVar4,1);
        FUN_0055b7d0(messageData);
        return;
      }
      FUN_004088c0(iVar4 + 0x3c);
      FUN_0055b7d0(messageData);
      return;
    }
  }
  else {
    if (iVar4 == DAT_0112fde8) {
      // Handle "cover" input
      if ((*(byte *)(thisPtr + 0xc4e) & 1) != 0) {
        (**(code **)(*(int *)(thisPtr - 0x3c) + 0x2ac))();
        FUN_0055b7d0(messageData);
        return;
      }
      (**(code **)(*(int *)(thisPtr - 0x3c) + 0x2b0))();
      FUN_0055b7d0(messageData);
      return;
    }
    if (iVar4 == DAT_0112fdf8) {
      // Handle "interact" input
      iVar4 = messageData[1];
      if ((iVar4 != 0) && ((*(byte *)(iVar4 + 0x40) & 1) != 0)) {
        FUN_00878170(iVar4);
        FUN_0055b7d0(messageData);
        return;
      }
    }
    else {
      if (iVar4 == *(int *)(thisPtr + 0xb58)) {
        // Handle "move forward" input
        (**(code **)(*(int *)(thisPtr - 0x3c) + 0x284))(1);
        FUN_0055b7d0(messageData);
        return;
      }
      if (iVar4 == *(int *)(thisPtr + 0xb60)) {
        // Handle "move backward" input
        (**(code **)(*(int *)(thisPtr - 0x3c) + 0x284))(0);
        FUN_0055b7d0(messageData);
        return;
      }
      if (iVar4 == DAT_0112e038) {
        // Handle "pause" input
        FUN_00878980(0x637b907);
        FUN_0055b7d0(messageData);
        return;
      }
      if (iVar4 == DAT_0112b36c) {
        // Handle "reset" input
        FUN_004088c0(thisPtr);
        FUN_0055b7d0(messageData);
        return;
      }
      if (iVar4 == *(int *)(thisPtr + 0xb68)) {
        // Handle "sprint" input
        if ((*(uint *)(thisPtr + 0xc4c) | 8) != *(uint *)(thisPtr + 0xc4c)) {
          (**(code **)(*(int *)(thisPtr + 0x1c) + 0x28))(0x10);
          *(uint *)(thisPtr + 0xc4c) = *(uint *)(thisPtr + 0xc4c) | 8;
          FUN_0055b7d0(messageData);
          return;
        }
      }
      else if (iVar4 == DAT_0112dfcc) {
        // Handle "aim" input
        if ((*(uint *)(thisPtr + 0xc4c) >> 6 & 1) != 0) {
          FUN_0087d560(1);
          FUN_0055b7d0(messageData);
          return;
        }
      }
      else if (iVar4 == DAT_0112dfc4) {
        // Handle "stop aiming" input
        *(uint *)(thisPtr + 0xc4c) = *(uint *)(thisPtr + 0xc4c) & 0xffffff7f;
        *(undefined4 *)(thisPtr + 0xc48) = 0;
        if (((*(uint *)(thisPtr + 0xc4c) >> 0x15 & 1) != 0) && (*(int *)(thisPtr + 0x9d0) != 0)) {
          FUN_004df590();
          FUN_0055b7d0(messageData);
          return;
        }
      }
      else {
        if (iVar4 == DAT_0112adf8) {
          // Handle "stop aiming" input (alternate)
          *(uint *)(thisPtr + 0xc4c) = *(uint *)(thisPtr + 0xc4c) & 0xffffff7f;
          *(undefined4 *)(thisPtr + 0xc48) = 0;
          if (((*(uint *)(thisPtr + 0xc4c) >> 0x15 & 1) != 0) && (*(int *)(thisPtr + 0x9d0) != 0)) {
            FUN_004df590();
          }
        }
        else {
          if (iVar4 == DAT_0112e104) {
            // Handle "reload" input
            FUN_0087bd50(1);
            FUN_0055b7d0(messageData);
            return;
          }
          if (iVar4 != DAT_0112e0f4) {
            if (iVar4 == DAT_0112e064) {
              // Handle "debug" input
              FUN_00876880();
              FUN_00440590(&DAT_0112e064,-(uint)(thisPtr != 0x3c) & thisPtr,DAT_00d5eee4,0,4);
              FUN_0055b7d0(messageData);
              return;
            }
            if (iVar4 == DAT_0120e93c) {
              // Handle "enter vehicle" input
              piVar1 = (int *)(thisPtr - 0x3c);
              (**(code **)(*(int *)(thisPtr - 0x3c) + 0x14))();
              uVar3 = FUN_007788c0(piVar1);
              *(undefined4 *)(thisPtr + 0x784) = uVar3;
              if (thisPtr == 0x3c) {
                iVar4 = 0;
              }
              else {
                iVar4 = thisPtr + 0x774;
              }
              FUN_009aefd0(iVar4,0x8000);
              FUN_00875be0();
              FUN_00876710();
              (**(code **)(*piVar1 + 0x274))();
              (**(code **)(*piVar1 + 0x178))(DAT_012067e8,0);
              iVar4 = **(int **)(DAT_012233a0 + 4);
              if ((iVar4 == 0) || (iVar4 == 0x1f30)) {
                iVar4 = 0;
              }
              else {
                iVar4 = *(int *)(iVar4 + 0x1250);
              }
              if ((iVar4 != 0) && (_DAT_00d577a0 <= *(float *)(iVar4 + 0x70))) {
                FUN_0072de20(piVar1);
                uStack_1c = 1;
                if (_DAT_00d577a0 <= *(float *)(iVar4 + 0x70)) {
                  ppuStack_14 = &PTR_LAB_00e54198;
                  fStack_18 = *(float *)(iVar4 + 0x70);
                }
                if (*(char *)(thisPtr + 0xe14) == '\0') {
                  FUN_0081dab0((int)&local_30 + 4);
                  *(undefined1 *)(thisPtr + 0xe14) = 1;
                }
                FUN_0072c130();
              }
              iVar4 = 0;
              puVar5 = (undefined4 *)(thisPtr + 0xde0);
              do {
                puVar2 = (undefined4 *)(*(int *)(*(int *)(thisPtr + 0x32c) + 0x8c) + 0xc + iVar4);
                iVar4 = iVar4 + 0x28;
                *puVar5 = *puVar2;
                puVar5 = puVar5 + 1;
              } while (iVar4 < 0xa0);
              FUN_0055b7d0(uStack_4);
              return;
            }
            if (iVar4 == DAT_0112e020) {
              // Handle "use item" input
              FUN_0087c4e0(1,thisPtr + 0xad8,1);
              if ((*(uint *)(thisPtr + 0x9dc) >> 9 & 1) != 0) {
                iVar4 = FUN_00471610();
                local_30 = *(undefined8 *)(iVar4 + 0x30);
                local_28 = *(undefined4 *)(iVar4 + 0x38);
                local_3c = &local_34;
                local_34 = &PTR_LAB_00d76624;
                local_40 = DAT_0112e0fc;
                local_38 = 0;
                FUN_00408a00(&local_40,0);
                FUN_0055b7d0(messageData);
                return;
              }
            }
            else if (iVar4 == *(int *)(thisPtr + 0xb78)) {
              // Handle "stop using item" input
              FUN_0087c4e0(0,thisPtr + 0xad8,0);
              if ((*(uint *)(thisPtr + 0x9dc) >> 9 & 1) != 0) {
                iVar4 = FUN_00471610();
                local_30 = *(undefined8 *)(iVar4 + 0x30);
                local_28 = *(undefined4 *)(iVar4 + 0x38);
                local_3c = &local_34;
                local_34 = &PTR_LAB_00d76624;
                local_40 = DAT_0112e0fc;
                local_38 = 0;
                FUN_00408a00(&local_40,0);
                FUN_0055b7d0(messageData);
                return;
              }
            }
            else if (iVar4 == DAT_012067dc) {
              // Handle "special action" input
              FUN_0087a880();
            }
            goto LAB_0087ea5a;
          }
        }
        if (*(int *)(thisPtr + 0x9d0) != 0) {
          FUN_004df590();
          FUN_0055b7d0(messageData);
          return;
        }
      }
    }
  }
LAB_0087ea5a:
  FUN_0055b7d0(messageData);
  return;
}