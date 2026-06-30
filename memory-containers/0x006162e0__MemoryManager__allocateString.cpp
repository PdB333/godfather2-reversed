// FUNC_NAME: MemoryManager::allocateString
uint * MemoryManager::allocateString(char *sourceString)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  size_t stringLength;
  uint *pAllocatedBlock;
  uint returnAddress;
  undefined4 local_c;
  undefined4 local_8;
  void *local_4;
  
  // Calculate string length
  pcVar1 = sourceString + 1;
  do {
    cVar2 = *sourceString;
    sourceString = sourceString + 1;
  } while (cVar2 != '\0');
  stringLength = (int)sourceString - (int)pcVar1;
  
  local_c = 0;
  local_8 = 0;
  local_4 = (void *)0x0;
  
  // Allocate memory: size = stringLength + 0xD (13 bytes overhead for header)
  pAllocatedBlock = (uint *)(**(code **)*DAT_01205964)(stringLength + 0xd, &local_c);
  if (pAllocatedBlock == (uint *)0x0) {
    pAllocatedBlock = (uint *)0x0;
  }
  else {
    // Store return address in first 4 bytes (for leak tracking)
    *pAllocatedBlock = returnAddress;
    // Zero out the next fields
    pAllocatedBlock[1] = 0;
    *(undefined2 *)(pAllocatedBlock + 2) = 0;
    
    // Insert into allocation tracking linked list (hash table based on return address low byte)
    iVar3 = DAT_01205960; // Allocation tracking table base
    pAllocatedBlock[1] = *(uint *)(iVar3 + (returnAddress & 0xff) * 4);
    *(uint **)(iVar3 + (returnAddress & 0xff) * 4) = pAllocatedBlock;
    *(int *)(iVar3 + 0x400) = *(int *)(iVar3 + 0x400) + 1; // Increment allocation count
  }
  
  // Copy the string into the allocated block (after 12-byte header)
  _memcpy(pAllocatedBlock + 3, local_4, stringLength);
  *(undefined1 *)(stringLength + (int)(pAllocatedBlock + 3)) = 0;
  return pAllocatedBlock;
}