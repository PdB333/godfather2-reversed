// FUNC_NAME: DCELinkNodeConstructor (linked list node constructor for a directed cyclic edge list)
void __thiscall DCELinkNodeConstructor(undefined4 *this, int listHeadOrNull, undefined4 data1, undefined4 data2, undefined4 data3, undefined8 *data4)
{
  // Set vtable pointer (likely for DCELinkNode base class or similar)
  *this = &PTR_FUN_00d74e6c;
  
  // If listHeadOrNull is non-null, insert this node after it (as a next pointer at +0x48)
  if (listHeadOrNull == 0) {
    listHeadOrNull = 0;
  }
  else {
    listHeadOrNull = listHeadOrNull + 0x48;
  }
  
  // +0x04: next pointer in linked list
  this[1] = listHeadOrNull;
  // +0x08: previous pointer (initialized to null)
  this[2] = 0;
  
  // If list is non-empty, link this node into the doubly-linked list
  if (listHeadOrNull != 0) {
    // +0x04 in the list node is the next pointer, so +0x04 + 4 = +0x08 is prev
    this[2] = *(undefined4 *)(listHeadOrNull + 4);  // Save current prev of the head's next
    *(undefined4 **)(listHeadOrNull + 4) = this + 1; // Set head's next node's prev to this
  }
  
  // +0x18: first data value
  this[6] = data1;
  // +0x1c: second data value
  this[7] = data2;
  // +0x20: third data value
  this[8] = data3;
  // +0x0c to 0x14: stores 8-byte data (likely a 64-bit value followed by 32-bit)
  *(undefined8 *)(this + 3) = *data4;
  this[5] = *(undefined4 *)(data4 + 1);
}