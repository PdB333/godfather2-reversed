// FUNC_NAME: SomeClass::getSomeValue
void __thiscall getSomeValue(int *this, undefined4 *outValue)
{
  if (*this != 0) {
    *outValue = **(undefined4 **)(*this + 0x14); // dereference this->ptr + 0x14
    return;
  }
  *outValue = 0;
  return;
}