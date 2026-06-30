// FUNC_NAME: LinkedList::addNodeWithData
void FUN_00540430(int this, undefined4 *data1, char *stringData)
{
  char cVar1;
  int iVar2;
  undefined4 *in_EAX;
  undefined1 *newNode;
  char *pcVar4;
  int iVar5;
  undefined4 *puVar6;
  
  iVar5 = *(int *)(this + 0x40); // +0x40: head pointer of linked list
  if (iVar5 != 0) {
    iVar2 = *(int *)(iVar5 + 0xb0); // +0xB0: next pointer
    while (iVar2 != 0) {
      iVar5 = *(int *)(iVar5 + 0xb0);
      iVar2 = *(int *)(iVar5 + 0xb0);
    }
  }
  
  newNode = (undefined1 *)FUN_009c8e50(0xc0); // allocate 0xC0 bytes (192 bytes)
  if (newNode == (undefined1 *)0x0) {
    newNode = (undefined1 *)0x0;
  }
  else {
    *(undefined4 *)(newNode + 4) = 0xbadbadba; // +0x04: magic number 1
    *(undefined4 *)(newNode + 8) = 0xbeefbeef; // +0x08: magic number 2
    *(undefined4 *)(newNode + 0xc) = 0xeac15a55; // +0x0C: magic number 3
    *(undefined4 *)(newNode + 0x10) = 0x91100911; // +0x10: magic number 4
  }
  
  if (iVar5 == 0) {
    *(undefined1 **)(this + 0x40) = newNode; // set head if list empty
  }
  else {
    *(undefined1 **)(iVar5 + 0xb0) = newNode; // link to last node
  }
  
  *newNode = 1; // +0x00: node type/flag
  *(undefined4 *)(newNode + 4) = *in_EAX; // +0x04: copy first 16 bytes from in_EAX
  *(undefined4 *)(newNode + 8) = in_EAX[1]; // +0x08
  *(undefined4 *)(newNode + 0xc) = in_EAX[2]; // +0x0C
  *(undefined4 *)(newNode + 0x10) = in_EAX[3]; // +0x10
  *(undefined4 *)(newNode + 0x20) = *data1; // +0x20: copy second 16 bytes from param_2
  *(undefined4 *)(newNode + 0x24) = data1[1]; // +0x24
  *(undefined4 *)(newNode + 0x28) = data1[2]; // +0x28
  *(undefined4 *)(newNode + 0x2c) = data1[3]; // +0x2C
  
  pcVar4 = stringData;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  
  if (0x7f < (uint)((int)pcVar4 - (int)(stringData + 1))) {
    // String too long (>127 chars), copy as raw data
    puVar6 = (undefined4 *)(newNode + 0x30); // +0x30: string buffer start
    for (iVar5 = 0x1f; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *(undefined4 *)stringData;
      stringData = stringData + 4;
      puVar6 = puVar6 + 1;
    }
    *(undefined2 *)puVar6 = *(undefined2 *)stringData;
    *(char *)((int)puVar6 + 2) = stringData[2];
    newNode[0xaf] = 0; // null terminate at offset 0xAF
    *(undefined4 *)(newNode + 0xb0) = 0; // +0xB0: next pointer = null
    return;
  }
  
  // String fits, copy with null termination
  iVar5 = 0x30 - (int)stringData;
  do {
    cVar1 = *stringData;
    stringData[(int)(newNode + iVar5)] = cVar1;
    stringData = stringData + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(newNode + 0xb0) = 0; // +0xB0: next pointer = null
  return;
}