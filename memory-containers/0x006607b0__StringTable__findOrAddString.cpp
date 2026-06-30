// FUNC_NAME: StringTable::findOrAddString
int StringTable::findOrAddString(void)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  
  puVar1 = PTR_FUN_00e274bc; // pointer to string data (likely +0x14 offset from base)
  iVar2 = 0;
  pbVar7 = (byte *)&DAT_01206408; // start of string table entries (each 0x14 bytes)
  do {
    uVar3 = 0x14; // size of each entry (20 bytes)
    pbVar6 = &DAT_00e274ac; // pointer to the string being searched for
    pbVar8 = pbVar7;
    do {
      if (*(int *)pbVar8 != *(int *)pbVar6) goto LAB_006607e8; // compare first 4 bytes
      uVar3 = uVar3 - 4;
      pbVar6 = pbVar6 + 4;
      pbVar8 = pbVar8 + 4;
    } while (3 < uVar3); // loop until all 20 bytes compared
    if (uVar3 == 0) {
LAB_00660845:
      iVar4 = 0; // exact match found
    }
    else {
LAB_006607e8:
      iVar9 = (uint)*pbVar8 - (uint)*pbVar6; // byte-by-byte comparison for remaining bytes
      if (iVar9 == 0) {
        if (uVar3 == 1) goto LAB_00660845;
        iVar9 = (uint)pbVar8[1] - (uint)pbVar6[1];
        if (iVar9 == 0) {
          if (uVar3 == 2) goto LAB_00660845;
          iVar9 = (uint)pbVar8[2] - (uint)pbVar6[2];
          if (iVar9 == 0) {
            if ((uVar3 == 3) || (iVar9 = (uint)pbVar8[3] - (uint)pbVar6[3], iVar9 == 0))
            goto LAB_00660845;
          }
        }
      }
      iVar4 = 1;
      if (iVar9 < 1) {
        iVar4 = -1;
      }
    }
    if (iVar4 == 0) {
      return iVar2; // found existing entry, return its index
    }
    pbVar7 = pbVar7 + 0x14; // move to next entry
    iVar2 = iVar2 + 1;
    if (0x1206687 < (int)pbVar7) { // check if past end of table
      iVar2 = 0;
      piVar5 = &DAT_01206408;
      do {
        if (*piVar5 == 0) { // find empty slot (first 4 bytes zero)
          *(undefined8 *)(&DAT_01206408 + iVar2 * 5) = _DAT_00e274ac; // copy string data (first 8 bytes)
          *(undefined8 *)(&DAT_01206410 + iVar2 * 0x14) = DAT_00e274b4; // copy next 8 bytes
          *(undefined **)(&DAT_01206418 + iVar2 * 0x14) = puVar1; // copy pointer
          return iVar2; // return index of new entry
        }
        piVar5 = piVar5 + 5; // advance by 5 ints (0x14 bytes)
        iVar2 = iVar2 + 1;
      } while ((int)piVar5 < 0x1206688); // check bounds
      return -1; // table full
    }
  } while( true );
}