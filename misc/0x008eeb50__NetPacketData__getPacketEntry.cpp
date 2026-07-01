// FUNC_NAME: NetPacketData::getPacketEntry
undefined4 * __thiscall NetPacketData::getPacketEntry(int this, undefined4 *outEntry, int param3, int param4, uint *packetNumber)
{
  int iVar1;
  char cVar2;
  undefined4 *puVar3;
  bool bVar4;
  int local_c;
  undefined4 local_8;
  
  if (*(int *)(this + 8) == 0) {
    FUN_008ed110(outEntry,1,*(undefined4 *)(this + 4),packetNumber);
    return outEntry;
  }
  iVar1 = **(int **)(this + 4);
  if ((param3 == 0) || (param3 != this)) {
    FUN_00b97aea();
  }
  if (param4 == iVar1) {
    if (*packetNumber < *(uint *)(param4 + 0xc)) {
      FUN_008ed110(outEntry,1,param4,packetNumber);
      return outEntry;
    }
  }
  else {
    iVar1 = *(int *)(this + 4);
    if ((param3 == 0) || (param3 != this)) {
      FUN_00b97aea();
    }
    if (param4 == iVar1) {
      iVar1 = *(int *)(*(int *)(this + 4) + 8);
      if (*(uint *)(iVar1 + 0xc) < *packetNumber) {
        FUN_008ed110(outEntry,0,iVar1,packetNumber);
        return outEntry;
      }
    }
    else {
      bVar4 = *(uint *)(param4 + 0xc) < *packetNumber;
      if (*packetNumber < *(uint *)(param4 + 0xc)) {
        FUN_008ea580();
        if (*(uint *)(param4 + 0xc) < *packetNumber) {
          if (*(char *)(*(int *)(param4 + 8) + 0x25) != '\0') {
            FUN_008ed110(outEntry,0,param4,packetNumber);
            return outEntry;
          }
          FUN_008ed110(outEntry,1,param4,packetNumber);
          return outEntry;
        }
        bVar4 = *(uint *)(param4 + 0xc) < *packetNumber;
      }
      if (bVar4) {
        local_8 = *(undefined4 *)(this + 4);
        local_c = this;
        FUN_008ea1d0();
        cVar2 = FUN_008ea1a0(&local_c);
        if ((cVar2 != '\0') || (*packetNumber < *(uint *)(param4 + 0xc))) {
          if (*(char *)(*(int *)(param4 + 8) + 0x25) != '\0') {
            FUN_008ed110(outEntry,0,param4,packetNumber);
            return outEntry;
          }
          FUN_008ed110(outEntry,1,param4,packetNumber);
          return outEntry;
        }
      }
    }
  }
  puVar3 = (undefined4 *)FUN_008ee360(&local_c,packetNumber);
  *outEntry = *puVar3;
  outEntry[1] = puVar3[1];
  return outEntry;
}