// FUNC_NAME: MemoryStream::readAndCallFunction
void MemoryStream::readAndCallFunction(int thisPtr, undefined4 *functionPtr)
{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 local_8;
  undefined4 uStack_4;
  
  // Read the base pointer from the stream's current position (+0x18)
  uVar2 = **(undefined4 **)(thisPtr + 0x18);
  
  // Align the pointer to 4-byte boundary (round up to next multiple of 4)
  puVar5 = (undefined4 *)((int)*(undefined4 **)(thisPtr + 0x18) + 7U & 0xfffffffc);
  
  // Update stream position to aligned pointer
  *(undefined4 **)(thisPtr + 0x18) = puVar5;
  
  // Read 4 consecutive 32-bit values from the aligned position
  uVar3 = *puVar5;
  *(undefined4 **)(thisPtr + 0x18) = puVar5 + 1;
  uVar4 = puVar5[1];
  *(undefined4 **)(thisPtr + 0x18) = puVar5 + 2;
  uVar1 = *(undefined8 *)(puVar5 + 2);
  *(undefined4 **)(thisPtr + 0x18) = puVar5 + 4;
  
  // Split the 64-bit value into two 32-bit parts
  local_8 = (undefined4)uVar1;
  uStack_4 = (undefined4)((ulonglong)uVar1 >> 0x20);
  
  // Call the function pointer with the 5 arguments read from the stream
  (*(code *)*functionPtr)(uVar2, uVar3, uVar4, local_8, uStack_4);
  
  return;
}