// FUNC_NAME: SomeClass::destructor
int __thiscall SomeClass::destructor(int this, byte flags)
{
  // Release various allocated resources at known offsets
  if (*(int *)(this + 0x70) != 0) {
    FUN_009c8f10(*(int *)(this + 0x70));  // Release resource at +0x70
  }
  if (*(int *)(this + 100) != 0) {
    FUN_009c8f10(*(int *)(this + 100));   // Release resource at +0x64
  }
  if (*(int *)(this + 0x58) != 0) {
    FUN_009c8f10(*(int *)(this + 0x58));  // Release resource at +0x58
  }
  if (*(int *)(this + 0x4c) != 0) {
    FUN_009c8f10(*(int *)(this + 0x4c));  // Release resource at +0x4c
  }
  FUN_005c16e0();  // Base class destructor or cleanup
  if ((flags & 1) != 0) {
    FUN_005c4480(this);  // operator delete if flag set
  }
  return this;
}