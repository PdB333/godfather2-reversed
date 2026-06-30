// FUNC_NAME: std::vector::swap
void __fastcall std_vector_swap(undefined4 *this, undefined4 *other)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int *piVar6;
  int iVar7;
  undefined4 *in_EAX;
  int iVar8;
  undefined8 local_8;
  
  // Swap the begin pointers
  uVar3 = *in_EAX;
  *in_EAX = *other;
  *other = uVar3;
  
  // Swap the end pointers
  uVar3 = in_EAX[1];
  in_EAX[1] = other[1];
  puVar4 = (undefined4 *)other[2];
  puVar1 = other + 3;
  other[1] = uVar3;
  puVar5 = (undefined4 *)in_EAX[2];
  puVar2 = in_EAX + 3;
  
  // Swap the capacity pointers, handling the case where they point to the inline storage
  if (puVar5 == puVar2) {
    other[2] = puVar1;
  }
  else {
    other[2] = puVar5;
  }
  if (puVar4 == puVar1) {
    in_EAX[2] = puVar2;
  }
  else {
    in_EAX[2] = puVar4;
  }
  
  // If both vectors use inline storage, swap the inline data
  if ((puVar5 == puVar2) || (puVar4 == puVar1)) {
    local_8 = 0;
    FUN_005a32d0(other + 5, &local_8);
    FUN_005a32d0(in_EAX + 5, other + 3);
    FUN_005a32d0(&stack0x00000000, in_EAX + 3);
    iVar8 = 1;
    do {
      piVar6 = *(int **)((int)register0x00000010 + -4);
      register0x00000010 = (BADSPACEBASE *)((int)register0x00000010 + -4);
      if (((piVar6 != (int *)0x0) && (*piVar6 = *piVar6 + -1, *piVar6 == 0)) &&
         (iVar7 = *(int *)register0x00000010, iVar7 != 0)) {
        FUN_005a1b40();
        (*DAT_0119caf8)(iVar7, 0x30);
      }
      iVar8 = iVar8 + -1;
    } while (-1 < iVar8);
  }
  return;
}