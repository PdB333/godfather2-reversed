// FUNC_NAME: StreamManager::openStream
undefined1 __thiscall StreamManager::openStream(int this, undefined4 param_2, int param_3, int param_4)
{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  *(undefined1 *)(this + 0xc) = 0;
  if (param_3 != 0) {
    *(int *)(this + 0x10) = *(int *)(this + 0x10) + 1;
    uVar3 = 0;
    *(undefined4 *)(this + 8) = 8;
    *(undefined4 *)(this + 0x18) = 0;
    *(undefined4 *)(this + 0x1c) = 0;
    *(undefined4 *)(this + 0x20) = 8;
    uVar2 = FUN_006fbc40(&LAB_007ca9a0, this);
    uVar1 = FUN_007f96a0(param_2, 0x103, uVar2, uVar3);
    *(undefined1 *)(this + 0xc) = uVar1;
    FUN_006fbc70();
    if ((*(char *)(this + 0xc) == '\0') && (param_4 != 0)) {
      uVar2 = FUN_006fbc40(&LAB_007ca9a0, this);
      uVar1 = FUN_007f96a0(param_2, 0x103, uVar2, param_3);
      *(undefined1 *)(this + 0xc) = uVar1;
      FUN_006fbc70();
    }
    return *(undefined1 *)(this + 0xc);
  }
  return *(undefined1 *)(this + 0xc);
}