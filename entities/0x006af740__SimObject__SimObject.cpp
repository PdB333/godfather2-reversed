// FUNC_NAME: SimObject::SimObject
undefined4 __thiscall SimObject::SimObject(SimObject *this, byte param_2)
{
  // Call base class constructor (likely EARS::Framework::Object)
  Object::Object(this);
  if ((param_2 & 1) != 0) {
    // If flag bit 0 is set, perform additional initialization (e.g., allocate object system resources)
    FUN_009c8eb0(this);
  }
  return this;
}