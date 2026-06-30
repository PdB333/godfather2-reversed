// FUNC_NAME: TNLConnection::writePacketData
void TNLConnection::writePacketData(int *this, undefined4 *param_1)
{
  int iVar1;
  undefined4 *puVar2;
  int *in_EAX;
  int iVar3;
  int unaff_EDI;
  
  if (unaff_EDI != 0) {
    FUN_005822d0(in_EAX[1] + unaff_EDI);
    iVar3 = in_EAX[1];
    iVar1 = iVar3 + unaff_EDI;
    do {
      puVar2 = (undefined4 *)(*in_EAX + iVar3 * 4);
      in_EAX[1] = iVar3 + 1;
      if (puVar2 != (undefined4 *)0x0) {
        *puVar2 = *param_1;
      }
      iVar3 = in_EAX[1];
    } while (iVar1 != iVar3);
  }
  return;
}