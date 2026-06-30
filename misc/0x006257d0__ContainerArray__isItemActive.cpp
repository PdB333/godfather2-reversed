// FUNC_NAME: ContainerArray::isItemActive
// Address: 0x006257d0
// Role: Checks whether an item at a given index is of a specific type (3 or 4) and active.
//   Items are stored as entries of 8 bytes each. The array starts at index 1; index <= 0 fetches a special sentinel.
//   m_pEnd (+0x8) points past the last valid entry, m_pBuffer (+0xC) points to the beginning of the array.
//   Item type is stored as the first int of each entry (3 = active, 4 = requires additional validation).

int ContainerArray::isItemActive(int index) {
  int* itemPtr;

  // If index is zero or negative, get a sentinel pointer (e.g., head of list)
  if (index < 1) {
    itemPtr = getSentinelPointer();  // FUN_00625430
  } else {
    // Compute pointer to the item: base + (index-1)*8
    itemPtr = (int*)(m_pBuffer + (index - 1) * 8);
    // If the item is beyond the end, it's invalid
    if (m_pEnd <= itemPtr) {
      return 0;
    }
  }

  if (itemPtr != nullptr) {
    // Type 3: always valid/active
    if (*itemPtr == 3) {
      return 1;
    }
    // Type 4: additionally check if index is active via external function
    if (*itemPtr == 4) {
      if (isIndexActive(&index)) { // FUN_00636850
        return 1;
      }
    }
  }
  return 0;
}