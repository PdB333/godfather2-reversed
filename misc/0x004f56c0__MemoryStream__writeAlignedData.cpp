// FUNC_NAME: MemoryStream::writeAlignedData
void MemoryStream::writeAlignedData(int param_1, int param_2, long long param_3, int param_4)
{
  // +0x14: current write pointer in the stream buffer
  *(int **)(in_EAX + 0x14) = param_1;
  
  // Align to 4-byte boundary (round up to next multiple of 4)
  int *ptr = (int *)((*(int *)(in_EAX + 0x14) + 7U) & 0xfffffffc);
  *(int **)(in_EAX + 0x14) = ptr;
  *ptr = param_2;
  
  // Align again and write third parameter
  ptr = (int *)((*(int *)(in_EAX + 0x14) + 7U) & 0xfffffffc);
  *(int **)(in_EAX + 0x14) = ptr;
  *ptr = param_3;
  
  // Align for 8-byte value and write 64-bit parameter
  long long *llPtr = (long long *)((*(int *)(in_EAX + 0x14) + 7U) & 0xfffffffc);
  *(long long **)(in_EAX + 0x14) = llPtr;
  *llPtr = param_4;
  
  // Advance write pointer by 8 bytes
  *(int *)(in_EAX + 0x14) = *(int *)(in_EAX + 0x14) + 8;
  
  // Write fifth parameter (4 bytes)
  *(int **)(in_EAX + 0x14) = param_5;
  *(int *)(in_EAX + 0x14) = *(int *)(in_EAX + 0x14) + 4;
  
  // Write ESI register value (likely a saved register or additional parameter)
  *(int **)(in_EAX + 0x14) = unaff_ESI;
  *(int *)(in_EAX + 0x14) = *(int *)(in_EAX + 0x14) + 4;
}