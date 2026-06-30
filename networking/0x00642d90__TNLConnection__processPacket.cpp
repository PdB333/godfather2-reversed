// FUNC_NAME: TNLConnection::processPacket
void TNLConnection::processPacket(int param_1)

{
  int in_EAX;
  int iVar1;
  int *unaff_EDI;
  
  FUN_00642c40(param_1);
  if (*unaff_EDI == 9) {
    FUN_00642880();
  }
  if (unaff_EDI[3] == unaff_EDI[4]) goto LAB_00642e98;
  iVar1 = FUN_006425f0(1);
  if (iVar1 == 0) {
    iVar1 = FUN_006425f0(0);
    if (iVar1 != 0) goto LAB_00642df3;
  }
  else {
LAB_00642df3:
    if (*unaff_EDI != 9) {
      FUN_006424b0();
    }
    *(undefined4 *)(in_EAX + 0x1c) = *(undefined4 *)(in_EAX + 0x18);
    FUN_006438e0(param_1 << 0x18 | 0x42,*(undefined4 *)(*(int *)(in_EAX + 0xc) + 8));
    *(undefined4 *)(in_EAX + 0x1c) = *(undefined4 *)(in_EAX + 0x18);
    FUN_006438e0(param_1 << 0x18 | 0x8002,*(undefined4 *)(*(int *)(in_EAX + 0xc) + 8));
    *(undefined4 *)(in_EAX + 0x1c) = *(undefined4 *)(in_EAX + 0x18);
    FUN_00642880();
  }
  *(undefined4 *)(in_EAX + 0x1c) = *(undefined4 *)(in_EAX + 0x18);
  FUN_006426a0();
  FUN_006426a0();
LAB_00642e98:
  unaff_EDI[3] = -1;
  unaff_EDI[4] = -1;
  unaff_EDI[1] = param_1;
  *unaff_EDI = 0xb;
  return;
}