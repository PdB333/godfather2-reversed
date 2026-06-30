// FUNC_NAME: EntityHandle::operator==
undefined1 __thiscall EntityHandle::operator==(int *this, int *otherHandle)
{
  undefined1 result;
  
  result = 0;
  if ((*this == *otherHandle) && ((*this == 0 || (this[2] == otherHandle[2])))) {
    result = 1;
  }
  return result;
}