// FUNC_NAME: Array::insertSorted
void Array::insertSorted(undefined4 *this, int newElement, undefined4 param_3)
{
  undefined4 uVar1;
  
  // Calculate the number of elements after insertion point
  // param_2 is initially the element to insert, then becomes the count
  for (newElement = newElement - (int)this; 1 < newElement >> 2; newElement = newElement + -4) {
    // Shift elements right to make room
    uVar1 = *(undefined4 *)((int)this + newElement + -4);
    *(undefined4 *)((int)this + newElement + -4) = *this;
    // Insert the new element at the correct position
    FUN_0068eec0(this,0,newElement + -4 >> 2,uVar1,param_3);
  }
  return;
}