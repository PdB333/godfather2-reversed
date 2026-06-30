// FUNC_NAME: ScriptParser::parseBlock
void ScriptParser::parseBlock(int param_2, int param_3)
{
  int in_EAX;
  undefined *puVar1;
  undefined4 uVar2;
  int *piVar3;
  char *pcVar4;
  undefined *puVar5;
  int iVar6;
  int local_5d8 [374];
  
  piVar3 = local_5d8;
  FUN_0063e530(); // ScriptParser::initTokenStream
  *(int *)(local_5d8[0] + 0x3c) = param_3; // +0x3c: currentLineNumber
  if (*(int *)(in_EAX + 0xc) == 0x28) { // 0x28 = TOKEN_OPEN_BRACE
    piVar3 = (int *)0x11f; // 0x11f = TOKEN_EOF
    *(undefined4 *)(in_EAX + 8) = *(undefined4 *)(in_EAX + 4); // +0x8: prevToken, +0x4: currentToken
    if (*(int *)(in_EAX + 0x14) == 0x11f) { // +0x14: lookaheadToken
      uVar2 = FUN_00639c70(in_EAX + 0x10); // getNextToken
      *(undefined4 *)(in_EAX + 0xc) = uVar2; // +0xc: currentToken
    }
    else {
      *(undefined4 *)(in_EAX + 0xc) = *(undefined4 *)(in_EAX + 0x14);
      *(undefined4 *)(in_EAX + 0x10) = *(undefined4 *)(in_EAX + 0x18);
      *(undefined4 *)(in_EAX + 0x14) = 0x11f; // TOKEN_EOF
    }
    if (param_2 != 0) {
      FUN_0063dfb0(); // ScriptParser::parseStatements
    }
    FUN_0063eee0(); // ScriptParser::skipWhitespaceAndComments
    if (*(int *)(in_EAX + 0xc) == 0x29) { // 0x29 = TOKEN_CLOSE_BRACE
      *(undefined4 *)(in_EAX + 8) = *(undefined4 *)(in_EAX + 4);
      if (*(int *)(in_EAX + 0x14) == 0x11f) goto LAB_0063f1af;
      *(undefined4 *)(in_EAX + 0xc) = *(undefined4 *)(in_EAX + 0x14);
      *(undefined4 *)(in_EAX + 0x10) = *(undefined4 *)(in_EAX + 0x18);
      *(undefined4 *)(in_EAX + 0x14) = 0x11f;
      while( true ) {
        FUN_006417c0(); // ScriptParser::advanceToken
        if (*(int *)(in_EAX + 0xc) == 0x106) break; // 0x106 = TOKEN_END_OF_FILE
        if (param_3 == *(int *)(in_EAX + 4)) {
          uVar2 = FUN_00636c00("`%s' expected",PTR_DAT_00e2a8d4); // formatError
        }
        else {
          pcVar4 = "`%s' expected (to close `%s' at line %d)";
          puVar1 = PTR_DAT_00e2a8d4;
          puVar5 = PTR_s_function_00e2a8e0;
          iVar6 = param_3;
LAB_0063f19e:
          uVar2 = FUN_00636c00(pcVar4,puVar1,puVar5,iVar6);
        }
        FUN_00638b80(uVar2); // reportError
LAB_0063f1af:
        uVar2 = FUN_00639c70(in_EAX + 0x10);
        *(undefined4 *)(in_EAX + 0xc) = uVar2;
      }
      *(undefined4 *)(in_EAX + 8) = *(undefined4 *)(in_EAX + 4);
      if (*(int **)(in_EAX + 0x14) == piVar3) {
        uVar2 = FUN_00639c70(in_EAX + 0x10);
        *(undefined4 *)(in_EAX + 0xc) = uVar2;
      }
      else {
        *(undefined4 *)(in_EAX + 0xc) = *(undefined4 *)(in_EAX + 0x14);
        *(undefined4 *)(in_EAX + 0x10) = *(undefined4 *)(in_EAX + 0x18);
        *(int **)(in_EAX + 0x14) = piVar3;
      }
      FUN_0063e5a0(); // ScriptParser::finalizeBlock
      FUN_0063e460(local_5d8); // ScriptParser::cleanup
      return;
    }
    iVar6 = 0x29; // TOKEN_CLOSE_BRACE
  }
  else {
    iVar6 = 0x28; // TOKEN_OPEN_BRACE
  }
  puVar5 = &DAT_00e4242c;
  puVar1 = (undefined *)FUN_00636c00(&DAT_00e4242c,iVar6);
  pcVar4 = "`%s' expected";
  goto LAB_0063f19e;
}