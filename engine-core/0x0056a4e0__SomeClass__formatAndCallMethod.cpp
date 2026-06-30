// FUNC_NAME: SomeClass::formatAndCallMethod
void SomeClass::formatAndCallMethod(int param_1, int param_2)
{
  char buffer[15]; // stack buffer for formatted string
  char nullTerminator = 0; // ensures null termination
  
  __snprintf(buffer, 0x10, "%d"); // format integer (missing argument? likely param_1 or param_2)
  nullTerminator = 0; // redundant null terminator
  
  // Call virtual function at offset 0x14 from global object at DAT_012234e0
  // This appears to be a method call on some object, passing param_1, param_2, and the formatted string
  (**(code **)(*DAT_012234e0 + 0x14))(param_1, param_2, buffer);
}