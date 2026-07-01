// FUNC_NAME: EARSObject::destructor
int __thiscall EARSObject::destructor(int this, byte flags)
{
  if (*(int *)(this + 4) != 0) {
    (**(code **)(this + 0x10))(*(int *)(this + 4));
  }
  if ((flags & 1) != 0) {
    EARSObject::operatorDelete(this);
  }
  return this;
}