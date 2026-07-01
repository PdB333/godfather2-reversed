// FUNC_NAME: EARSObject::destroyAllChildren
void __fastcall EARSObject::destroyAllChildren(int *this)
{
  int childCount;
  int childIndex;
  
  childIndex = this[1] + -1;
  if (-1 < childIndex) {
    childCount = childIndex * 0x130;
    do {
      // Call virtual destructor on each child object (vtable at offset 0)
      (*(code *)**(undefined4 **)(childCount + *this))(0);
      childIndex = childIndex + -1;
      childCount = childCount + -0x130;
    } while (-1 < childIndex);
  }
  // Call destroy on this object's data (vtable at this[4] + 4)
  (**(code **)(*(int *)this[4] + 4))(*this, 0);
  if (this[3] != 0) {
    // Call destroy on sibling/next object (vtable at this[4] + 4)
    (**(code **)(*(int *)this[4] + 4))(this[3], 0);
  }
  // Call final cleanup (vtable at this[4] + 0xc)
  (**(code **)(*(int *)this[4] + 0xc))();
  return;
}