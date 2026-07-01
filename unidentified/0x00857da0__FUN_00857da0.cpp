// FUNC_NAME: SomeClass::setSomeFlagsOrState
void SomeClass::setSomeFlagsOrState(int param_1)
{
  undefined4 *puVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)FUN_009c8f80(); // likely returns a pointer to a global or singleton
  local_c = 2;   // +0x00: some flag or value
  local_8 = 0x10; // +0x04: another flag or value
  local_4 = 0;    // +0x08: third flag or value
  (**(code **)*puVar1)(param_1, &local_c); // call a function pointer from the returned object
  return;
}