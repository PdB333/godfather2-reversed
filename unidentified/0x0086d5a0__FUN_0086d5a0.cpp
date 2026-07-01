// FUNC_NAME: SomeClass::getPositionOffset
int __fastcall SomeClass::getPositionOffset(int thisPtr)
{
  float fVar1;
  int iVar2;
  float *pfVar3;
  
  if (*(char *)(thisPtr + 0x25) == '\0') {
    iVar2 = FUN_00471610();
    *(undefined8 *)(thisPtr + 0x18) = *(undefined8 *)(iVar2 + 0x30);
    *(undefined4 *)(thisPtr + 0x20) = *(undefined4 *)(iVar2 + 0x38);
    fVar1 = DAT_00d76128;
    pfVar3 = (float *)FUN_0086d500();
    *(float *)(thisPtr + 0x18) = *pfVar3 * fVar1 + *(float *)(thisPtr + 0x18);
    *(float *)(thisPtr + 0x1c) = pfVar3[1] * fVar1 + *(float *)(thisPtr + 0x1c);
    *(float *)(thisPtr + 0x20) = pfVar3[2] * fVar1 + *(float *)(thisPtr + 0x20);
    *(undefined1 *)(thisPtr + 0x25) = 1;
  }
  return thisPtr + 0x18;
}