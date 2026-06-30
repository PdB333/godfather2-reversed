// FUNC_NAME: LinkedListNode::assign
// Function at 0x0071da80: assignment operator for a linked list node structure.
// The node layout (offsets relative to this):
//   offset 0: int* mData       - pointer to the associated data object
//   offset 4: int  mPrev       - back pointer (encoded as int, but used as pointer)
//   offset 8: int  mPayload    - payload value copied directly
// The data object pointed to by mData also contains a back pointer at offset 4,
// which this function updates to maintain the list.

int* __thiscall LinkedListNode::assign(int* this, int* other)
{
  int otherData;

  // Avoid self-assignment
  if (this != other) {
    otherData = *other;

    // Only reassign if the data pointer differs
    if (*this != otherData) {
      // Release the current data object if it exists
      if (*this != 0) {
        FUN_004daf90(this);
      }

      // Take ownership of the data pointer from 'other'
      *this = otherData;

      // If the new data is non-null, update the linked list back pointers
      if (otherData != 0) {
        // Copy the back pointer from the data object's offset 4 into this node
        this[1] = *(int*)(otherData + 4);
        // Set the data object's back pointer to this node
        *(int**)(otherData + 4) = this;
      }
    }
  }

  // Copy the payload field directly
  this[2] = other[2];

  return this;
}