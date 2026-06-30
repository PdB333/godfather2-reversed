// FUNC_NAME: PlayerActionableInfo::updateFromSimNpc
undefined4 PlayerActionableInfo::updateFromSimNpc(undefined4 param_1, int *param_2)

{
  int iVar1;
  undefined4 *in_EAX;
  int iVar2;
  
  *in_EAX = 0;
  iVar1 = *param_2;
  iVar2 = FUN_00672a80();
  if (iVar2 != 0) {
    if ((*(int *)(iVar2 + 0x50) == 0) && (*(int *)(iVar2 + 0x4c) == 0)) {
      *(undefined4 *)(iVar1 + 0x11c) = 0;
      *(undefined4 *)(iVar1 + 0x118) = 0;
    }
    else if (*(short *)(iVar2 + 0x5a) == 1) {
      *(int *)(iVar1 + 0x11c) = iVar2 + 0x68;
    }
    else {
      *(int *)(iVar1 + 0x118) = iVar2 + 0x68;
    }
    *(undefined4 *)(iVar1 + 0x30) = 0;
    *(int *)(iVar1 + 0xcc) = (int)*(short *)(iVar2 + 0x14);
    *(undefined4 *)(iVar1 + 0xd0) = *(undefined4 *)(iVar2 + 0x18);
    *(undefined4 *)(iVar1 + 0xd4) = *(undefined4 *)(iVar2 + 0x1c);
    *(undefined4 *)(iVar1 + 0xd8) = *(undefined4 *)(iVar2 + 0x20);
    *(undefined4 *)(iVar1 + 0xdc) = *(undefined4 *)(iVar2 + 0x24);
    *(undefined4 *)(iVar1 + 0xe0) = *(undefined4 *)(iVar2 + 0x28);
    *(undefined4 *)(iVar1 + 0xe4) = *(undefined4 *)(iVar2 + 0x2c);
    *(int *)(iVar1 + 0xe8) = (int)*(short *)(iVar2 + 0x30);
    *(undefined4 *)(iVar1 + 0xec) = *(undefined4 *)(iVar2 + 0x34);
    *(undefined4 *)(iVar1 + 0xf0) = *(undefined4 *)(iVar2 + 0x38);
    *(undefined4 *)(iVar1 + 0xf4) = *(undefined4 *)(iVar2 + 0x3c);
    *(undefined4 *)(iVar1 + 0xf8) = *(undefined4 *)(iVar2 + 0x40);
    *(undefined4 *)(iVar1 + 0xfc) = *(undefined4 *)(iVar2 + 0x44);
    *(undefined4 *)(iVar1 + 0x100) = *(undefined4 *)(iVar2 + 0x48);
    *(undefined4 *)(iVar1 + 0x10c) = *(undefined4 *)(iVar2 + 0x4c);
    *(undefined4 *)(iVar1 + 0x110) = *(undefined4 *)(iVar2 + 0x50);
    *(undefined4 *)(iVar1 + 0x114) = *(undefined4 *)(iVar2 + 0x54);
    *(int *)(iVar1 + 0x120) = (int)*(short *)(iVar2 + 0x58);
    *(undefined2 *)(iVar1 + 0x108) = *(undefined2 *)(iVar2 + 0x5c);
    return 1;
  }
  return 0;
}