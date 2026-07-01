// FUNC_NAME: ScriptTable::SetGlobalVariable
void ScriptTable::SetGlobalVariable(int param_1)

{
  if (param_1 != 0) {
    SetScriptVariable(&gScriptContext, param_1 + 0x3c, 0);
    return;
  }
  SetScriptVariable(&gScriptContext, 0, 0);
  return;
}