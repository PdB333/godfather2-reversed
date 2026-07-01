// FUNC_NAME: ScriptEngine::parseBoolValue
undefined4 FUN_0077ab80(int this, undefined1 *outValue)

{
  int iVar1;
  
  if (*(int *)(this + 4) != 0) {
    iVar1 = FUN_004d4b70(&DAT_00e36d8c);  // likely string compare to "true"
    if (iVar1 == 0) {
      *outValue = 1;
      return 1;
    }
    iVar1 = FUN_004d4b70("false");  // string compare to "false"
    if (iVar1 == 0) {
      *outValue = 0;
      return 1;
    }
  }
  return 0;
}