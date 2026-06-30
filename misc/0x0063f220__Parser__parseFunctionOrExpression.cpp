// FUNC_NAME: Parser::parseFunctionOrExpression
int Parser::parseFunctionOrExpression(int parserCtx)
{
  int *piVar1;
  int *in_EAX;
  undefined4 uVar2;
  int iVar3;
  int local_c;
  
  local_c = 1;
  FUN_0063fad0(parserCtx);  // parseNextToken
  do {
    if (*(int *)(parserCtx + 0xc) != 0x2c) {  // TOKEN_OPEN_PAREN
      return local_c;
    }
    *(undefined4 *)(parserCtx + 8) = *(undefined4 *)(parserCtx + 4);
    if (*(int *)(parserCtx + 0x14) == 0x11f) {  // TOKEN_IDENTIFIER
      uVar2 = FUN_00639c70(parserCtx + 0x10);  // parseExpression
      *(undefined4 *)(parserCtx + 0xc) = uVar2;
    }
    else {
      *(undefined4 *)(parserCtx + 0xc) = *(undefined4 *)(parserCtx + 0x14);
      *(undefined4 *)(parserCtx + 0x10) = *(undefined4 *)(parserCtx + 0x18);
      *(undefined4 *)(parserCtx + 0x14) = 0x11f;  // set TOKEN_IDENTIFIER
    }
    piVar1 = *(int **)(parserCtx + 0x1c);  // symbol table
    FUN_00642b00();  // getNextSymbol
    if (((*in_EAX == 0xb) && (piVar1[0xd] <= in_EAX[1])) && (in_EAX[1] < 0xfa)) {
      piVar1[9] = piVar1[9] + -1;
    }
    iVar3 = piVar1[9] + 1;
    if ((int)(uint)*(byte *)(*piVar1 + 0x47) < iVar3) {  // symbol table capacity
      if (0xf9 < iVar3) {
        FUN_00638b80("function or expression too complex");  // error message
        return local_c;
      }
      *(char *)(*piVar1 + 0x47) = (char)iVar3;  // update capacity
    }
    piVar1[9] = piVar1[9] + 1;  // increment symbol count
    FUN_00642d90(piVar1[9] + -1);  // initializeSymbol
    FUN_0063fad0(parserCtx);  // parseNextToken
    local_c = local_c + 1;
  } while( true );
}