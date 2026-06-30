// FUNC_NAME: parseWideDigitString
void parseWideDigitString(int wideString, int *param_2)
{
  int iVar1;
  int iVar2;
  undefined2 local_8 [4];
  
  iVar1 = _iswdigit(*(wint_t *)(wideString + *param_2 * 2));
  for (iVar2 = 0; (iVar1 != 0 && (iVar2 < 4)); iVar2 = iVar2 + 1) {
    iVar1 = *param_2 + 1;
    local_8[iVar2] = *(undefined2 *)(wideString + *param_2 * 2);
    *param_2 = iVar1;
    iVar1 = _iswdigit(*(wint_t *)(wideString + iVar1 * 2));
  }
  local_8[iVar2] = 0;
  thunk_FUN_00b99984(local_8);
  return;
}