// FUNC_NAME: unknown::someCaptureToBufferFunction
void __fastcall someCaptureToBufferFunction(int thisPtr, int param2)
{
  int iVar1;
  undefined4 *puVar2;
  int in_EAX;
  int *piVar3;
  int extraout_ECX;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  
  uVar6 = CONCAT44(param2, in_EAX);
  // Read a state indicator at offset: thisPtr + (param2 * 2 + 5) * 4
  iVar4 = *(int *)(in_EAX + (param2 * 2 + 5) * 4);
  if (iVar4 == -1) {
    uVar6 = FUN_00627bd0("unfinished capture");
    iVar4 = extraout_ECX;
  }
  iVar5 = (int)((ulonglong)uVar6 >> 0x20);
  piVar3 = (int *)uVar6;
  if (iVar4 == -2) {
    // Write to buffer: set type=3 and length
    iVar4 = piVar3[iVar5 * 2 + 4];
    iVar5 = *piVar3;
    iVar1 = piVar3[2];
    puVar2 = *(undefined4 **)(iVar1 + 8);
    *puVar2 = 3;
    puVar2[1] = (float)((iVar4 - iVar5) + 1);
    piVar3 = (int *)(iVar1 + 8);
    *piVar3 = *piVar3 + 8;
    return;
  }
  FUN_00625c60(piVar3[iVar5 * 2 + 4], iVar4);
  return;
}