// FUNC_NAME: EA::EASTL::hash_map::insert_or_assign
undefined4 * __thiscall EA::EASTL::hash_map::insertOrAssign(int thisPtr, undefined4 *outPair, uint *keyValue)
{
  int iVar1;
  uint hash;
  uint bucketIndex;
  uint *bucketHead;
  uint *currentNode;
  uint *newNode;
  char local_8 [4];
  undefined4 local_4;
  
  // Check if key already exists (via some validation function)
  FUN_00ab4570(local_8, *(undefined4 *)(thisPtr + 8), *(undefined4 *)(thisPtr + 0xc), 1);
  if (local_8[0] != '\0') {
    FUN_0088ff40(local_4);
  }
  
  hash = *keyValue;
  uint bucketCount = *(uint *)(thisPtr + 8);
  
  // Allocate new node (size 0xC = 12 bytes: key, value, next pointer)
  newNode = (uint *)FUN_0068ab90(0xc, "EASTL", 0, 0,
                                "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h",
                                0xe9);
  if (newNode != (uint *)0x0) {
    *newNode = *keyValue;          // +0x00: key
    newNode[1] = keyValue[1];     // +0x04: value
  }
  newNode[2] = 0;                  // +0x08: next pointer
  
  // Compute bucket index
  int bucketIndex = (hash % bucketCount) * 4;
  uint *bucketHead = *(uint **)(bucketIndex + *(int *)(thisPtr + 4));
  
  if (bucketHead != (uint *)0x0) {
    // Search for existing key in bucket chain
    currentNode = bucketHead;
    do {
      if (*keyValue == *currentNode) {
        // Key found: insert new node after existing one (linked list insertion)
        newNode[2] = currentNode[2];
        currentNode[2] = (uint)newNode;
        goto LAB_008904b5;
      }
      currentNode = (uint *)currentNode[2];
    } while (currentNode != (uint *)0x0);
  }
  
  // Key not found: prepend to bucket chain
  newNode[2] = (uint)bucketHead;
  *(uint **)(bucketIndex + *(int *)(thisPtr + 4)) = newNode;
  
LAB_008904b5:
  // Increment element count
  *(int *)(thisPtr + 0xc) = *(int *)(thisPtr + 0xc) + 1;
  
  // Set output pair: pointer to node, and pointer to bucket head
  *outPair = newNode;
  outPair[1] = *(int *)(thisPtr + 4) + bucketIndex;
  return outPair;
}