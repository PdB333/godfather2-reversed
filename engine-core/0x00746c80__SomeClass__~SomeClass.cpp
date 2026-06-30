// FUNC_NAME: SomeClass::~SomeClass
undefined4 * __thiscall ~SomeClass(undefined4 *this, byte param_2)
{
  *this = &vtable_00d63f60; // set vtable to destructor vtable
  if (this[0x17] != 0) { // offset 0x5C: pointer to subcomponent
    destructComponent(this + 0x17); // FUN_004daf90
  }
  destructBase(); // FUN_004ac1e0 – base class destructor
  if ((param_2 & 1) != 0) {
    operatorDelete(this); // FUN_00624da0 – deallocation
  }
  return this;
}