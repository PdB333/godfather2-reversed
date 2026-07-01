// FUNC_NAME: TNLConnection::removeFromSendQueue
undefined4 __fastcall TNLConnection::removeFromSendQueue(int this)
{
  int iVar1;
  int local_4;
  
  local_4 = this;
  FUN_0098b550(&local_4,&stack0x00000004);
  iVar1 = local_4;
  if (local_4 != this + 0x218) {
    *(int *)(this + 0x228) = *(int *)(this + 0x228) + -1;
    FUN_00ab3c50(local_4);
    FUN_00ab4010(iVar1,this + 0x218);
    if (*(int *)(iVar1 + 0x14) != 0) {
      (**(code **)(iVar1 + 0x20))(*(int *)(iVar1 + 0x14));
    }
    FUN_009c8f10(iVar1);
    return 1;
  }
  return 0;
}