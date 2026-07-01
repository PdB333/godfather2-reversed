// FUNC_NAME: BitStream::writeBits
void __thiscall BitStream::writeBits(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5,
            undefined4 param_6, char param_7, undefined4 param_8, undefined4 param_9)

{
  undefined4 *puVar1;
  
  // Write param_2 as 32-bit value at current buffer position
  **(undefined4 **)(param_1 + 0x14) = param_2;
  // Advance buffer pointer by 4 bytes
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 4;
  
  // Call some marshaling function (likely memcpy or bit copy) with size 0x40, alignment 0x10
  FUN_0049c430(param_3, 0x40, 0x10);
  
  // Call marshaling for param_4 with size 4, alignment 4
  FUN_0049c430(&param_4, 4, 4);
  
  // Write param_5 as 32-bit value
  **(undefined4 **)(param_1 + 0x14) = param_5;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 4;
  
  // Write param_6 as 32-bit value
  **(undefined4 **)(param_1 + 0x14) = param_6;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 4;
  
  // Write boolean param_7 as a byte (bool stored at buffer pointer)
  *(bool *)*(undefined4 *)(param_1 + 0x14) = param_7 != '\0';
  
  // Align buffer pointer to next 4-byte boundary and write param_8 and param_9 as a pair
  puVar1 = (undefined4 *)(*(int *)(param_1 + 0x14) + 4U & 0xfffffffc);
  *puVar1 = param_8;
  puVar1[1] = param_9;
  *(undefined4 **)(param_1 + 0x14) = puVar1 + 2;
  
  return;
}