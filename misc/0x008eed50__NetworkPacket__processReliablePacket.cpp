// FUNC_NAME: NetworkPacket::processReliablePacket
undefined4 * __thiscall NetworkPacket::processReliablePacket(NetworkPacket *this,undefined4 *outPacket,int param_3,int param_4,uint *param_5)

{
  int iVar1;
  char cVar2;
  undefined4 *puVar3;
  bool bVar4;
  int local_c;
  undefined4 local_8;
  
  if (*(int *)(this + 8) == 0) {
    FUN_008ed3e0(outPacket,1,*(undefined4 *)(this + 4),param_5);
    return outPacket;
  }
  iVar1 = **(int **)(this + 4);
  if ((param_3 == 0) || (param_3 != this)) {
    FUN_00b97aea();
  }
  if (param_4 == iVar1) {
    if (*param_5 < *(uint *)(param_4 + 0xc)) {
      FUN_008ed3e0(outPacket,1,param_4,param_5);
      return outPacket;
    }
  }
  else {
    iVar1 = *(int *)(this + 4);
    if ((param_3 == 0) || (param_3 != this)) {
      FUN_00b97aea();
    }
    if (param_4 == iVar1) {
      iVar1 = *(int *)(*(int *)(this + 4) + 8);
      if (*(uint *)(iVar1 + 0xc) < *param_5) {
        FUN_008ed3e0(outPacket,0,iVar1,param_5);
        return outPacket;
      }
    }
    else {
      bVar4 = *(uint *)(param_4 + 0xc) < *param_5;
      if (*param_5 < *(uint *)(param_4 + 0xc)) {
        FUN_008ea610();
        if (*(uint *)(param_4 + 0xc) < *param_5) {
          if (*(char *)(*(int *)(param_4 + 8) + 0x19) != '\0') {
            FUN_008ed3e0(outPacket,0,param_4,param_5);
            return outPacket;
          }
          FUN_008ed3e0(outPacket,1,param_4,param_5);
          return outPacket;
        }
        bVar4 = *(uint *)(param_4 + 0xc) < *param_5;
      }
      if (bVar4) {
        local_8 = *(undefined4 *)(this + 4);
        local_c = this;
        FUN_008ea280();
        cVar2 = FUN_008ea250(&local_c);
        if ((cVar2 != '\0') || (*param_5 < *(uint *)(param_4 + 0xc))) {
          if (*(char *)(*(int *)(param_4 + 8) + 0x19) != '\0') {
            FUN_008ed3e0(outPacket,0,param_4,param_5);
            return outPacket;
          }
          FUN_008ed3e0(outPacket,1,param_4,param_5);
          return outPacket;
        }
      }
    }
  }
  puVar3 = (undefined4 *)FUN_008ee4f0(&local_c,param_5);
  *outPacket = *puVar3;
  outPacket[1] = puVar3[1];
  return outPacket;
}