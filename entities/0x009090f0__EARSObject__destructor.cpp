// FUNC_NAME: EARSObject::destructor
int * __thiscall EARSObject::destructor(int *this, byte flags)
{
  if (*this != 0) {
    EARSObject::release(this);
  }
  if ((flags & 1) != 0) {
    EARSObject::operatorDelete(this);
  }
  return this;
}