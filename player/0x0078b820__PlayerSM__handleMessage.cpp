// FUNC_NAME: PlayerSM::handleMessage
void __thiscall PlayerSM::handleMessage(int thisPtr, int *msg)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  float10 fVar6;
  undefined4 uVar7;
  undefined8 uStack_1c;
  undefined4 uStack_14;
  
  iVar2 = *msg;
  if (iVar2 == DAT_012069f4) {
    // Handle "enter vehicle" message
    if ((*(uint *)(*(int *)(thisPtr + 0x5c) + 0x1f58) >> 0x19 & 1) == 0) {
      FUN_0078a9f0(); // enterVehicle
      return;
    }
  }
  else {
    if (iVar2 == DAT_0120e93c) {
      // Handle "exit vehicle" message
      FUN_0078abb0(); // exitVehicle
      FUN_004086d0(&DAT_0120e93c); // deleteMessage
      return;
    }
    if (iVar2 == *(int *)(thisPtr + 0x34)) {
      // Handle "attack" message
      FUN_0078a900(1); // startAttack
      return;
    }
    if (iVar2 == DAT_0112afe0) {
      // Handle "damage" message
      iVar2 = FUN_00806440(); // getGameMode
      if (iVar2 == 3) {
        if (*(int *)(msg[1] + 4) == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(msg[1] + 4) + -0x48;
        }
        if (*(int *)(*(int *)(thisPtr + 0x5c) + 0x1ed4) != *(int *)(iVar2 + 0x1ed4)) {
          FUN_00806440(); // getGameMode
          return;
        }
      }
    }
    else if (iVar2 == DAT_01131028) {
      // Handle "interact" message
      iVar2 = *(int *)(msg[1] + 4);
      if (((((iVar2 != 0) && (iVar2 != 0x48)) && (iVar2 = *(int *)(msg[1] + 4), iVar2 != 0)) &&
          ((iVar2 = iVar2 + -0x48, iVar2 != 0 &&
           (iVar3 = FUN_006dc8e0(iVar2,0x383225a1), iVar3 != 0)))) &&
         ((piVar4 = (int *)FUN_0078a640(iVar2), piVar4 != (int *)0x0 &&
          (iVar2 = (**(code **)(*piVar4 + 0x34))(), iVar2 != 0)))) {
        (**(code **)(*piVar4 + 0x34))();
        return;
      }
    }
    else if (iVar2 == DAT_0112afd8) {
      // Handle "move to" message
      iVar2 = msg[1];
      cVar1 = (**(code **)(**(int **)(thisPtr + 0x5c) + 0x28c))(); // getCurrentState
      if (((cVar1 == *(char *)(iVar2 + 0x18)) && (*(int *)(thisPtr + 0x1c) != 0)) &&
         ((*(int *)(thisPtr + 0x1c) != 0x3c &&
          ((*(int *)(iVar2 + 4) != *(int *)(thisPtr + 0x5c) &&
           (fVar6 = (float10)(**(code **)(**(int **)(thisPtr + 0x5c) + 0xc0))(), (float10)0 < fVar6)
           ))))) {
        uStack_14 = *(undefined4 *)(iVar2 + 0x10);
        uStack_1c = *(undefined8 *)(iVar2 + 8);
        fVar6 = (float10)FUN_004702b0(&uStack_1c); // getDistance
        if (fVar6 < (float10)_DAT_00d699e8) {
          msg = (int *)0x0;
          if ((*(int *)(iVar2 + 4) == 0) || (cVar1 = FUN_00806f50(), cVar1 == '\0')) {
            if ((*(uint *)(*(int *)(thisPtr + 0x5c) + 0x1f98) >> 3 & 1) == 0) {
              FUN_0078b4b0(_DAT_00d62b10,0,1); // playAnimation
            }
          }
          else {
            if (*(int *)(iVar2 + 0x14) == 0) {
              msg = (int *)uRam00000098;
              if (*(int *)(thisPtr + 0x1c) != 0) {
                msg = *(int **)(*(int *)(thisPtr + 0x1c) + 0x5c);
              }
            }
            else if (*(int *)(iVar2 + 0x14) == 1) {
              if (*(int *)(thisPtr + 0x1c) == 0) {
                iVar2 = 0;
              }
              else {
                iVar2 = *(int *)(thisPtr + 0x1c) + -0x3c;
              }
              msg = *(int **)(iVar2 + 0x9c);
            }
            FUN_0078b270(5); // setMovementState
            FUN_0078b4b0(msg,0,1); // playAnimation
            cVar1 = FUN_00732380(); // isPlayerControlled
            if (cVar1 != '\0') {
              if (**(int **)(DAT_012233a0 + 4) == 0) {
                iVar2 = 0;
              }
              else {
                iVar2 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
              }
              piVar4 = (int *)FUN_006ad7f0(iVar2); // getPlayer
              (**(code **)(*piVar4 + 0x28))(0xe306a3f5,0,0xffffffff,0); // playSound
              uVar7 = 0;
              uVar5 = FUN_006fbc40(0,0); // getRandomFloat
              FUN_007f96a0(0x33197d73,0x74,uVar5,uVar7); // spawnVFX
              FUN_006fbc70(); // releaseRandom
              cVar1 = FUN_0078a7d0(); // isInCombat
              if (cVar1 != '\0') {
                uVar7 = 0;
                uVar5 = FUN_006fbc40(0,0); // getRandomFloat
                FUN_007f96a0(0xc5cc0ef5,0x74,uVar5,uVar7); // spawnVFX
                FUN_006fbc70(); // releaseRandom
                return;
              }
            }
          }
        }
      }
    }
  }
  return;
}