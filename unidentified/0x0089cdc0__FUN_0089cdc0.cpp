// FUNC_NAME: SomeClass::destructor

int __thiscall SomeClass::destructor(int this, byte param_2)

{
  if (*(int *)(this + 8) != 0) {
    FUN_004daf90(this + 8);
  }
  if ((param_2 & 1) != 0) {
    operatorDelete(this);
  }
  return this;
}