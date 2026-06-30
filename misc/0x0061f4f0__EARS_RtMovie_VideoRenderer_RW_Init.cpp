// Xbox PDB: EARS::RtMovie::VideoRenderer_RW::Init
// FUNC_NAME: RenderTarget::initialize
void __thiscall RenderTarget::initialize(int thisPtr, undefined4 param_2, uint width, uint height)
{
  undefined4 uVar1;
  
  *(uint *)(thisPtr + 0xcc) = width;
  *(uint *)(thisPtr + 0xd0) = height;
  *(ushort *)(thisPtr + 0xd4) = (short)width + 0xffU & 0xff00;
  *(undefined4 *)(thisPtr + 200) = 0;
  *(ushort *)(thisPtr + 0xd6) = (short)height + 0x1fU & 0xffe0;
  *(ushort *)(thisPtr + 0xd8) = (short)(width >> 1) + 0xffU & 0xff00;
  *(ushort *)(thisPtr + 0xda) = (short)(height >> 1) + 0x1fU & 0xffe0;
  uVar1 = FUN_00ab8560(0,"placeholder",0xb);
  uVar1 = FUN_00ab8560(uVar1,"color",5);
  uVar1 = FUN_00611000(uVar1);
  *(undefined4 *)(thisPtr + 0xbc) = uVar1;
  uVar1 = FUN_00606c80(8,0x200000,*(undefined2 *)(thisPtr + 0xd4),*(undefined2 *)(thisPtr + 0xd6),1,
                       0xffffffff);
  *(undefined4 *)(thisPtr + 0xb0) = uVar1;
  uVar1 = FUN_00606c80(8,0x200000,*(undefined2 *)(thisPtr + 0xd8),*(undefined2 *)(thisPtr + 0xda),1,
                       0xffffffff);
  *(undefined4 *)(thisPtr + 0xb4) = uVar1;
  uVar1 = FUN_00606c80(8,0x200000,*(undefined2 *)(thisPtr + 0xd8),*(undefined2 *)(thisPtr + 0xda),1,
                       0xffffffff);
  *(undefined4 *)(thisPtr + 0xb8) = uVar1;
  FUN_006154e0(*(undefined4 *)(thisPtr + 0xb0),0x10);
  FUN_006154e0(*(undefined4 *)(thisPtr + 0xb4),0x80);
  FUN_006154e0(*(undefined4 *)(thisPtr + 0xb8),0x80);
  uVar1 = DAT_00e2b1a4;
  if ((undefined4 *)(thisPtr + 0x30) != (undefined4 *)0x0) {
    *(undefined4 *)(thisPtr + 0x30) = 0;
    *(undefined4 *)(thisPtr + 0x34) = uVar1;
    *(undefined4 *)(thisPtr + 0x38) = 0;
    *(undefined4 *)(thisPtr + 0x3c) = uVar1;
    *(undefined4 *)(thisPtr + 0x40) = uVar1;
    *(undefined4 *)(thisPtr + 0x44) = 0;
    *(undefined4 *)(thisPtr + 0x48) = 0;
    *(undefined4 *)(thisPtr + 0x4c) = uVar1;
  }
  *(undefined4 *)(thisPtr + 0x50) = uVar1;
  *(undefined4 *)(thisPtr + 0x54) = uVar1;
  *(undefined4 *)(thisPtr + 0x58) = uVar1;
  *(undefined4 *)(thisPtr + 0x5c) = uVar1;
  *(undefined4 *)(thisPtr + 0x60) = uVar1;
  *(undefined4 *)(thisPtr + 100) = uVar1;
  *(undefined4 *)(thisPtr + 0x68) = uVar1;
  *(undefined4 *)(thisPtr + 0x6c) = uVar1;
  if ((undefined4 *)(thisPtr + 0x10) != (undefined4 *)0x0) {
    *(undefined4 *)(thisPtr + 0x10) = 0;
    *(undefined4 *)(thisPtr + 0x14) = 0;
    *(undefined4 *)(thisPtr + 0x18) = 0;
    *(undefined4 *)(thisPtr + 0x1c) = uVar1;
    *(undefined4 *)(thisPtr + 0x20) = uVar1;
    *(undefined4 *)(thisPtr + 0x24) = uVar1;
    *(undefined4 *)(thisPtr + 0x28) = 0;
    *(undefined4 *)(thisPtr + 0x2c) = uVar1;
  }
  return;
}