// FUNC_NAME: ScriptParser::expectToken
void __thiscall ScriptParser::expectToken(int this, int expectedTokenType)
{
  code *handler;
  int currentTokenType;
  undefined4 tokenString1;
  undefined4 tokenString2;
  int lineNumber;
  
  if (*(int *)(this + 0xc) != lineNumber) {
    if (expectedTokenType == *(int *)(this + 4)) {
      ScriptParser::advanceToken(this);
      return;
    }
    if (currentTokenType < 0x101) {
      tokenString1 = ScriptParser::getTokenString(&DAT_00e4242c);
    }
    else {
      tokenString1 = *(undefined4 *)(&DAT_00e2a4bc + currentTokenType * 4);
    }
    if (lineNumber < 0x101) {
      tokenString2 = ScriptParser::getTokenString(&DAT_00e4242c);
    }
    else {
      tokenString2 = *(undefined4 *)(&DAT_00e2a4bc + lineNumber * 4);
    }
    tokenString1 = ScriptParser::formatError("`%s\' expected (to close `%s\' at line %d)",tokenString2,tokenString1,expectedTokenType);
    ScriptParser::reportError(tokenString1);
    handler = (code *)swi(3);
    (*handler)();
    return;
  }
  *(undefined4 *)(this + 8) = *(undefined4 *)(this + 4);
  if (*(int *)(this + 0x14) != 0x11f) {
    *(undefined4 *)(this + 0xc) = *(undefined4 *)(this + 0x14);
    *(undefined4 *)(this + 0x10) = *(undefined4 *)(this + 0x18);
    *(undefined4 *)(this + 0x14) = 0x11f;
    return;
  }
  tokenString1 = ScriptParser::getNextToken(this + 0x10);
  *(undefined4 *)(this + 0xc) = tokenString1;
  return;
}