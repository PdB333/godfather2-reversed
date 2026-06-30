// FUNC_NAME: TUIOptionsManager::isUIVisible
uint TUIOptionsManager::isUIVisible(void)
{
  char cVar1;
  uint in_EAX;
  int unaff_ESI; // this pointer
  
  // Check if UI options are enabled (+0x98 likely a bool/enable flag)
  if (*(int *)(unaff_ESI + 0x98) != 0) {
    // Check if some condition prevents UI from being shown
    cVar1 = FUN_00d06180(); // likely isSomethingBlocked() or similar
    if (cVar1 == '\0') {
      // Perform UI initialization/shutdown steps
      FUN_00d01870(); // likely hideCursor() or similar display function
      FUN_00d01890(); // likely showPointer() or similar input mode function
      FUN_00d09ab0(); // likely resetOverlayState() or similar
    }
    // Return whether UI should be visible (inverted check)
    cVar1 = FUN_00d06180(); // re-check the blocking condition
    return (uint)(cVar1 == '\0'); // returns 1 if not blocked, 0 if blocked
  }
  // Return 0 from register (already set by caller or default)
  return in_EAX & 0xffffff00;
}