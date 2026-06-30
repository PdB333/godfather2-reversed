// FUNC_NAME: StringBuffer::appendFromStream
int StringBuffer::appendFromStream(int param_1)
{
  int iVar1;
  undefined2 uVar2;
  int *in_EAX;
  undefined2 *puVar3;
  int iVar4;
  
  iVar1 = in_EAX[2]; // +0x08: current read position in stream
  iVar4 = *in_EAX + iVar1; // +0x00: stream size, compute end position
  while (iVar1 != iVar4) {
    FUN_005b8d10(); // readNextCharFromStream
  }
  FUN_005b8c50(); // ensureBufferCapacity
  puVar3 = *(undefined2 **)(param_1 + 8); // +0x08: buffer write pointer
  if (iVar1 != iVar4) {
    do {
      uVar2 = FUN_005b8d10(); // readNextCharFromStream
      *puVar3 = uVar2;
      puVar3 = puVar3 + 1;
    } while (iVar1 != iVar4);
    *puVar3 = 0; // null-terminate
    return param_1;
  }
  *puVar3 = 0; // null-terminate
  return param_1;
}