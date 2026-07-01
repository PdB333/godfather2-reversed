// FUNC_NAME: SomeClass::setSomeIntProperty
void __thiscall SomeClass::setSomeIntProperty(int *this, int newValue)
{
  int oldValue;
  code *virtualFunc;
  
  if (newValue != this[0x7bd]) {
    // Call some method at vtable+0x28 on object at this[0x16] with parameter 0x80
    (**(code **)(this[0x16] + 0x28))(0x80);
    oldValue = this[0x7bd];
    virtualFunc = *(code **)(*this + 0x1cc);
    this[0x7bd] = newValue;
    (*virtualFunc)(oldValue, newValue);
  }
  return;
}