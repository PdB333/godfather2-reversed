// FUNC_NAME: SomeClass::setSomeFlagsOrMode
void SomeClass::setSomeFlagsOrMode(int param_1)
{
  undefined4 *puVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)FUN_009c8f80(); // likely getSingleton() or getInstance()
  local_c = 2;   // +0x00: some enum or flag value
  local_8 = 0x10; // +0x04: another parameter (e.g., mode, size, or mask)
  local_4 = 0;    // +0x08: third parameter (e.g., flags or zero)
  (**(code **)*puVar1)(param_1, &local_c); // call virtual function on singleton with param_1 and the struct
  return;
}