// FUNC_NAME: StackAllocator::pushFrame
void __thiscall StackAllocator::pushFrame(int *this, undefined4 param_2, undefined8 *param_3, undefined8 *param_4)
{
  int *piVar1;
  int iVar2;
  undefined8 *puVar3;
  
  iVar2 = *this;
  // Store current frame pointer (offset +0x14)
  **(undefined4 **)(iVar2 + 0x14) = &PTR_LAB_01124ae0;
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;
  
  iVar2 = *this;
  // Push param_2 as frame marker
  **(undefined4 **)(iVar2 + 0x14) = param_2;
  
  // Align to 16-byte boundary for param_3 (16 bytes)
  puVar3 = (undefined8 *)(*(int *)(iVar2 + 0x14) + 0x13U & 0xfffffff0);
  *(undefined8 **)(iVar2 + 0x14) = puVar3;
  *puVar3 = *param_3;
  puVar3[1] = param_3[1];
  
  // Align to 16-byte boundary for param_4 (16 bytes)
  puVar3 = (undefined8 *)(*(int *)(iVar2 + 0x14) + 0x1fU & 0xfffffff0);
  *(undefined8 **)(iVar2 + 0x14) = puVar3;
  *puVar3 = *param_4;
  puVar3[1] = param_4[1];
  
  // Advance frame pointer by 16 bytes
  *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 0x10;
  return;
}