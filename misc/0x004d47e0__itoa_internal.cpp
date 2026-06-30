// FUNC_NAME: itoa_internal
int itoa_internal(void)
{
  undefined1 uVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int unaff_ESI;
  
  iVar2 = in_EAX;
  if (in_EAX < 0) {
    iVar2 = -in_EAX;
  }
  iVar5 = 0;
  do {
    iVar4 = iVar5;
    iVar3 = iVar2 / 10;
    iVar5 = iVar4 + 1;
    *(char *)(iVar4 + unaff_ESI) = (char)(iVar2 % 10) + '0';
    iVar2 = iVar3;
  } while (iVar3 != 0);
  if (in_EAX < 0) {
    *(undefined1 *)(iVar5 + unaff_ESI) = 0x2d;
    iVar5 = iVar4 + 2;
  }
  *(undefined1 *)(iVar5 + unaff_ESI) = 0;
  iVar2 = iVar5 + -1;
  iVar3 = 0;
  if (0 < iVar2) {
    do {
      uVar1 = *(undefined1 *)(iVar2 + unaff_ESI);
      *(undefined1 *)(iVar2 + unaff_ESI) = *(undefined1 *)(iVar3 + unaff_ESI);
      *(undefined1 *)(iVar3 + unaff_ESI) = uVar1;
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar3 < iVar2);
  }
  return iVar5;
}