// FUNC_NAME: BinaryTree::mergeNodes
void __thiscall BinaryTree::mergeNodes(BinaryTree* this, BinaryTree* other)
{
  char otherRootValue;
  undefined4 *otherNodePtr;
  undefined4 *thisNodePtr;
  undefined4 value1, value2, value3, value4, value5, value6, value7;

  otherRootValue = *(char*)*other;
  if (*(char*)*this == 0x02) {
    *(undefined1*)*this = 0x02; // overkill, already set
    if (otherRootValue == 0x02) {
      FUN_00582b70(); // likely handleBothEmptyOrError
      return;
    }
    // This is a leaf (0x02), other is not -> copy other's data into this
    otherNodePtr = (undefined4 *)other[1];
  }
  else {
    if (otherRootValue != 0x02) {
      *(undefined1*)*this = 0; // both non-02? set to 0 (emptyish)
      return;
    }
    // This is not leaf, other is leaf (0x02) -> copy this's data into other? 
    // Actually sets this to 0x02, then copies from other to this's data slot.
    *(undefined1*)*this = 0x02;
    otherNodePtr = (undefined4 *)other[1];
  }
  // copy 8 dwords from otherNodePtr to this's data slot
  thisNodePtr = (undefined4 *)this[1];
  // copy first 4
  thisNodePtr[0] = otherNodePtr[0];
  thisNodePtr[1] = otherNodePtr[1];
  thisNodePtr[2] = otherNodePtr[2];
  thisNodePtr[3] = otherNodePtr[3];
  // copy next 4
  thisNodePtr[4] = otherNodePtr[4];
  thisNodePtr[5] = otherNodePtr[5];
  thisNodePtr[6] = otherNodePtr[6];
  thisNodePtr[7] = otherNodePtr[7];
}