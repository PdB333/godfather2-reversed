// FUNC_NAME: EARS::StreamManager::pushCommand
void __thiscall pushCommand(int *this, undefined4 commandType, undefined4 commandData)
{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = *this;
  // Write vtable pointer for command object at current stream position
  **(undefined4 **)(iVar2 + 0x14) = &PTR_LAB_01126adc;
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;
  
  iVar2 = *this;
  // Write command type
  **(undefined4 **)(iVar2 + 0x14) = commandType;
  *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 4;
  
  // Align to 4-byte boundary
  puVar3 = (undefined4 *)(*(int *)(iVar2 + 0x14) + 3U & 0xfffffffc);
  *(undefined4 **)(iVar2 + 0x14) = puVar3;
  // Write command data
  *puVar3 = commandData;
  *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 4;
  
  return;
}