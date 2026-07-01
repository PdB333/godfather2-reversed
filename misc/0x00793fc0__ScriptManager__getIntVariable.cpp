// FUNC_NAME: ScriptManager::getIntVariable
int ScriptManager::getIntVariable(int scriptId, int varId, int *outValue)
{
  int localValue = 0;
  char result = FUN_004480d0(scriptId, varId, &localValue);
  if (result != '\0') {
    *outValue = localValue;
    return 1;
  }
  *outValue = 0;
  return 0;
}