// FUNC_NAME: GodfatherGameManager::handleGameStateChange
undefined1 __thiscall GodfatherGameManager::handleGameStateChange(int this, undefined4 param_2, float param_3, undefined4 param_4, int gameState, undefined4 param_6)

{
  float10 fVar1;
  char cVar2;
  undefined1 uVar3;
  float *pfVar4;
  int *piVar5;
  int iVar6;
  ushort *puVar7;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float local_c;
  float local_8;
  float local_4;
  
  uVar3 = 1;
  switch(gameState + -10) {
  case 0: // GameState 10 - likely "game over" or similar
    *(undefined4 *)(this + 0x7c) = DAT_00d5ccf8;
    return 1;
  case 1: // GameState 11 - probably "start mission"
    FUN_0086d740();
    piVar5 = (int *)FUN_006c12a0(*(undefined4 *)(*(int *)(this + 0x54) + 4),0x10e5319e);
    if (piVar5 != (int *)0x0) {
      (**(code **)(*piVar5 + 0x28c))(1);
      FUN_00862460();
      iVar6 = FUN_00471610();
      FUN_00868b20(1,iVar6 + 0x20);
      return 1;
    }
    break;
  case 2: // GameState 12
    FUN_0086f470(param_3);
    return 1;
  case 3: // GameState 13
    FUN_0086e360();
  case 0x12: // GameState 28
    cVar2 = FUN_0086fcc0();
    if (cVar2 != '\0') {
      *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) | 2;
      return 1;
    }
  case 7: // GameState 17
    *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) & 0xfffffffd;
    return 1;
  case 4: // GameState 14 - probably "entering/exiting vehicle"
    *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) | 1;
    pfVar4 = (float *)FUN_0086d5a0();
    local_c = *(float *)(this + 0x70) - *pfVar4;
    local_8 = *(float *)(this + 0x74) - pfVar4[1];
    local_4 = *(float *)(this + 0x78) - pfVar4[2];
    FUN_0043a210(&local_c,&local_c);
    param_3 = 2.8026e-45;
    FUN_0086cbc0(&param_3);
    if (param_3 != 0.0) {
      *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) & 0xffffffdf;
      return 1;
    }
    *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) | 0x20;
    return 1;
  case 5: // GameState 15
    FUN_0086f5c0(param_3,1);
    return 1;
  case 6: // GameState 16
    FUN_0086e110();
    return 1;
  case 8: // GameState 18
    FUN_0086d740();
    FUN_00624d00();
    return 1;
  case 9: // GameState 19
    FUN_0086d740();
    FUN_004088c0(*(int *)(this + 0x5c) + 0x3c);
    return 1;
  case 10: // GameState 20 - probably "update timer"
    if ((((~(*(byte *)(*(int *)(this + 0x50) + 200) >> 6) & 1) != 0) &&
        (_DAT_00d5c458 < *(float *)(*(int *)(this + 0x50) + 0x88))) &&
       ((**(code **)(**(int **)(this + 0x5c) + 0x1a8))(), extraout_ST0 < (float10)DAT_00d5ef88))
    {
      *(float *)(this + 0x98) = param_3 + *(float *)(this + 0x98);
      return 1;
    }
    *(undefined4 *)(this + 0x98) = 0;
    return 1;
  case 0xb: // GameState 21
    FUN_0086fe50();
    return 1;
  case 0xc: // GameState 22
    FUN_0086fef0(param_3);
    return 1;
  case 0xd: // GameState 23
    FUN_008704f0(param_3);
    return 1;
  case 0xe: // GameState 24
    FUN_0086d740();
    return 1;
  case 0xf: // GameState 25
    FUN_006b6f90(0x3f800000);
    fVar1 = (float10)DAT_00d5ef70;
    *(float *)(this + 0xb4) = (float)(extraout_ST0_00 + fVar1);
    if ((*(uint *)(this + 0x6c) >> 7 & 1) != 0) {
      *(float *)(this + 0xb4) = (float)(extraout_ST0_00 + fVar1) + DAT_00d5ddec;
      return 1;
    }
    break;
  case 0x10: // GameState 26
    FUN_0086b7d0(0x3f800000);
    FUN_0086b7f0(0);
    FUN_0086b7b0(0);
    return 1;
  case 0x11: // GameState 27
    (**(code **)(**(int **)(this + 0x50) + 0x44))();
    puVar7 = (ushort *)(*(int *)(this + 0x50) + 200);
    *puVar7 = *puVar7 & 0xfff7;
    return 1;
  case 0x13: // GameState 29
    FUN_0086e9c0();
    return 1;
  default:
    uVar3 = FUN_004ac700(param_2,param_3,param_4,gameState,param_6);
  }
  return uVar3;
}