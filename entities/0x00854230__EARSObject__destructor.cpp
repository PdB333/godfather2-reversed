// FUNC_NAME: EARSObject::destructor
int __thiscall EARSObject::destructor(int this, byte flags)
{
  int *refCountPtr;
  
  if (*(int *)(this + 0x10) != 0) {
    refCountPtr = (int *)(*(int *)(this + 0x10) + 4); // +0x14: reference count
    *refCountPtr = *refCountPtr + -1;
    if ((*(int **)(this + 0x10))[1] == 0) {
      (**(code **)(**(int **)(this + 0x10) + 4))(); // call vtable destructor
    }
    *(undefined4 *)(this + 0x10) = 0; // +0x10: clear pointer
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  return this;
}