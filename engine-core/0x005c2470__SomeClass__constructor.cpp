// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte param_2)

{
  char cVar1;
  
  // Call base constructor
  SomeClass::baseConstructor(this);
  
  // Check if param_2 has bit 0 set
  if ((param_2 & 1) != 0) {
    // Call some initialization check
    cVar1 = SomeClass::someInitCheck(this);
    if (cVar1 == '\0') {
      // Call virtual function via vtable to handle failure
      (**(code **)(**(int **)(DAT_012234ec + 4))(4))(this,0);
    }
  }
  return this;
}