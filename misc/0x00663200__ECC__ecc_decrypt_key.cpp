// FUNC_NAME: ECC::ecc_decrypt_key
undefined4 __thiscall ECC::ecc_decrypt_key(uint keyIdx, undefined4 param_2, undefined4 *outParams)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int in_EAX;
  int iVar3;
  void *_Memory;
  int iVar4;
  undefined4 uVar5;
  char *_Format;
  undefined1 auStack_94 [16];
  undefined1 local_84 [132];
  
  if (outParams == (undefined4 *)0x0) {
    _Format = "_ARGCHK '%s' failure on line %d of file %s\n";
    iVar3 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","key != NULL",0x253,
                         "..\\src\\libtomcrypt\\ecc.c");
    _fprintf((FILE *)(iVar3 + 0x40),_Format);
  }
  if ((0x1f < keyIdx) || ((&DAT_01206408)[keyIdx * 5] == 0)) {
    return 0xc;
  }
  iVar3 = 0;
  if (0x14 < in_EAX) {
    iVar4 = 0x14;
    do {
      if (iVar4 == 0) break;
      iVar3 = iVar3 + 1;
      iVar4 = (&DAT_00e279c0)[iVar3 * 7];
    } while (iVar4 < in_EAX);
  }
  iVar4 = (&DAT_00e279c0)[iVar3 * 7];
  if (iVar4 == 0) {
    return 3;
  }
  outParams[1] = iVar3;
  iVar3 = (**(code **)(&DAT_01206418 + keyIdx * 0x14))(local_84,iVar4,param_2);
  if (iVar3 != iVar4) {
    return 9;
  }
  puVar1 = outParams + 10;
  puVar2 = outParams + 2;
  iVar3 = FUN_00667820(puVar2,outParams + 6,puVar1,auStack_94,0);
  if (iVar3 == 0) {
    _Memory = _malloc(0x20);
    if (_Memory != (void *)0x0) {
      iVar3 = FUN_00667820(_Memory,(int)_Memory + 0x10,0);
      if (iVar3 == 0) {
        iVar3 = FUN_00669f00((&PTR_s_G00000000000000000000000007_00e279c8)[outParams[1] * 7],0x40);
        if (iVar3 == 0) {
          iVar3 = FUN_00669f00((&PTR_s_jpqOf1BHus6Yd_pyhyVpP_00e279d4)[outParams[1] * 7],0x40);
          if (iVar3 == 0) {
            iVar3 = FUN_00669f00((&PTR_s_D_wykuuIFfr_vPyx7kQEPu8MixO_00e279d8)[outParams[1] * 7],0x40)
            ;
            if (iVar3 == 0) {
              iVar3 = FUN_0066a010(local_84);
              if (iVar3 == 0) {
                iVar3 = FUN_00662a30(puVar1,_Memory,puVar2,auStack_94);
                if (iVar3 == 0) {
                  *outParams = 0;
                  iVar3 = FUN_0066a620();
                  if (iVar3 == 0) {
                    iVar3 = FUN_0066a620();
                    if (iVar3 == 0) {
                      iVar3 = FUN_0066a620();
                      if (iVar3 == 0) {
                        uVar5 = 0;
                        goto LAB_0066342a;
                      }
                    }
                  }
                }
              }
            }
          }
        }
        uVar5 = 0xd;
LAB_0066342a:
        FUN_00665b80(_Memory,(int)_Memory + 0x10,0);
        _free(_Memory);
        FUN_00665b40();
        return uVar5;
      }
      _free(_Memory);
    }
    FUN_00665b80(puVar2,outParams + 6,puVar1,auStack_94,0);
  }
  return 0xd;
}