// FUNC_NAME: IdToByteMapper::findMapping
bool __thiscall IdToByteMapper::findMapping(int thisPtr, int key, char* outValue)
{
  bool found = false;
  uint index = 0;
  if (*(uint *)(thisPtr + 0x38) != 0) { // +0x38: count of entries
    int* entryPtr = *(int **)(thisPtr + 0x34); // +0x34: pointer to array of entries (each 8 bytes)
    while (*(int *)(*entryPtr + 4) != key) {   // first field of entry: pointer to structure; key is at offset +4
      index++;
      entryPtr += 2; // move to next entry (8 bytes)
      if (*(uint *)(thisPtr + 0x38) <= index) {
        return found;
      }
    }
    found = (entryPtr != (int *)0x0);
    if (found) {
      *outValue = (char)entryPtr[1]; // second field: byte value stored in lower byte
    }
  }
  return found;
}