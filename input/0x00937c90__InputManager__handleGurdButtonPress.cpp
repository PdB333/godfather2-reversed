// FUNC_NAME: InputManager::handleGurdButtonPress
char InputManager::handleGurdButtonPress(byte *buttonName)
{
  byte localBuffer[64];
  char result = '\0';
  uint buttonIndex = 0;
  
  do {
    if (1 < buttonIndex) {
      return result;
    }
    // Build path: /gurd/buttons/button_%d/button
    FUN_00910160(localBuffer, "/gurd/buttons/button_%d/button", buttonIndex);
    
    // Compare strings (strcmp equivalent)
    byte *bufPtr = localBuffer;
    byte *namePtr = buttonName;
    int cmpResult;
    do {
      byte b1 = *bufPtr;
      byte b2 = *namePtr;
      bool lessThan = b1 < b2;
      if (b1 != b2) {
        cmpResult = (1 - (uint)lessThan) - (uint)(lessThan != 0);
        break;
      }
      if (b1 == 0) {
        cmpResult = 0;
        break;
      }
      b1 = bufPtr[1];
      b2 = namePtr[1];
      lessThan = b1 < b2;
      if (b1 != b2) {
        cmpResult = (1 - (uint)lessThan) - (uint)(lessThan != 0);
        break;
      }
      bufPtr += 2;
      namePtr += 2;
    } while (b1 != 0);
    
    if (cmpResult == 0) {
      // Build the full path and call RollOutButton
      FUN_00910160(localBuffer, &DAT_00e3266c, buttonIndex);
      FUN_005a04a0("RollOutButton", 0, &DAT_00d8a1e4, 1, localBuffer);
      result = '\x01';
    }
    buttonIndex++;
    if (result != '\0') {
      return result;
    }
  } while( true );
}