// FUNC_NAME: Vector4Array::pushBack
void __thiscall Vector4Array::pushBack(int *this, undefined4 *value)
{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = this[2]; // capacity
  if (this[1] == iVar2) { // size == capacity
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    else {
      iVar2 = iVar2 * 2; // double capacity
    }
    FUN_008affc0(iVar2); // reallocate
  }
  puVar1 = (undefined4 *)(*this + this[1] * 4); // base + size * 4
  this[1] = this[1] + 1; // increment size
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = *value; // copy value
  }
  return;
}