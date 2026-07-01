// FUNC_NAME: Object::constructor
undefined4 __thiscall Object::constructor(Object *this, byte flag)
{
  // Call base class constructor (likely initializes base members)
  Object::baseConstructor();
  
  // If the lowest bit of flag is set, perform additional cleanup/initialization
  // This pattern is common in EARS engine for placement new or conditional destruction
  if ((flag & 1) != 0) {
    Object::cleanup(this);
  }
  
  return this;
}