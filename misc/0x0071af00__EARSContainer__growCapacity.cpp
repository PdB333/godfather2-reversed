// FUNC_NAME: EARSContainer::growCapacity
void __thiscall EARSContainer::growCapacity(int *this, int newCapacity)
{
  int *oldData;
  int *newData;
  int *elementPtr;
  int *srcElement;
  int *dstElement;
  int index;
  unsigned int count;
  
  if (this[2] < newCapacity) {
    oldData = (int *)this[0];
    if (oldData == (int *)0x0) {
      oldData = &DAT_01218a14;  // default empty placeholder
    }
    // allocate new block: size = newCapacity * 12
    newData = (int *)(*(code *)**(undefined4 **)this[4])(newCapacity * 12, oldData);
    if (this[0] != 0) {
      count = 0;
      if (this[1] != 0) {
        index = 0;
        do {
          srcElement = (int *)(this[0] + index);
          dstElement = newData + index / 4;  // offset in ints
          if (newData != (int *)0x0) {
            // copy element fields
            dstElement[0] = srcElement[0];
            dstElement[1] = 0;
            if (srcElement[0] != 0) {
              dstElement[1] = *(int *)(srcElement[0] + 4);
              *(int **)(srcElement[0] + 4) = dstElement;
            }
            dstElement[2] = srcElement[2];
          }
          // destroy old element
          FUN_004daf90(srcElement);
          count = count + 1;
          index = index + 12;
          dstElement = dstElement + 3;
          newCapacity = this;  // harmless loop artifact
        } while (count < (unsigned int)this[1]);
      }
      // deallocate old memory
      (*(code **)(*(int *)this[4] + 4))(this[0], 0);
    }
    this[0] = (int)newData;
    this[2] = (int)newCapacity;  // actually this[2] = newCapacity (but loop corrupted variable)
  }
  return;
}