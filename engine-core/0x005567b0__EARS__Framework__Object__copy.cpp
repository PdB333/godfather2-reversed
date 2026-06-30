// FUNC_NAME: EARS::Framework::Object::copy
void EARS::Framework::Object::copy(void)
{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  char *pcVar4;
  uint unaff_ESI;
  int unaff_EDI;
  
  // Clear destination fields +0x48 through +0x5c (8 bytes each, total 24 bytes)
  *(undefined4 *)(unaff_ESI + 0x48) = 0;
  *(undefined4 *)(unaff_ESI + 0x4c) = 0;
  *(undefined4 *)(unaff_ESI + 0x50) = 0;
  *(undefined4 *)(unaff_ESI + 0x54) = 0;
  *(undefined4 *)(unaff_ESI + 0x58) = 0;
  *(undefined4 *)(unaff_ESI + 0x5c) = 0;
  
  // Call a helper (potentially reference counting or string copy)
  FUN_005420c0(unaff_EDI);
  
  // Copy packet data from source (+0x40 to +0x60) to destination
  *(undefined4 *)(unaff_ESI + 0x40) = *(undefined4 *)(unaff_EDI + 0x40);
  *(undefined4 *)(unaff_EDI + 0x40) = 0;
  iVar1 = *(int *)(unaff_ESI + 0x40);
  *(undefined4 *)(unaff_ESI + 0x44) = *(undefined4 *)(unaff_EDI + 0x44);
  *(undefined4 *)(unaff_ESI + 0x48) = *(undefined4 *)(unaff_EDI + 0x48);
  *(undefined8 *)(unaff_ESI + 0x4c) = *(undefined8 *)(unaff_EDI + 0x4c);
  *(undefined8 *)(unaff_ESI + 0x54) = *(undefined8 *)(unaff_EDI + 0x54);
  *(undefined4 *)(unaff_ESI + 0x5c) = *(undefined4 *)(unaff_EDI + 0x5c);
  *(undefined4 *)(unaff_ESI + 0x60) = *(undefined4 *)(unaff_EDI + 0x60);
  
  // If the source had data, check for debug string
  if (iVar1 != 0) {
    piVar2 = (int *)(**(code **)(*DAT_0113dfc8 + 0x14))();
    uVar3 = (**(code **)(*piVar2 + 0x10))(iVar1);
    pcVar4 = (char *)FUN_00ab06f0(&stack0xfffffffb,uVar3);
    if (*pcVar4 == '\0') goto LAB_0055684b;
  }
  
  // If destination has data, set reference
  if (*(int *)(unaff_ESI + 0x40) != 0) {
    *(uint *)(*(int *)(unaff_ESI + 0x40) + 0x2c) = unaff_ESI >> 2 | 0xc0000000;
  }
LAB_0055684b:
  // Copy remaining fields at +0x64 and +0x68
  *(undefined4 *)(unaff_ESI + 100) = *(undefined4 *)(unaff_EDI + 100);
  *(undefined4 *)(unaff_ESI + 0x68) = *(undefined4 *)(unaff_EDI + 0x68);
  return;
}