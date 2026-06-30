// FUNC_NAME: TNLConnection::processPacket
void TNLConnection::processPacket(void)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  int unaff_EDI;
  char *_Format;
  
  FUN_00625ca0();
  puVar1 = (undefined4 *)FUN_00633cb0();
  iVar3 = *(int *)(unaff_EDI + 8);
  *(undefined4 *)(iVar3 + -8) = *puVar1;
  *(undefined4 *)(iVar3 + -4) = puVar1[1];
  puVar1 = *(undefined4 **)(unaff_EDI + 8);
  if ((puVar1 + -2 != (int *)0x0) && (puVar1[-2] == 6)) {
    for (puVar2 = puVar1; puVar1 + -4 < puVar2; puVar2 = puVar2 + -2) {
      *puVar2 = puVar2[-2];
      puVar2[1] = puVar2[-1];
    }
    puVar2 = *(undefined4 **)(unaff_EDI + 8);
    puVar1[-4] = *puVar2;
    puVar1[-3] = puVar2[1];
    FUN_006362d0();
    return;
  }
  piVar4 = puVar1 + -4;
  if (piVar4 != (int *)0x0) {
    if (*piVar4 == 4) {
      piVar4 = (int *)(puVar1[-3] + 0x10);
    }
    else {
      iVar3 = FUN_00633990();
      if (iVar3 == 0) {
        piVar4 = (int *)0x0;
      }
      else {
        piVar4 = (int *)(puVar1[-3] + 0x10);
      }
      if (*(uint *)(*(int *)(unaff_EDI + 0x10) + 0x20) <=
          *(uint *)(*(int *)(unaff_EDI + 0x10) + 0x24)) {
        FUN_00627360();
      }
    }
  }
  _Format = "%s\n";
  iVar3 = FUN_00b995f7(&DAT_00e41634,piVar4);
  _fprintf((FILE *)(iVar3 + 0x40),_Format);
  *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + -0x10;
  return;
}