// FUNC_NAME: StreamManager::writeStreamData
void __thiscall StreamManager::writeStreamData(undefined4 param_1, undefined4 param_2)
{
  int *piVar1;
  
  piVar1 = (int *)(DAT_01206880 + 0x14); // +0x14: stream buffer pointer
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e569b0; // Write vtable pointer
  *piVar1 = *piVar1 + 4; // Advance buffer position
  *(undefined4 *)*piVar1 = param_1; // Write first parameter to stream
  *piVar1 = *piVar1 + 4; // Advance buffer position
  FUN_0049c430(&param_2,4,4); // Write 4 bytes from param_2 to stream
  return;
}