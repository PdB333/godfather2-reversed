// FUNC_NAME: SomeClass::releaseOrDelete
void __fastcall SomeClass::releaseOrDelete(int *this)
{
  if (this[4] != 0) {
    // Call release function at offset +0x1C (this[7]) on object at +0x10 (this[4])
    (*(code *)this[7])(this[4]);
  }
  if (*this != 0) {
    // Call delete function at offset +0x0C (this[3]) on object at +0x00 (this[0])
    (*(code *)this[3])(*this);
  }
  return;
}