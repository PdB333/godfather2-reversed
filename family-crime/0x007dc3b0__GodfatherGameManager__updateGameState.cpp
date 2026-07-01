// FUNC_NAME: GodfatherGameManager::updateGameState
undefined4 __thiscall GodfatherGameManager::updateGameState(short *stateMachine, int *gameManager)
{
  short *psVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  bool bVar9;
  float fVar10;
  undefined1 local_c [12];
  
  iVar4 = DAT_01223394;
  switch(*stateMachine) {
  case 0: // INIT state
    if ((*(byte *)(stateMachine + 1) & 2) != 0) {
      FUN_006901b0(6); // playSound(6)
    }
    gameManager[0x928] = gameManager[0x928] | 0x10; // set flag +0x928 bit 4
    if ((stateMachine[1] & 0x400U) == 0) {
      FUN_00799c20(); // showLoadingScreen()
    }
    else {
      FUN_006901e0(0x49); // playSound(0x49)
    }
    FUN_0079d4f0(); // initRendering()
    gameManager[0x928] = gameManager[0x928] | 0x80; // set flag +0x928 bit 7
    *(undefined1 *)(stateMachine + 0x34) = 0;
    stateMachine[0x35] = 0;
    stateMachine[0x36] = 0;
    iVar4 = DAT_0112ad5c;
    stateMachine[0x37] = 0;
    if ((*(byte *)(stateMachine + 1) & 3) != 0) {
      *(undefined4 *)(DAT_0112ad5c + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x14) = 0;
      FUN_007dc2e0(); // resetSomeState()
      FUN_00786bc0(); // resetAudio()
    }
    if (DAT_01129820 != 0) {
      *stateMachine = 0xc; // skip to EXIT
      goto LAB_007dca19;
    }
    FUN_0083b330(0); // setGamePaused(0)
    if ((*(byte *)(stateMachine + 1) & 0x20) != 0) {
      FUN_0088d640(); // enableInput()
      DAT_0112e241 = 1;
    }
    *stateMachine = 1; // transition to LOADING
    iVar4 = DAT_01223394;
    cVar3 = FUN_008a4380(); // isMultiplayer()
    if (cVar3 == '\\0') {
      if ((*(int *)(iVar4 + 0x58) == 1) || (*(char *)(iVar4 + 0x54) == '\\0')) {
        FUN_0040c1f0(0xff000000,0x3f800000,0,1); // fadeToBlack(0xff000000, 1.0, 0, 1)
      }
    }
    else {
      FUN_0040c1f0(0xff000000,0,0,1); // fadeToBlack(0xff000000, 0, 0, 1)
    }
    break;
  case 1: // LOADING state
    cVar3 = FUN_0068c530(); // isLoadingComplete()
    if (cVar3 != '\\0') {
LAB_007dc522:
      *stateMachine = 2; // transition to GAME_LOADED
      return 1;
    }
    if ((*(int *)(iVar4 + 0x58) == 1) || (*(char *)(iVar4 + 0x54) == '\\0')) {
      FUN_0040c1f0(0xff000000,0,0,1); // fadeToBlack(0xff000000, 0, 0, 1)
      goto LAB_007dc522;
    }
    break;
  case 2: // GAME_LOADED state
    if ((*(byte *)(stateMachine + 1) & 3) != 0) {
      FUN_006fe030(); // initGameplaySystems()
    }
    if ((stateMachine[1] & 0x108U) != 0) {
      FUN_0083b340(); // setGamePaused(1)
    }
    if ((stateMachine[1] & 0x300U) != 0) {
      FUN_006af760(); // initAudioSystems()
    }
    gameManager[0x129] = gameManager[0x129] | 1; // set flag +0x129 bit 0
    DAT_00e518a0 = 0;
    (**(code **)(*gameManager + 0x7c))(); // gameManager->vtable[0x7c]()
    FUN_007d5440(gameManager); // initGameState(gameManager)
    iVar4 = FUN_0072dc00(gameManager); // getPlayerObject(gameManager)
    if ((iVar4 != 0) && (*(int *)(iVar4 + 0x20) != 0)) {
      FUN_00998270(); // initPlayerCamera()
    }
    (**(code **)(*gameManager + 0x2c))(stateMachine + 0x10); // gameManager->vtable[0x2c](&stateMachine[0x10])
    FUN_007f89d0(&DAT_00d6f418); // updateTimer(&DAT_00d6f418)
    if ((*(byte *)(stateMachine + 1) & 0x80) != 0) {
      FUN_0073b040(gameManager); // initMissionSystem(gameManager)
      iVar4 = FUN_009a9460(); // getCurrentMission()
      if (iVar4 != 0) {
        FUN_009ab270(0,0); // startMission(0, 0)
      }
    }
    if (gameManager[0x92d] != 0) {
      FUN_004daf90(gameManager + 0x92d); // deleteObject(gameManager + 0x92d)
      gameManager[0x92d] = 0;
    }
    (**(code **)(*gameManager + 0x2dc))(); // gameManager->vtable[0x2dc]()
    cVar3 = FUN_00690210(8); // isSoundPlaying(8)
    if (cVar3 != '\\0') {
      FUN_0079d520(); // stopSound()
      FUN_006901e0(8); // playSound(8)
    }
    FUN_006901e0(0x1a); // playSound(0x1a)
    gameManager[0x216] = 4; // set some state +0x216 to 4
    if (*(int *)(stateMachine + 10) != 0) {
      uVar7 = 0;
      iVar4 = FUN_0088daf0(); // getNumPlayers()
      if (iVar4 != 0) {
        do {
          iVar4 = FUN_0088db00(uVar7); // getPlayerByIndex(uVar7)
          iVar5 = FUN_007dc020(&stack0x00000000); // getPlayerSlot()
          if (iVar5 == -1) {
            *(undefined1 *)(iVar4 + 0xad) = 0; // set player ready flag
          }
          uVar7 = uVar7 + 1;
          uVar6 = FUN_0088daf0(); // getNumPlayers()
        } while (uVar7 < uVar6);
      }
    }
    if ((stateMachine[1] & 0x100U) != 0) {
      FUN_00897e60(); // initHUD()
      FUN_00440b80(0); // setPauseMenu(0)
      *(undefined1 *)(stateMachine + 0x34) = 1;
      FUN_007dc070(); // initGameplay()
      FUN_0088d640(); // enableInput()
      DAT_0112e241 = 1;
    }
    FUN_0088d5c0(); // enableRendering()
    DAT_0112e240 = 1;
    DAT_00e54265 = 0;
    FUN_00444d90(); // resetCamera()
    if ((*(byte *)(stateMachine + 1) & 1) != 0) {
      FUN_007a4250(0); // showMenu(0)
      FUN_00402050(&DAT_0112b36c,0); // setGlobalFlag(&DAT_0112b36c, 0)
    }
    if ((*(byte *)(stateMachine + 1) & 4) != 0) {
      (**(code **)(*gameManager + 0x260))(); // gameManager->vtable[0x260]()
    }
    FUN_00426450(gameManager[0x925]); // deleteTexture(gameManager[0x925])
    FUN_0083b330(1); // setGamePaused(1)
    *stateMachine = 3; // transition to WAITING_FOR_PLAYERS
    return 1;
  case 3: // WAITING_FOR_PLAYERS state
    cVar3 = FUN_004035a0(); // areAllPlayersReady()
    if (cVar3 == '\\0') goto LAB_007dc779;
    uVar7 = 0;
    *stateMachine = 4; // transition to PLAYERS_READY
    if (*(int *)(stateMachine + 10) == 0) {
      return 1;
    }
    piVar8 = (int *)(stateMachine + 2);
    do {
      uVar7 = uVar7 + 1;
      *(undefined1 *)(*piVar8 + 0xad) = 1; // set player ready flag
      piVar8 = piVar8 + 1;
    } while (uVar7 < *(uint *)(stateMachine + 10));
    break;
  case 4: // PLAYERS_READY state
    cVar3 = FUN_004035a0(); // areAllPlayersReady()
    if (cVar3 != '\\0') {
      *stateMachine = 5; // transition to GAME_STARTING
      return 1;
    }
LAB_007dc779:
    if ((char)stateMachine[0x34] != '\\0') {
      *(undefined1 *)(stateMachine + 0x34) = 0;
      FUN_00440b80(0); // setPauseMenu(0)
    }
    break;
  case 5: // GAME_STARTING state
    if ((char)stateMachine[0x34] != '\\0') {
      *(undefined1 *)(stateMachine + 0x34) = 0;
      FUN_00440b80(0); // setPauseMenu(0)
    }
    *stateMachine = 6; // transition to GAME_RUNNING
    return 1;
  case 6: // GAME_RUNNING state
    cVar3 = FUN_008fc7b0(); // isGameOver()
    if (cVar3 == '\\0') {
      if ((*(byte *)(stateMachine + 1) & 0x10) == 0) {
        DAT_0112e241 = 0;
      }
      *stateMachine = 7; // transition to GAME_OVER
      return 1;
    }
    break;
  case 7: // GAME_OVER state
    cVar3 = FUN_004035a0(); // areAllPlayersReady()
    if (cVar3 != '\\0') {
      if ((stateMachine[1] & 1U) == 0) {
        if ((stateMachine[1] & 0x40U) != 0) {
          FUN_006901e0(0x28); // playSound(0x28)
        }
      }
      else {
        FUN_007984b0(); // showVictoryScreen()
      }
      FUN_006901e0(0x27); // playSound(0x27)
      if ((*(byte *)(stateMachine + 1) & 0x42) != 0) {
        iVar4 = gameManager[0xa53];
        while (1 < iVar4) {
          FUN_0079d520(); // stopSound()
          iVar4 = gameManager[0xa53];
        }
      }
      *stateMachine = 8; // transition to GAME_OVER_DONE
      return 1;
    }
    break;
  case 8: // GAME_OVER_DONE state
    cVar3 = FUN_004035a0(); // areAllPlayersReady()
    if (cVar3 != '\\0') {
      DAT_00e518a0 = 1;
      DAT_0112e240 = 0;
      DAT_00e54265 = 1;
      FUN_007f89d0(&DAT_00d6f418); // updateTimer(&DAT_00d6f418)
      gameManager[0x129] = gameManager[0x129] & 0xfffffffe; // clear flag +0x129 bit 0
      uVar2 = DAT_00d6f444;
      *stateMachine = 9; // transition to WAITING_FOR_RESTART
      *(undefined4 *)(stateMachine + 0x36) = uVar2;
      return 1;
    }
    break;
  case 9: // WAITING_FOR_RESTART state
    cVar3 = FUN_004035a0(); // areAllPlayersReady()
    if (cVar3 == '\\0') {
      stateMachine[0x35] = 0;
      fVar10 = *(float *)(stateMachine + 0x36) - DAT_012067e8;
      *(float *)(stateMachine + 0x36) = fVar10;
      bVar9 = 0.0 < fVar10;
    }
    else {
      stateMachine[0x35] = stateMachine[0x35] + 1;
      bVar9 = (ushort)stateMachine[0x35] < 4;
    }
    if (!bVar9) {
      FUN_00402050(&DAT_0112b344,0); // setGlobalFlag(&DAT_0112b344, 0)
      if ((stateMachine[1] & 0x1000U) == 0) {
        *stateMachine = 10; // transition to RESTARTING
        cVar3 = FUN_008a4380(); // isMultiplayer()
        if ((cVar3 != '\\0') &&
           (cVar3 = FUN_0040b8d0(*(undefined4 *)(DAT_01223394 + 0x4c)), cVar3 == '\\0')) {
          FUN_009cb3d0(); // showMultiplayerResults()
        }
        FUN_0040c2c0(0xff000000,0x3f800000,0,1); // fadeToBlack(0xff000000, 1.0, 0, 1)
      }
      else {
        *stateMachine = 0xb; // transition to EXITING
      }
      psVar1 = stateMachine + 0x30;
      if (*(int *)(stateMachine + 0x30) != 0) {
        FUN_0045ca00(gameManager); // cleanupGameState(gameManager)
        FUN_0045c400(psVar1,local_c,0); // serializeState(psVar1, local_c, 0)
        FUN_00408310(psVar1); // destroyObject(psVar1)
        psVar1[0] = 0;
        psVar1[1] = 0;
        FUN_0045cac0(); // finalizeCleanup()
      }
    }
    break;
  case 10: // RESTARTING state
    cVar3 = FUN_007dbef0(); // isRestartComplete()
    if (cVar3 != '\\0') {
      *stateMachine = 0xb; // transition to EXITING
      return 1;
    }
    break;
  case 0xb: // EXITING state
    FUN_0079d520(); // stopSound()
    FUN_00402050(&DAT_0112b564,0); // setGlobalFlag(&DAT_0112b564, 0)
    *stateMachine = 0xc; // transition to EXIT
    if (((stateMachine[1] & 0x800U) == 0) || (*(int *)(DAT_011299bc + 0x1c) == 0)) goto LAB_007dca19;
    FUN_00839990(); // showExitScreen()
  }
  if (*stateMachine != 0xc) {
    return 1;
  }
LAB_007dca19:
  gameManager[0x928] = gameManager[0x928] & 0xffffff7f; // clear flag +0x928 bit 7
  gameManager[0x927] = gameManager[0x927] & 0xffffffbf; // clear flag +0x927 bit 6
  return 0;
}