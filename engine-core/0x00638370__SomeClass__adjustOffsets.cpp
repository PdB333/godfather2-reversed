// FUNC_NAME: SomeClass::adjustOffsets
void SomeClass::adjustOffsets(void)
{
  int *piVar1;
  int iVar2;
  int in_EAX;
  int unaff_ESI;
  
  iVar2 = *(int *)(unaff_ESI + 0x2c);
  if (*(int *)(unaff_ESI + 0xc) != 0) {
    (*DAT_012059e0)(*(int *)(unaff_ESI + 0xc));
    if (in_EAX != 0) {
      piVar1 = (int *)(*(int *)(in_EAX + 0x10) + 0x24);
      *piVar1 = *piVar1 + iVar2 * -4;
    }
  }
  iVar2 = *(int *)(unaff_ESI + 0x34);
  if (*(int *)(unaff_ESI + 0x10) != 0) {
    (*DAT_012059e0)(*(int *)(unaff_ESI + 0x10));
    if (in_EAX != 0) {
      piVar1 = (int *)(*(int *)(in_EAX + 0x10) + 0x24);
      *piVar1 = *piVar1 + iVar2 * -4;
    }
  }
  iVar2 = *(int *)(unaff_ESI + 0x28);
  if (*(int *)(unaff_ESI + 8) != 0) {
    (*DAT_012059e0)(*(int *)(unaff_ESI + 8));
    if (in_EAX != 0) {
      piVar1 = (int *)(*(int *)(in_EAX + 0x10) + 0x24);
      *piVar1 = *piVar1 + iVar2 * -8;
    }
  }
  iVar2 = *(int *)(unaff_ESI + 0x30);
  if (*(int *)(unaff_ESI + 0x14) != 0) {
    (*DAT_012059e0)(*(int *)(unaff_ESI + 0x14));
    if (in_EAX != 0) {
      piVar1 = (int *)(*(int *)(in_EAX + 0x10) + 0x24);
      *piVar1 = *piVar1 + iVar2 * -4;
    }
  }
  iVar2 = *(int *)(unaff_ESI + 0x38);
  if (*(int *)(unaff_ESI + 0x18) != 0) {
    (*DAT_012059e0)(*(int *)(unaff_ESI + 0x18));
    if (in_EAX != 0) {
      piVar1 = (int *)(*(int *)(in_EAX + 0x10) + 0x24);
      *piVar1 = *piVar1 + iVar2 * -0xc;
    }
  }
  iVar2 = *(int *)(unaff_ESI + 0x24);
  if (*(int *)(unaff_ESI + 0x1c) != 0) {
    (*DAT_012059e0)(*(int *)(unaff_ESI + 0x1c));
    if (in_EAX != 0) {
      piVar1 = (int *)(*(int *)(in_EAX + 0x10) + 0x24);
      *piVar1 = *piVar1 + iVar2 * -4;
    }
  }
  (*DAT_012059e0)();
  if (in_EAX != 0) {
    piVar1 = (int *)(*(int *)(in_EAX + 0x10) + 0x24);
    *piVar1 = *piVar1 + -0x48;
  }
  return;
}