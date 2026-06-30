// FUNC_NAME: EARSObject::destructor
void EARSObject::destructor(void)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 *in_EAX;
  undefined2 *unaff_ESI;
  
  FUN_00672320();
  *in_EAX = 0;
  FUN_00671c20();
  iVar2 = *(int *)(unaff_ESI + 6); // +0x0c: some pointer
  iVar3 = *(int *)(unaff_ESI + 0xf1c); // +0x1e38: manager pointer
  if (iVar2 != 0) {
    *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar2 + -8) * 4) = 0;
    piVar1 = (int *)(iVar3 + 4);
    *piVar1 = *piVar1 + -1;
    (*DAT_01206694)(iVar2 + -0x10);
  }
  iVar2 = *(int *)(unaff_ESI + 2); // +0x04: another pointer
  iVar3 = *(int *)(unaff_ESI + 0xf1c); // +0x1e38: manager pointer
  unaff_ESI[4] = 0; // +0x08: clear flag
  if (iVar2 != 0) {
    *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar2 + -8) * 4) = 0;
    piVar1 = (int *)(iVar3 + 4);
    *piVar1 = *piVar1 + -1;
    (*DAT_01206694)(iVar2 + -0x10);
  }
  iVar2 = *(int *)(unaff_ESI + 0xf1c); // +0x1e38: manager pointer
  *unaff_ESI = 0; // +0x00: clear self pointer
  FUN_00672fd0();
  (*DAT_01206694)(*(undefined4 *)(iVar2 + 0xc)); // free manager's data array
  (*DAT_01206694)(iVar2); // free manager
  (*DAT_01206694)(); // free this
  return;
}