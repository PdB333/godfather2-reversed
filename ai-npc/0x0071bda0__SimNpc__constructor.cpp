// FUNC_NAME: SimNpc::constructor
undefined4 __thiscall SimNpc::constructor(undefined4 this, byte param_2)
{
  // Call base class constructor (FUN_0071bd10)
  BaseClass::constructor();

  // If flag bit 0 is set, call cleanup/destructor (FUN_009c8eb0)
  if ((param_2 & 1) != 0) {
    SimNpc::destructor(this);
  }

  return param_1; // implicit return of 'this' pointer
}