// FUNC_NAME: FlatMap::lookup
uint __thiscall FlatMap::lookup(uint key, uint *outValue)
{
  // +0x0c: pointer to sorted map structure
  int *mapPtr = *(int **)(this + 0x0c);
  if (mapPtr != 0) {
    uint count = (uint)*(ushort *)(mapPtr + 2);  // +0x02: number of entries (ushort)
    uint low = 0;
    if (count != 0) {
      uint high = count;
      do {
        uint mid = (high + low) >> 1;
        // +0x04: pointer to array of keys (uint*)
        uint *keyArray = *(uint **)(mapPtr + 4);
        if (keyArray[mid] < key) {
          low = mid + 1;
          mid = high;
        }
        high = mid;
      } while (low < high);
    }
    // Found?
    if (low < count) {
      uint *keyArray = *(uint **)(mapPtr + 4);
      if (keyArray[low] == key) {
        // +0x08: pointer to array of values (ushort*)
        ushort *valArray = *(ushort **)(mapPtr + 8);
        *outValue = (uint)valArray[low];
        // Return success (lower byte = 1, high bits come from valArray shifted right)
        return (uint)((uint)(valArray) >> 8) | 1;
      }
    }
  }
  // Not found: store the key itself as output, return failure
  *outValue = key;
  return (uint)outValue & 0xffffff00;
}