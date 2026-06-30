// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(void)

{
  undefined4 *this;
  undefined4 unaff_retaddr;
  undefined4 allocSize;
  undefined4 unknownArg2;
  undefined4 unknownArg3;
  
  this = (undefined4 *)FUN_009c8f80();
  allocSize = 2;
  unknownArg2 = 0x10;
  unknownArg3 = 0;
  this = (undefined4 *)(**(code **)*this)(0x70,&allocSize);
  if (this != (undefined4 *)0x0) {
    FUN_00416a70(unknownArg3,unaff_retaddr);
    *this = &PTR_FUN_00d58020;
    return this;
  }
  return (undefined4 *)0x0;
}