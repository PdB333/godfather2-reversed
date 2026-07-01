// FUNC_NAME: SomeClass::resolveInterface
bool __thiscall resolveInterface(int param_1, int param_2, int *param_3)
{
  // Check for interface ID 0xa7039c8 (likely IID_ISomeInterface)
  if (param_2 == 0xa7039c8) {
    *param_3 = param_1;  // Cast this to the interface
    return true;
  }
  
  *param_3 = 0;  // Clear output pointer
  
  // Check for interface ID 0x38523fc3 (likely IID_IOtherInterface)
  if (param_2 == 0x38523fc3) {
    *param_3 = param_1;  // Cast this to the other interface
  }
  
  // Return true if we resolved to a non-null interface
  return *param_3 != 0;
}