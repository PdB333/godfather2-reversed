// FUNC_NAME: GodfatherGameManager::processGameState
undefined4 GodfatherGameManager::processGameState(int this)

{
  int state;
  int iVar1;
  undefined4 result;
  undefined1 local_30 [16];
  undefined1 local_20 [16];
  undefined1 local_10 [16];
  
  state = FUN_00667820(local_30,local_20,local_10,0);
  if (state != 0) {
    iVar1 = 0;
    do {
      if (state == (&DAT_00e2747c)[iVar1 * 2]) {
        return *(undefined4 *)(&UNK_00e27480 + iVar1 * 8);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 3);
    return 1;
  }
  iVar1 = FUN_00668da0(this + 0x10,local_20);
  if (iVar1 == 0) {
    iVar1 = FUN_00667910();
    if (iVar1 == 0) {
      iVar1 = FUN_0066a660(this,local_30);
      if (iVar1 == 0) {
        iVar1 = FUN_0066a090(local_30);
        if (iVar1 == 0) {
          iVar1 = FUN_00668f50(local_30,3,local_30);
          if (iVar1 == 0) {
            iVar1 = FUN_0066a7f0(local_30,3,local_30);
            if (iVar1 == 0) {
              iVar1 = FUN_00665c00();
              if (iVar1 == -1) {
                iVar1 = FUN_006657c0(local_30);
                if (iVar1 != 0) goto LAB_006626a0;
              }
              iVar1 = FUN_00668ce0(local_30,local_20,local_30);
              if (iVar1 == 0) {
                iVar1 = FUN_0066a090(local_30);
                if (iVar1 == 0) {
                  iVar1 = FUN_0066a660(local_30,local_10);
                  if (iVar1 == 0) {
                    iVar1 = FUN_0066a090(local_10);
                    if (iVar1 == 0) {
                      iVar1 = FUN_0066a780(local_10,this);
                      if (iVar1 == 0) {
                        iVar1 = FUN_0066a8d0(local_10,this);
                        if (iVar1 == 0) {
                          iVar1 = FUN_0066a780(this,local_10);
                          if (iVar1 == 0) {
                            iVar1 = FUN_00668ce0(local_20,local_30,local_20);
                            if (iVar1 == 0) {
                              iVar1 = FUN_0066a8d0(local_20,this + 0x10);
                              if (iVar1 == 0) {
                                iVar1 = FUN_00665ce0();
                                if (iVar1 == 0) {
                                  result = 0;
                                  goto LAB_006626c5;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_006626a0:
  iVar1 = 0;
  do {
    if (state == (&DAT_00e2747c)[iVar1 * 2]) {
      result = *(undefined4 *)(&UNK_00e27480 + iVar1 * 8);
      goto LAB_006626c5;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 3);
  result = 1;
LAB_006626c5:
  FUN_00665b80(local_10,local_20,local_30,0);
  return result;
}