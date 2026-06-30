// FUNC_NAME: HeapManager::freeBlock
void __thiscall HeapManager::freeBlock(int param_1, int param_2, int param_3)
{
  uint *puVar1;
  int iVar2;
  int in_EAX;
  uint uVar3;
  int iVar4;
  
  iVar4 = (param_1 - in_EAX) + param_3;
  uVar3 = param_3 - iVar4;
  if (uVar3 < 0x10) {
    puVar1 = (uint *)(param_1 + 4 + param_3);
    *puVar1 = *puVar1 | 1;
    return;
  }
  iVar2 = *(int *)(param_2 + 0x3c);
  *(int *)(param_1 + 0xc) = iVar2;
  *(int *)(param_1 + 8) = param_2 + 0x30;
  *(int *)(param_2 + 0x3c) = param_1;
  *(int *)(iVar2 + 8) = param_1;
  if (uVar3 < 0x200) {
    *(int *)(param_2 + 0x444) = param_1;
  }
  *(int *)(in_EAX + 4) = iVar4;
  puVar1 = (uint *)(iVar4 + 4 + in_EAX);
  *puVar1 = *puVar1 | 1;
  *(uint *)(param_1 + 4) = uVar3 | 1;
  *(uint *)(uVar3 + param_1) = uVar3;
  return;
}