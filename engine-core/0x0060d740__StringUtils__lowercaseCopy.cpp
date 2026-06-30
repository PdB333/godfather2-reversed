// FUNC_NAME: StringUtils::lowercaseCopy
void StringUtils::lowercaseCopy(char *source)
{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 auStack_1c [2];
  undefined4 uStack_14;
  int iStack_10;
  
  // Calculate length of source string
  pcVar4 = source;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  
  iStack_10 = 0x60d763;
  iVar2 = -(int)(pcVar4 + (1 - (int)(source + 1)));
  
  // Allocate space on stack for copy
  pcVar4 = &stack0xfffffff4 + iVar2;
  iVar3 = iVar2 - (int)source;
  
  // Copy string to stack buffer
  do {
    cVar1 = *source;
    source[(int)(&stack0xfffffff4 + iVar3)] = cVar1;
    source = source + 1;
  } while (cVar1 != '\0');
  
  *(undefined1 **)((int)&iStack_10 + iVar2) = &stack0xfffffff4 + iVar2;
  *(undefined4 *)((int)&uStack_14 + iVar2) = 0x60d782;
  
  // Convert to lowercase
  __strlwr(*(char **)((int)&iStack_10 + iVar2));
  
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  
  *(int *)((int)&iStack_10 + iVar2) = (int)pcVar4 - (int)(&stack0xfffffff5 + iVar2);
  *(undefined1 **)((int)&uStack_14 + iVar2) = &stack0xfffffff4 + iVar2;
  *(undefined4 *)((int)auStack_1c + iVar2 + 4) = 0;
  *(undefined4 *)((int)auStack_1c + iVar2) = 0x60d7a4;
  
  // Call string hashing function
  FUN_00ab8560();
  return;
}