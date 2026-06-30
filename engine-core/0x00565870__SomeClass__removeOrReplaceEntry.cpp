// FUNC_NAME: SomeClass::removeOrReplaceEntry
void SomeClass::removeOrReplaceEntry(byte *param_1)
{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  int unaff_ESI;
  int iVar6;
  bool bVar7;
  
  iVar6 = 0;
  pbVar2 = (byte *)(unaff_ESI + 0x23c); // +0x23c: first entry string (or key)
  pbVar4 = param_1;
  pbVar5 = pbVar2;
LAB_00565884:
  do {
    bVar1 = *pbVar2;
    bVar7 = bVar1 < *pbVar4;
    if (bVar1 == *pbVar4) {
      if (bVar1 != 0) {
        bVar1 = pbVar2[1];
        bVar7 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_005658a4;
        pbVar2 = pbVar2 + 2;
        pbVar4 = pbVar4 + 2;
        if (bVar1 != 0) goto LAB_00565884;
      }
      iVar3 = 0;
    }
    else {
LAB_005658a4:
      iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
    }
    if (iVar3 == 0) {
      // Found matching entry: call some function with param_1
      FUN_00569b40(*(undefined4 *)(unaff_ESI + 0x20),param_1); // +0x20: some pointer
      // Call virtual function at vtable+4
      (**(code **)(**(int **)(unaff_ESI + 0x128) + 4))(param_1); // +0x128: vtable pointer
      iVar3 = *(int *)(iVar6 * 0x84 + 700 + unaff_ESI);
      iVar6 = iVar6 * 0x84 + unaff_ESI;
      *(undefined1 *)(iVar6 + 0x23c) = 0; // Clear the entry string
      // Decrement counters if the removed entry index is less than the current count
      if ((*(char *)(unaff_ESI + 0x23c) != '\0') && (iVar3 < *(int *)(unaff_ESI + 700))) {
        *(int *)(unaff_ESI + 700) = *(int *)(unaff_ESI + 700) + -1; // +0x2bc: count1
      }
      if ((*(char *)(unaff_ESI + 0x2c0) != '\0') && (iVar3 < *(int *)(unaff_ESI + 0x340))) {
        *(int *)(unaff_ESI + 0x340) = *(int *)(unaff_ESI + 0x340) + -1; // +0x340: count2
      }
      if ((*(char *)(unaff_ESI + 0x344) != '\0') && (iVar3 < *(int *)(unaff_ESI + 0x3c4))) {
        *(int *)(unaff_ESI + 0x3c4) = *(int *)(unaff_ESI + 0x3c4) + -1; // +0x3c4: count3
      }
      if ((*(char *)(unaff_ESI + 0x3c8) != '\0') && (iVar3 < *(int *)(unaff_ESI + 0x448))) {
        *(int *)(unaff_ESI + 0x448) = *(int *)(unaff_ESI + 0x448) + -1; // +0x448: count4
      }
      if ((*(char *)(unaff_ESI + 0x44c) != '\0') && (iVar3 < *(int *)(unaff_ESI + 0x4cc))) {
        *(int *)(unaff_ESI + 0x4cc) = *(int *)(unaff_ESI + 0x4cc) + -1; // +0x4cc: count5
      }
      *(undefined4 *)(iVar6 + 700) = 0xf; // Set some flag to 0xf
      return;
    }
    iVar6 = iVar6 + 1;
    pbVar2 = pbVar5 + 0x84; // Each entry is 0x84 bytes
    pbVar4 = param_1;
    pbVar5 = pbVar2;
    if (4 < iVar6) { // Max 5 entries (0-4)
      return;
    }
  } while( true );
}