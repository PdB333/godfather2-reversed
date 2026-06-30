// FUNC_NAME: StreamWriter::writeVTableAndData
void __thiscall StreamWriter::writeVTableAndData(int *this, int param_2, undefined8 *param_3)
{
  int *bufferBase;
  int *alignedPtr;

  // Dereference the this pointer to get the buffer control block base
  bufferBase = (int *)*this;

  // Write the vtable pointer into the current write position
  *(undefined4 **)(bufferBase + 0x14) = &PTR_LAB_01124af4;

  // Increment the write position by 4 bytes
  *(int **)(bufferBase + 0x14) = (int *)(*(int *)(bufferBase + 0x14) + 4);

  // Write param_2 (likely an identifier or size) at the new write position
  *(undefined4 **)(bufferBase + 0x14) = param_2;

  // Align the write pointer to the next 16-byte boundary
  alignedPtr = (undefined8 *)((*(int *)(bufferBase + 0x14) + 0x13U) & 0xfffffff0);

  // Store the aligned pointer back
  *(undefined8 **)(bufferBase + 0x14) = alignedPtr;

  // Write the first 8 bytes of param_3
  *alignedPtr = *param_3;

  // Write the next 8 bytes of param_3
  alignedPtr[1] = param_3[1];

  // Advance the write pointer by 16 bytes
  *(int *)(bufferBase + 0x14) = *(int *)(bufferBase + 0x14) + 0x10;
}