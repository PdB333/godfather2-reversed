// FUNC_NAME: SomeClass::destructor
int * __thiscall SomeClass::destructor(int *this, byte flags)
{
  // Call destructor for member at offset +0x10 (param_1[4])
  if (this[4] != 0) {
    (*(code *)this[7])(this[4]);  // vtable call at +0x1C
  }
  // Call destructor for member at offset +0x00 (this[0])
  if (*this != 0) {
    (*(code *)this[3])(*this);  // vtable call at +0x0C
  }
  // If bit 0 of flags is set, call operator delete
  if ((flags & 1) != 0) {
    operatorDelete(this);
  }
  return this;
}