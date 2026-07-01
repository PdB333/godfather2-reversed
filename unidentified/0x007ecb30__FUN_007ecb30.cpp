// FUNC_NAME: SomeEARSObject::destructor
int __thiscall SomeEARSObject::destructor(int this, byte flags)
{
  short refCount;
  
  refCount = *(short *)(this + 0x1a);
  *(undefined ***)(this + 8) = &PTR_FUN_00d6ffac; // vtable reset to base destructor
  while (refCount != 0) {
    FUN_00408090(); // likely release/decrement ref
    refCount = *(short *)(this + 0x1a);
  }
  if ((*(undefined4 **)(this + 0x10) != (undefined4 *)0x0) &&
     ((*(byte *)(this + 0x20) & 1) == 0)) {
    (**(code **)**(undefined4 **)(this + 0x10))(1); // call some cleanup function
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  return this;
}