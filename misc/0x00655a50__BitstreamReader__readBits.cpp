// FUNC_NAME: BitstreamReader::readBits
void __thiscall BitstreamReader::readBits(void *this, undefined4 param_2)
{
  uint uVar1;
  int unaff_ESI;
  bool bVar2;
  bool bVar3;
  undefined1 local_c [12];
  
  if (*(char *)((int)this + 0x7c) != '\0') {
    FUN_0064b9e0(0x40,local_c);
    uVar1 = *(uint *)(unaff_ESI + 0x18);
    if (*(uint *)(unaff_ESI + 0x2c) < uVar1) {
      *(undefined1 *)(unaff_ESI + 0x1c) = 1;
      bVar2 = false;
    }
    else {
      bVar2 = (*(byte *)((uVar1 >> 3) + *(int *)(unaff_ESI + 0xc)) & (byte)(1 << ((byte)uVar1 & 7)))
              != 0;
      *(int *)(unaff_ESI + 0x18) = *(int *)(unaff_ESI + 0x18) + 1;
    }
    uVar1 = *(uint *)(unaff_ESI + 0x18);
    if (*(uint *)(unaff_ESI + 0x2c) < uVar1) {
      *(undefined1 *)(unaff_ESI + 0x1c) = 1;
      bVar3 = false;
    }
    else {
      bVar3 = (*(byte *)((uVar1 >> 3) + *(int *)(unaff_ESI + 0xc)) & (byte)(1 << ((byte)uVar1 & 7)))
              != 0;
      *(uint *)(unaff_ESI + 0x18) = uVar1 + 1;
    }
    FUN_00655b10(param_2,bVar2,bVar3);
  }
  return;
}