// FUNC_NAME: StreamWriter::writePackedData 
void StreamWriter::writePackedData(void* sourceData, int size1, long long data2, long long data3, int flags, long long data6)
{
  // +0x14: current buffer pointer (this->bufferPtr)
  // Writes packed data with alignment to 4-byte boundaries
  
  // Write first 4-byte value at current position
  *(int*)(this->bufferPtr[0x14]) = sourceData;
  
  // Align to next 4-byte boundary and write second 4-byte value
  int* alignedPtr1 = (int*)((this->bufferPtr[0x14] + 7U) & 0xfffffffc);
  this->bufferPtr[0x14] = (int)alignedPtr1;
  *alignedPtr1 = size1;
  
  // Align to 8-byte boundary and write 8-byte value (data2 + data3 as 8-byte pair)
  long long* alignedPtr2 = (long long*)((this->bufferPtr[0x14] + 7U) & 0xfffffffc);
  this->bufferPtr[0x14] = (int)alignedPtr2;
  *alignedPtr2 = data2;
  alignedPtr2[1] = data3;
  
  // Write flags as 4-byte value after the 8-byte pair
  *(int*)(alignedPtr2 + 2) = flags;
  
  // Align to 8-byte boundary and write data6
  long long* alignedPtr3 = (long long*)((this->bufferPtr[0x14] + 0x17U) & 0xfffffffc);
  this->bufferPtr[0x14] = (int)alignedPtr3;
  *alignedPtr3 = data6;
  
  // Advance buffer pointer by 8 bytes past the last write
  this->bufferPtr[0x14] += 8;
}