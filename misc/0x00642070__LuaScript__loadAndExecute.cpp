// FUNC_NAME: LuaScript::loadAndExecute
int LuaScript::loadAndExecute(undefined4 *scriptData, undefined4 defaultParam)
{
  int luaState;
  int scriptResult;
  int local_c;
  
  luaState = getLuaState();
  scriptResult = compileScript(scriptData);
  *(int *)(luaState + 0x20) = scriptResult;
  if (scriptResult == 0) {
    *(undefined4 *)(luaState + 0x20) = defaultParam;
  }
  pushGlobalTable();
  if (local_c < 0) {
    local_c = reportError(*scriptData,"bad integer in %s",scriptData[4]);
  }
  *(int *)(luaState + 0x3c) = local_c;
  pushNil();
  *(undefined1 *)(luaState + 0x44) = pushNil();
  pushNil();
  *(undefined1 *)(luaState + 0x45) = pushNil();
  pushNil();
  *(undefined1 *)(luaState + 0x46) = pushNil();
  pushNil();
  *(undefined1 *)(luaState + 0x47) = pushNil();
  setupEnvironment(scriptData,luaState);
  callFunction(luaState);
  setupProtection(scriptData,luaState);
  executeFunction(luaState);
  setupArguments(scriptData,luaState);
  scriptResult = checkStack(luaState,*(undefined4 *)(luaState + 0x2c),0xff);
  if (scriptResult == 0) {
    reportError(*scriptData,"bad code in %s",scriptData[4]);
  }
  return luaState;
}