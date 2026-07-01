// FUNC_NAME: SomeGameClass::setSomeFlag
void SomeGameClass::setSomeFlag(void *this)
{
  undefined4 *puVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)SomeGlobalGetter_009c8f80(); // Returns some global singleton or manager
  local_c = 2;
  local_8 = 0x10;
  local_4 = 0;
  (**(code **)*puVar1)(this, &local_c); // Virtual call with parameters (flag, mask or ID)
  return;
}