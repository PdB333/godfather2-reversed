// FUN_NAME: Action::canActivate
bool __thiscall Action::canActivate(void)
{
  bool bVar1;
  char cVar2;
  int iVar3;
  int *actionFlags;
  int *innerPtr;
  
  actionFlags = *(int **)(this + 0x24);
  if ((*(byte *)(actionFlags + 0x14) & 0x40) != 0) {
    // Action has the "requires validation" flag
    iVar3 = *(int *)(*(int *)(this + 4) + 0x20);
    if (iVar3 != 0) {
      // Increment reference count on the internal data
      *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
    }
    iVar3 = FUN_004e8550(iVar3); // Perform action-specific validation
    if ((iVar3 != 0) && (FUN_004e4230() == '\0')) {
      // Validation returned non-zero but game is paused/blocked => fail
      return false;
    }
  }
  // Check global button masking
  if ((((*(uint *)(actionFlags + 0x14) & 0x200) != 0) &&
      (cVar2 = *(char *)(actionFlags + 0x11), cVar2 != '\0')) &&
     (DAT_011947e4 != 0) &&
     (((char)DAT_011947e4 & cVar2) == 0)) {
    // Action is masked by global disabled buttons => fail
    return false;
  }
  return true;
}