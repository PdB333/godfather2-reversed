// FUNC_NAME: Vector3Array::pushBack
void __thiscall Vector3Array::pushBack(int *this, undefined8 *value)
{
  undefined8 *puVar1;
  int iVar2;
  
  iVar2 = this[2]; // +0x08 capacity
  if (this[1] == iVar2) { // +0x04 size == capacity
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    else {
      iVar2 = iVar2 * 2;
    }
    FUN_006ad900(iVar2); // reallocate with new capacity
  }
  puVar1 = (undefined8 *)(*this + this[1] * 0xc); // +0x00 data pointer, 0xc = sizeof(Vector3)
  this[1] = this[1] + 1; // increment size
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = *value; // copy x,y (first 8 bytes)
    *(undefined4 *)(puVar1 + 1) = *(undefined4 *)(value + 1); // copy z (last 4 bytes)
  }
  return;
}