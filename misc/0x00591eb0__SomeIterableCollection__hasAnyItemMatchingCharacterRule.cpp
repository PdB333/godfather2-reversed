// FUNC_NAME: SomeIterableCollection::hasAnyItemMatchingCharacterRule
undefined4 __thiscall SomeIterableCollection::hasAnyItemMatchingCharacterRule(int this, undefined4 param_2)
{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  // +0x01: count of items in collection (char)
  if (*(char *)(this + 1) > '\0') {
    do {
      // +0x08: array of pointers to strings (4 bytes each)
      // Get first character of current string
      cVar1 = **(char **)(*(int *)(this + 8) + iVar2 * 4);
      // Check if character is less than newline (0x0A) - possibly a rule/classification check
      if ((cVar1 < '\n') && 
          // Use jump table at PTR_FUN_0103af90 indexed by character value
          (cVar1 = (*(code *)(&PTR_FUN_0103af90)[cVar1])(param_2), cVar1 != '\0'))
      {
        return 1; // Match found
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(char *)(this + 1));
  }
  return 0; // No match
}