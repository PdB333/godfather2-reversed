// FUNC_NAME: Serializer::writeBuffer
void __thiscall Serializer::writeBuffer(int *this, undefined4 param_2, undefined4 param_3, undefined8 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7)
{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined8 *puVar4;
  
  iVar2 = *this;
  // Write pointer to vtable/function table at +0x14
  **(undefined4 **)(iVar2 + 0x14) = &PTR_FUN_01124d3c;
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;
  iVar2 = *this;
  // Write param_2 as next element
  **(undefined4 **)(iVar2 + 0x14) = param_2;
  // Align to 4 bytes and write param_3
  puVar3 = (undefined4 *)(*(int *)(iVar2 + 0x14) + 7U & 0xfffffffc);
  *(undefined4 **)(iVar2 + 0x14) = puVar3;
  *puVar3 = param_3;
  // Align to 8 bytes and write param_4 + param_5 (as 64-bit value)
  puVar4 = (undefined8 *)(*(int *)(iVar2 + 0x14) + 7U & 0xfffffffc);
  *(undefined8 **)(iVar2 + 0x14) = puVar4;
  *puVar4 = param_4;
  *(undefined4 *)(puVar4 + 1) = param_5;
  // Align to 16 bytes and write param_6 + param_7 (as 64-bit value)
  puVar4 = (undefined8 *)(*(int *)(iVar2 + 0x14) + 0xfU & 0xfffffffc);
  *(undefined8 **)(iVar2 + 0x14) = puVar4;
  *puVar4 = CONCAT44(param_7, param_6);
  // Advance write pointer by 8 bytes
  *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 8;
  return;
}