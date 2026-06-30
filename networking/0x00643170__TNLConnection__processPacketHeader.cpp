// FUNC_NAME: TNLConnection::processPacketHeader
void __thiscall TNLConnection::processPacketHeader(int *this, int *packetHeader)
{
  int iVar1;
  int *in_EAX;
  int iVar2;
  uint uVar3;
  int extraout_ECX;
  int iVar4;
  
  FUN_00642b00();
  if (*in_EAX == 0xb) {
    if (in_EAX[3] == in_EAX[4]) goto LAB_006431ae;
    if (this[0xd] <= in_EAX[1]) {
      FUN_00642d90(in_EAX[1]);
      goto LAB_006431ae;
    }
  }
  FUN_00642ec0();
LAB_006431ae:
  if (((*in_EAX == 0xb) && (this[0xd] <= in_EAX[1])) && (in_EAX[1] < 0xfa)) {
    this[9] = this[9] + -1;
  }
  iVar4 = *this;
  iVar1 = this[9];
  iVar2 = iVar1 + 2;
  if ((int)(uint)*(byte *)(iVar4 + 0x47) < iVar2) {
    if (0xf9 < iVar2) {
      this = (int *)this[3];
      iVar2 = FUN_00638b80("function or expression too complex");
      iVar4 = extraout_ECX;
    }
    *(char *)(iVar4 + 0x47) = (char)iVar2;
  }
  this[9] = this[9] + 2;
  uVar3 = FUN_00642fc0();
  FUN_006438e0(((iVar1 << 9 | in_EAX[1]) << 9 | uVar3) << 6 | 0xb,*(undefined4 *)(this[3] + 8));
  if (((*packetHeader == 0xb) && (this[0xd] <= packetHeader[1])) && (packetHeader[1] < 0xfa)) {
    this[9] = this[9] + -1;
  }
  in_EAX[1] = iVar1;
  *in_EAX = 0xb;
  return;
}