// FUNC_NAME: InputManager::isControllerConnected
undefined4 FUN_007c0b00(void)

{
  char cVar1;
  undefined4 uVar2;
  
  // Check controller 0x29 (41) for connection status
  uVar2 = FUN_00798f50(0x29);
  cVar1 = FUN_0079e920(uVar2);
  if (cVar1 != '\0') {
    return 1;
  }
  
  // Check controller 0xe (14) for connection status
  uVar2 = FUN_00798f50(0xe);
  cVar1 = FUN_0079e920(uVar2);
  
  // If controller 0xe not connected AND a special ID check fails, report connected
  if ((cVar1 == '\0') && (cVar1 = FUN_0079e920(0x6eae57f2), cVar1 == '\0')) {
    return 1;
  }
  
  return 0;
}