// FUNC_NAME: SomeClass::setStateVtable
undefined4 * SomeClass::setStateVtable(void)

{
  undefined4 *this;
  
  switch(this[1]) {
  case 0:
    *this = &PTR_LAB_00e381d8;
    this[1] = 0;
    return this;
  case 1:
    *this = &PTR_LAB_00e381f0;
    this[1] = 1;
    return this;
  default:
    return (undefined4 *)0x0;
  case 3:
    *this = &PTR_LAB_00e38208;
    this[1] = 3;
    return this;
  case 4:
    *this = &PTR_LAB_00e38220;
    this[1] = 4;
    return this;
  }
}