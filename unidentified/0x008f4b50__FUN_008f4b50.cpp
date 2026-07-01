// FUNC_NAME: Unknown::logMessageWithTimestamp
void FUN_008f4b50(undefined2 **param_1)

{
  char cVar1;
  char *pcVar2;
  undefined2 *puVar3;
  char *pcVar4;
  char *local_20;          // +0x00: local string buffer
  undefined4 local_1c;     // +0x04: unknown
  undefined4 local_18;     // +0x08: unknown
  code *local_14;          // +0x0c: cleanup function pointer for local_20
  undefined2 *local_10;    // +0x10: local buffer (undefined2*)
  undefined4 local_c;      // +0x14: unknown
  code *local_4;           // +0x18: cleanup function pointer for local_10
  
  local_20 = (char *)0x0;
  local_1c = 0;
  local_18 = 0;
  local_14 = (code *)0x0;
  FUN_008f2280(&local_20);   // likely retrieve a formatted timestamp string
  pcVar4 = local_20;
  if (local_20 == (char *)0x0) {
    pcVar4 = &DAT_0120546e;  // fallback string (maybe "unknown" or empty)
  }
  pcVar2 = pcVar4;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');   // calculate length of string
  FUN_004dba80(pcVar4,(int)pcVar2 - (int)(pcVar4 + 1));  // call to log/output function with string + length
  if (param_1 != &local_10) {   // if param_1 is not the local stack, copy data
    puVar3 = local_10;
    if (local_10 == (undefined2 *)0x0) {
      puVar3 = &DAT_00e2df14;   // another fallback? or error string
    }
    FUN_004dbb10(puVar3,0,local_c);   // possibly format/copy output
  }
  if (local_10 != (undefined2 *)0x0) {
    (*local_4)(local_10);   // cleanup for local_10
  }
  if (local_20 != (char *)0x0) {
    (*local_14)(local_20);   // cleanup for local_20
  }
  return;
}