// FUNC_NAME: SomeClass::checkAndProcess
void __thiscall checkAndProcess(int this, undefined4 param_2)
{
  // +0x1c: some counter or size field
  // +0x14: another counter or limit field
  if (*(int *)(this + 0x1c) < *(int *)(this + 0x14)) {
    // Process the parameter
    FUN_0093f3a0(param_2);
    // Update global state at DAT_012069c4
    FUN_00408680(&DAT_012069c4);
  }
  return;
}