// FUNC_NAME: OnlineServices::initializeOnlineServices
undefined4 OnlineServices::initializeOnlineServices(void)

{
  int iVar1;
  void *pMemory;
  void *pMemory_00;
  int iVar2;
  undefined4 uVar3;
  int local_2c;
  int local_24;
  undefined1 local_20 [16];
  undefined1 local_10 [16];
  
  iVar2 = 0;
  iVar1 = FUN_00667820(local_10,local_20,0); // Initialize some context/state
  if (iVar1 != 0) {
    return 0xd; // Error code 13
  }
  pMemory = _malloc(0x20); // Allocate 32 bytes
  if (pMemory != (void *)0x0) {
    iVar1 = FUN_00667820(pMemory,(int)pMemory + 0x10,0); // Initialize second half of allocation
    if (iVar1 == 0) {
      pMemory_00 = (void *)FUN_00662440(); // Allocate/initialize another structure
      if (pMemory_00 == (void *)0x0) {
        FUN_00665b80(local_10,local_20,0); // Cleanup context
        FUN_00665b80(pMemory,(int)pMemory + 0x10,0); // Cleanup first allocation
        _free(pMemory);
        return 0xd; // Error code 13
      }
      local_24 = 0;
      do {
        // Initialize various online service strings/identifiers
        iVar1 = FUN_00669f00(*(undefined4 *)
                              ((int)&PTR_s_G00000000000000000000000007_00e279c8 + iVar2),0x40);
        if (iVar1 != 0) {
LAB_00663152:
          uVar3 = 0xd; // Error code 13
          goto LAB_0066310c;
        }
        iVar1 = FUN_00669f00(*(undefined4 *)
                              ((int)&PTR_s_G0000000000004sCQUtDxaqDUN5_00e279d0 + iVar2),0x40);
        if (iVar1 != 0) goto LAB_00663152;
        iVar1 = FUN_0066ca40(); // Initialize some service component
        if (iVar1 != 0) goto LAB_00663152;
        if (local_2c == 0) goto LAB_00663159;
        iVar1 = FUN_0066ca40(); // Initialize another service component
        if (iVar1 != 0) goto LAB_00663152;
        if (local_2c == 0) goto LAB_00663159;
        iVar1 = FUN_00669f00(*(undefined4 *)((int)&PTR_s_jpqOf1BHus6Yd_pyhyVpP_00e279d4 + iVar2),
                             0x40);
        if (iVar1 != 0) goto LAB_00663152;
        iVar2 = FUN_00669f00(*(undefined4 *)
                              ((int)&PTR_s_D_wykuuIFfr_vPyx7kQEPu8MixO_00e279d8 + iVar2),0x40);
        if (iVar2 != 0) goto LAB_00663152;
        iVar2 = FUN_00665820(local_20,1,local_20); // Process some data
        if (iVar2 != 0) goto LAB_00663152;
        iVar2 = FUN_00662a30(local_20,pMemory,pMemory_00,local_10); // Perform online operation
        if (iVar2 != 0) goto LAB_00663152;
        iVar2 = FUN_00665bd0(); // Check for completion/timeout
        if (iVar2 != 0) {
LAB_00663159:
          uVar3 = 5; // Error code 5 (timeout?)
          goto LAB_0066310c;
        }
        iVar2 = FUN_00665bd0(); // Check again
        if (iVar2 != 0) goto LAB_00663159;
        local_24 = local_24 + 1;
        iVar2 = local_24 * 0x1c; // 28 bytes per entry
      } while ((&DAT_00e279c0)[local_24 * 7] != 0); // Loop through service table
      uVar3 = 0; // Success
LAB_0066310c:
      FUN_00665b80(pMemory_00,(int)pMemory_00 + 0x10,0); // Cleanup second allocation
      _free(pMemory_00);
      FUN_00665b80(pMemory,(int)pMemory + 0x10,0); // Cleanup first allocation
      _free(pMemory);
      FUN_00665b80(local_20,local_10,0); // Cleanup context
      return uVar3;
    }
    _free(pMemory);
  }
  FUN_00665b80(local_10,local_20,0); // Cleanup context
  return 0xd; // Error code 13
}