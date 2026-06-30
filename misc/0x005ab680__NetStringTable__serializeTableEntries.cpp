// FUNC_NAME: NetStringTable::serializeTableEntries
void NetStringTable::serializeTableEntries(int param_1, int *param_2)

{
  int iVar1;
  undefined *puStack_30;
  undefined8 *puStack_2c;
  char *pcStack_28;
  int local_24 [2];
  undefined8 *local_1c;
  undefined8 local_18;
  undefined8 uStack_10;
  
  FUN_005a0980(); // likely beginWrite or stream start
  FUN_005a1060(); // likely writeInt or version header
  if ((local_1c != &local_18) && (local_1c != (undefined8 *)0x0)) {
    (*DAT_0119caf4)(local_1c); // operator delete or free
  }
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 0x54)) { // +0x54: entryCount
    do {
      if (*(int *)(*(int *)(param_1 + 0x4c) + iVar1 * 4) != 0) { // +0x4c: entryArray
        local_24[0] = 0;
        local_24[1] = 0;
        local_1c = &local_18;
        local_18 = 0;
        uStack_10 = 0;
        FUN_005a92b0(local_24); // likely getString or resolveString
        pcStack_28 = (char *)(param_2[2] + *param_2); // param_2 is BitStream: [0]=bitPosition, [2]=buffer
        puStack_30 = (undefined *)((int)local_1c + local_24[0]);
        puStack_2c = local_1c;
        FUN_005aba20(&puStack_2c,&puStack_30); // likely writeString or writeBits
        if ((local_1c != &local_18) && (local_1c != (undefined8 *)0x0)) {
          (*DAT_0119caf4)(local_1c);
        }
      }
      if (iVar1 < *(int *)(param_1 + 0x54) + -1) {
        pcStack_28 = ",";
        puStack_2c = (undefined8 *)&DAT_00e3c9fc;
        do {
          pcStack_28 = pcStack_28 + 1;
        } while (*pcStack_28 != '\0');
        puStack_30 = (undefined *)(param_2[2] + *param_2);
        FUN_005aba20(&puStack_2c,&pcStack_28); // write delimiter
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(param_1 + 0x54));
  }
  return;
}