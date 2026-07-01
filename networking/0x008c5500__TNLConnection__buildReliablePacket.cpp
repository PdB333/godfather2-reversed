// FUNC_NAME: TNLConnection::buildReliablePacket
int TNLConnection::buildReliablePacket(int param_1, int param_2, int param_3)
{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  
  FUN_008c21e0();
  FUN_008c2080(param_2);
  iVar4 = param_2 * 0x10 + param_1;
  if (param_2 != 0) {
    piVar3 = (int *)(param_1 + 4);
    param_1 = param_2;
    do {
      iVar1 = FUN_008c4100();
      *(int *)(iVar1 + 4) = piVar3[-1];
      if (piVar3[1] != 0) {
        *(undefined1 *)(iVar1 + 0xc) = 1;
      }
      if (*piVar3 != 0) {
        uVar2 = FUN_006b0ee0(*piVar3);
        *(undefined4 *)(iVar1 + 8) = uVar2;
      }
      iVar1 = FUN_008c1c70(iVar4,*piVar3,piVar3[2],iVar1 + 0x10);
      iVar4 = iVar4 + iVar1;
      piVar3 = piVar3 + 4;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  return (param_3 + param_2) * 0x10;
}