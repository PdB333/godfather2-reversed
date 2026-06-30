// FUNC_NAME: HavokWheeledVehicle::updateSuspensionForces
undefined4 FUN_006626f0(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_30 [3];
  void *local_24;
  undefined1 local_20 [16];
  undefined1 local_10 [16];
  
  local_24 = _calloc(4,0x40);
  if (local_24 == (void *)0x0) {
    iVar2 = 0;
    while ((&DAT_00e2747c)[iVar2 * 2] != -2) {
      iVar2 = iVar2 + 1;
      if (2 < iVar2) {
        return 1;
      }
    }
  }
  else {
    local_30[0] = 0;
    local_30[1] = 0x40;
    local_30[2] = 0;
    iVar1 = FUN_00665ce0();
    if (iVar1 == 0) {
      if (local_30[0] != 0) {
        local_30[2] = (int)(*(int *)(param_2 + 0x18) == 0);
      }
      iVar1 = FUN_00668850(local_30,param_4);
      if (iVar1 == 0) {
        iVar2 = FUN_00665bd0();
        if ((iVar2 == 0) &&
           ((iVar2 = FUN_00665bd0(), iVar2 == 0 || (iVar2 = FUN_00665bd0(), iVar2 == 0)))) {
          FUN_00665b40();
          uVar3 = FUN_006624a0(param_1,param_3,param_5);
          return uVar3;
        }
        iVar2 = FUN_00667820(local_10,local_20,0);
        if (iVar2 != 0) {
          FUN_00665b40();
          uVar3 = FUN_0066cf40();
          return uVar3;
        }
        iVar2 = FUN_0066a780(param_1,param_2);
        if ((iVar2 == 0) &&
           (((iVar2 = FUN_00665c00(), iVar2 != -1 || (iVar2 = FUN_006657c0(local_30), iVar2 == 0))
            && (iVar2 = FUN_00667910(param_4,local_30), iVar2 == 0)))) {
          iVar2 = FUN_0066a780(param_1 + 0x10,param_2 + 0x10);
          if ((iVar2 == 0) &&
             ((((iVar2 = FUN_00665c00(), iVar2 != -1 || (iVar2 = FUN_006657c0(local_20), iVar2 == 0)
                ) && ((iVar2 = FUN_00668ce0(local_20,local_30,local_20), iVar2 == 0 &&
                      ((iVar2 = FUN_0066a090(local_20,param_4,param_5), iVar2 == 0 &&
                       (iVar2 = FUN_0066a660(local_20,local_30), iVar2 == 0)))))) &&
              (iVar2 = FUN_0066a090(local_30,param_4,param_5), iVar2 == 0)))) {
            iVar2 = FUN_0066a780(local_30,param_1);
            if (iVar2 == 0) {
              iVar2 = FUN_0066a780(local_30,param_2);
              if (iVar2 == 0) {
                iVar2 = FUN_0066a780(param_1,local_10);
                if ((((iVar2 == 0) && (iVar2 = FUN_00668ce0(local_30,local_20,local_30), iVar2 == 0)
                     ) && (iVar2 = FUN_0066a8d0(local_30,param_1 + 0x10,param_4,param_3 + 0x10),
                          iVar2 == 0)) && (iVar2 = FUN_00668850(local_10,param_4), iVar2 == 0)) {
                  uVar3 = 0;
                  goto LAB_006629f5;
                }
              }
            }
          }
        }
        uVar3 = FUN_0066cf40();
LAB_006629f5:
        FUN_00665b80(local_20,local_10,local_30,0);
        return uVar3;
      }
    }
    FUN_00665b40();
    iVar2 = 0;
    while (iVar1 != (&DAT_00e2747c)[iVar2 * 2]) {
      iVar2 = iVar2 + 1;
      if (2 < iVar2) {
        return 1;
      }
    }
  }
  return *(undefined4 *)(&UNK_00e27480 + iVar2 * 8);
}