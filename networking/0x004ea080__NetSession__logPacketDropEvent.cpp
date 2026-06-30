// FUNC_NAME: NetSession::logPacketDropEvent
void NetSession::logPacketDropEvent(int param_1)
{
  int iVar1;
  int iVar2;
  int fsOffset;
  
  iVar1 = *(int *)(**(int **)(fsOffset + 0x2c) + 0x34);
  *(undefined4 *)((uint)(iVar1 != 0) * 0x98 + 4 + param_1) = 0;
  iVar2 = DAT_01206880;
  if (iVar1 != 0) {
    iVar2 = DAT_012068e8;
  }
  **(undefined4 **)(iVar2 + 0x14) = &PTR_LAB_01124be4;
  *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 4;
  **(uint **)(iVar2 + 0x14) = (uint)(iVar1 != 0);
  *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 4;
  return;
}