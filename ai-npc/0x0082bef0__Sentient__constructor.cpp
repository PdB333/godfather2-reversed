// FUNC_NAME: Sentient::constructor
undefined4 __thiscall Sentient::constructor(Sentient* this, byte flags)
{
  // Call base class Animated constructor
  Animated::constructor();
  // If bit 0 of flags is set, call placement delete for this object
  if ((flags & 1) != 0) {
    operatorDelete(this);
  }
  return this;
}