// FUNC_NAME: SimpleArray::clearAndFree
void __fastcall SimpleArray::clearAndFree(int *this)
{
  int countMinusOne;
  int offset;

  countMinusOne = this[1] - 1; // count - 1, note: this[1] is count of elements
  if (-1 < countMinusOne) {
    offset = countMinusOne * 0xc; // 12 bytes per element
    do {
      // Check if the element's first field (vtable pointer or resource handle) is non-null
      if (*(int *)(this[0] + offset) != 0) {
        // Cleanup the element at this[0] + offset (12-byte object)
        FUN_004daf90(this[0] + offset);
      }
      countMinusOne = countMinusOne + -1;
      offset = offset + -0xc; // move to previous element
    } while (-1 < countMinusOne);
  }
  // Free the underlying array buffer if it exists
  if (this[0] != 0) {
    FUN_009c8f10(this[0]); // likely operator delete or free
  }
  return;
}