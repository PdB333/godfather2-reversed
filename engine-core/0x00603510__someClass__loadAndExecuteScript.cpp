// FUNC_NAME: someClass::loadAndExecuteScript
void __thiscall someClass::loadAndExecuteScript(int this, int param_2)
{
  char *scriptBuffer;
  char *local_14;
  int local_24;
  int local_20;
  int local_1c;
  void (*local_18)(int);
  void (*local_8)(char *);
  
  local_14 = (char *)0x0;
  local_10 = 0;
  local_c = 0;
  local_8 = (void (*)(char *))0x0;
  FUN_00603330(this,&local_14); // Load script data into buffer
  scriptBuffer = local_14;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = (void (*)(int))0x0;
  char *source = local_14;
  if (local_14 == (char *)0x0) {
    source = &DAT_0120546e; // Default empty string if no script loaded
  }
  FUN_00603610(param_2,&local_24,source,0); // Compile/parse script
  FUN_004d43f0(local_24,0,local_20); // Execute compiled script
  if (local_24 != 0) {
    (*local_18)(local_24); // Cleanup compiled script
  }
  if (scriptBuffer != (char *)0x0) {
    (*local_8)(scriptBuffer); // Free script buffer
  }
  return;
}