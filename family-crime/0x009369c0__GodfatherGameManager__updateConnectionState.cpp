// FUNC_NAME: GodfatherGameManager::updateConnectionState
void __fastcall GodfatherGameManager::updateConnectionState(int this)
{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  if (DAT_01206978 != 0) {
    FUN_00408900(this + 0x4c, &DAT_01206978, 0x8000);
  }
  if (((((DAT_01130590 >> 0xd & 1) != 0) || ((DAT_01130590 >> 5 & 1) != 0)) ||
      ((DAT_01130590 >> 0xf & 1) != 0)) ||
     (((DAT_01130590 >> 0xb & 1) != 0 || ((DAT_01130590 >> 0x12 & 1) != 0)))) {
    FUN_00983190();
    iVar1 = FUN_009c8e50(0xf0);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = FUN_00982280(0);
    }
    *(undefined4 *)(iVar1 + 0xc) = 0xb;
    FUN_00982400(1);
    *(code **)(iVar1 + 0x14) = FUN_00982b30;
    if ((DAT_01130590 >> 0xd & 1) == 0) {
      if ((DAT_01130590 >> 5 & 1) == 0) {
        if ((DAT_01130590 >> 0xf & 1) == 0) {
          if ((DAT_01130590 >> 0x12 & 1) == 0) {
            pcVar3 = "$mp_lost_conn_host_left_returned";
          }
          else {
            pcVar3 = "$mp_don_match_failed_to_start";
          }
        }
        else {
          pcVar3 = "$mp_lost_conn_game_return";
        }
      }
      else {
        pcVar3 = "$mp_lost_conn_returned_to_main";
      }
    }
    else {
      pcVar3 = "$mp_sign_in_change_returned_to_title";
    }
    FUN_00981eb0(pcVar3);
    DAT_01130590 = DAT_01130590 & 0xfffb57df;
    FUN_00982e10();
  }
  if ((DAT_01130590 >> 0x13 & 1) != 0) {
    DAT_01130590 = DAT_01130590 & 0xfff7ffff;
    *(uint *)(DAT_01129930 + 0x6f4) = *(uint *)(DAT_01129930 + 0x6f4) | 0x80000;
  }
  *(undefined4 *)(this + 0x60) = 0;
  if ((DAT_01130590 & 1) == 0) {
    FUN_005c0d50(this + 0x14, &LAB_00931e00, 0);
    DAT_01130590 = DAT_01130590 | 1;
  }
  if (((DAT_01223484 != 0) &&
      (*(int *)(DAT_01223484 + 0x28) != 0 || *(int *)(DAT_01223484 + 0x2c) != 0)) &&
     (DAT_01223484 != -0x28)) {
    FUN_00936790();
  }
  uVar2 = FUN_00602e60(0xffffffff);
  FUN_005a04a0("SetLanguageCode", 0, &DAT_00d8963c, 1, uVar2);
  local_c = DAT_01130470;
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c, 0);
  return;
}