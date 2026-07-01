// FUNC_NAME: Animation::checkVisibility
undefined1 __fastcall Animation::checkVisibility(int this)
{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined8 local_c;
  undefined4 local_4;

  if (*(int *)(this + 0x50) != 0) {
    if ((*(int *)(this + 0x88) == 4) ||
       (uVar2 = FUN_0084d420(*(int *)(this + 0x88)), (uVar2 & 8) != 0)) {
      local_4 = *(undefined4 *)(this + 0x80);
      local_c = *(undefined8 *)(this + 0x78);
    }
    else if ((*(int *)(this + 0x5c) == 0) || (*(int *)(this + 0x5c) == 0x48)) {
      local_4 = *(undefined4 *)(this + 0x74);
      local_c = *(undefined8 *)(this + 0x6c);
    }
    else {
      iVar3 = FUN_00471610();
      local_c = *(undefined8 *)(iVar3 + 0x30);
      local_4 = *(undefined4 *)(iVar3 + 0x38);
    }
    iVar3 = FUN_00471610();
    iVar4 = FUN_00471610();
    cVar1 = FUN_007f7f30(&local_c,iVar4 + 0x30,iVar3 + 0x20,_DAT_00d67af8);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  return 1;
}