// Xbox PDB: struct Proto * __cdecl luaY_parser(struct lua_State *,struct Zio *,struct Mbuffer *)
// FUNC_NAME: ConfigFile::parseValue
undefined4 __thiscall ConfigFile::parseValue(int this, undefined4 param_2)
{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined1 local_614 [4];
  undefined4 local_610;
  undefined4 local_60c;
  int local_608;
  undefined4 local_604;
  int local_600;
  undefined4 local_5fc;
  undefined4 local_5e4;
  undefined4 local_5e0;
  
  pcVar2 = *(char **)(this + 0x10); // +0x10: current buffer pointer
  local_5e4 = 0;
  pcVar3 = pcVar2;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  uVar4 = FUN_00638920(param_2,pcVar2,(int)pcVar3 - (int)(pcVar2 + 1)); // parseString
  FUN_00638cd0(uVar4); // pushValue
  FUN_0063e530(local_614); // initTokenizer
  local_60c = local_610;
  if (local_600 == 0x11f) { // 0x11f = TOKEN_EOF
    local_608 = FUN_00639c70(&local_604); // parseExpression
  }
  else {
    local_608 = local_600;
    local_604 = local_5fc;
    local_600 = 0x11f;
  }
  FUN_006417c0(local_614); // destroyTokenizer
  if (local_608 != 0x11f) {
    FUN_00638b80("<eof> expected"); // error
  }
  FUN_0063e5a0(local_614); // freeTokenizer
  return local_5e0;
}