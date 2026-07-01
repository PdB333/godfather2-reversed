// FUNC_NAME: SomeClass::constructor

undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  this->baseClassConstructor();  // FUN_007875e0 - likely base class initialization
  
  if ((flags & 1) != 0) {
    operatorDelete(this);  // FUN_009c8eb0 - likely operator delete if construction fails
  }
  
  return this;
}