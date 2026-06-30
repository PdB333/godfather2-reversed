// FUNC_NAME: StringBuffer::appendWideString
void __thiscall StringBuffer::appendWideString(int thisPtr, wchar_t *sourceString)
{
  short *psVar1;
  undefined1 *puVar2;
  int iVar3;
  wchar_t *pwVar4;
  undefined4 *puVar5;
  undefined1 *local_514;
  undefined4 local_510;
  undefined4 local_50c;
  code *local_508;
  wchar_t local_504 [15]; // buffer for truncated string
  undefined2 local_4e6;
  undefined4 local_4c4;
  
  _memset(local_504,0,0x504); // clear local buffer (0x504 = 1284 bytes)
  _wcsncpy(local_504,sourceString,0xf); // copy at most 15 wchar_t
  local_4e6 = 0;
  local_514 = (undefined1 *)0x0;
  local_510 = 0;
  local_50c = 0;
  local_508 = (code *)0x0;
  FUN_004ddaf0(local_504,&local_514); // some string processing (e.g., trim/convert)
  puVar2 = local_514;
  if (local_514 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e; // fallback empty string
  }
  local_4c4 = FUN_004db320(puVar2,local_510); // get length or hash
  puVar5 = *(undefined4 **)(thisPtr + 8); // current write pointer
  if (puVar5 < *(undefined4 **)(thisPtr + 0xc)) { // check if space available
    *(undefined4 **)(thisPtr + 8) = puVar5 + 0x141; // advance pointer by 0x141 dwords (0x504 bytes)
    if (puVar5 != (undefined4 *)0x0) {
      pwVar4 = local_504;
      for (iVar3 = 0x141; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *(undefined4 *)pwVar4; // copy 4 bytes at a time
        pwVar4 = pwVar4 + 2; // advance source by 2 wchar_t (4 bytes)
        puVar5 = puVar5 + 1;
      }
    }
  }
  else {
    FUN_0069a140(puVar5,local_504); // handle overflow (reallocate?)
  }
  psVar1 = (short *)(*(int *)(thisPtr + 0x14) + 4); // increment some counter
  *psVar1 = *psVar1 + 1;
  if (local_514 != (undefined1 *)0x0) {
    (*local_508)(local_514); // free temporary buffer
  }
  return;
}