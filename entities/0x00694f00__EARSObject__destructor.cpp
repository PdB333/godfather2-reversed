// FUNC_NAME: EARSObject::destructor
int __thiscall EARSObject::destructor(int this, byte flags)
{
  if (*(int *)(this + 0xc) != 0) {
    (**(code **)(this + 0x18))(*(int *)(this + 0xc));
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  return this;
}