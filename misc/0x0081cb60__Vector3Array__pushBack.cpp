// FUNC_NAME: Vector3Array::pushBack
void __thiscall Vector3Array::pushBack(int *this, undefined8 *value)
{
  undefined8 *puVar1;
  int iVar2;
  
  iVar2 = this[2]; // capacity
  if (this[1] == iVar2) { // size == capacity
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    else {
      iVar2 = iVar2 * 2; // double capacity
    }
    FUN_00818f90(iVar2); // reallocate
  }
  puVar1 = (undefined8 *)(*this + this[1] * 0xc); // pointer to new element (3 floats = 12 bytes)
  this[1] = this[1] + 1; // increment size
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = *value; // copy first 8 bytes (2 floats)
    *(undefined4 *)(puVar1 + 1) = *(undefined4 *)(value + 1); // copy last 4 bytes (1 float)
  }
  return;
}