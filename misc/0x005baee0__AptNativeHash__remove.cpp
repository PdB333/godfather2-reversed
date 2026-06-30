// FUNC_NAME: AptNativeHash::remove
void __thiscall AptNativeHash::removeKey(byte *thisPtr, byte *key)
{
  // Source: ..\source\Apt\AptNativeHash.cpp line 262 (approximate)
  if (key == 0) {
    // Debug assertion failure
    AssertMsg("removeKey: key is null", "..\\source\\Apt\\AptNativeHash.cpp", 0x106);
    return;
  }

  // Hash calculation (case insensitive)
  uint hash = 0;
  byte *p = key;
  do {
    uint c = *p;
    p++;
    if (c >= 0x41 && c <= 0x5A) { // 'A' to 'Z'
      c += 0x20; // to lowercase
    }
    hash = hash * 0x21 + c;
  } while (c != 0);

  // Bitmask from thisPtr[0]
  uint mask = (1 << (thisPtr[0] & 0x1f)) - 1;
  uint bucketIndex = hash & mask;

  // Bucket array at thisPtr+4
  AptHashNode **buckets = *(AptHashNode ***)(thisPtr + 4);
  AptHashNode *node = buckets[bucketIndex];
  AptHashNode *prev = 0;

  while (node != 0) {
    // Compare hash first, then actual string
    if (node->hash == hash) {
      // String stored at (+0xc) of the first data object
      char *nodeKey = *(char **)(node->data1 + 0xc);
      if (_stricmp(nodeKey, (const char *)key) == 0) {
        break; // found
      }
    }
    prev = node;
    node = node->next;
  }

  if (node == 0) {
    return; // key not found
  }

  // Unlink node from bucket list
  if (prev == 0) {
    buckets[bucketIndex] = node->next; // was head
  } else {
    prev->next = node->next;
  }

  // Release the two data objects (calling destructors via table)
  // Each data object has a type index at offset 0 (low 15 bits)
  uint typeIndex1 = *(uint *)(node->data1) & 0x7fff;
  uint typeIndex2 = *(uint *)(node->data2) & 0x7fff;
  ((void (__thiscall *)(void *))destructorTable[typeIndex1])(node->data1);
  ((void (__thiscall *)(void *))destructorTable[typeIndex2])(node->data2);

  // Free the node itself (16 bytes)
  operator delete(node, 0x10);

  // Update count
  short *count = (short *)(thisPtr + 2);
  *count = *count - 1;
}