// FUNC_NAME: SomeClass::releaseOrFreeStrings
void SomeClass::releaseOrFreeStrings(void)
{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int this; // unaff_EDI

  // +0x34: pointer to some resource (e.g., a buffer or object)
  if (*(int *)(this + 0x34) != 0) {
    FUN_00587680(); // likely a free/release function
  }
  iVar3 = 0;
  // +0x24: count of strings/items
  if (0 < *(int *)(this + 0x24)) {
    do {
      // +0x28: pointer to array of pointers to strings
      pcVar2 = (char *)**(undefined4 **)(*(int *)(this + 0x28) + iVar3 * 4);
      if (pcVar2 != (char *)0x0) {
        cVar1 = *pcVar2;
        while (cVar1 != '\0') {
          pcVar2 = pcVar2 + 1;
          cVar1 = *pcVar2;
        }
      }
      FUN_005737c0(); // likely a free/delete function for each string
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(this + 0x24));
  }
  return;
}