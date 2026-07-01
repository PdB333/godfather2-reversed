// FUNC_NAME: ResourceVector::push_back
void __thiscall ResourceVector::push_back(int *this, undefined4 *value)
{
  undefined4 *dest;
  int capacity;
  
  capacity = this[2];
  if (this[1] == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_00821e00(capacity);  // reallocate or grow internal buffer (likely resize)
  }
  dest = (undefined4 *)(*this + this[1] * 4);
  this[1] = this[1] + 1;  // increment size
  if (dest != (undefined4 *)0x0) {
    *dest = *value;  // copy element
  }
  return;
}