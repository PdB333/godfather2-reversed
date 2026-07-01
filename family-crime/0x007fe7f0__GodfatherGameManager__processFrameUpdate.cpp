//FUNC_NAME: GodfatherGameManager::processFrameUpdate
void __thiscall GodfatherGameManager::processFrameUpdate(int *thisPtr, int inputData)
{
  int updateManager;
  int stackStruct[4]; // 16 bytes, but only 4 ints shown; actual layout may differ
  
  // Initialize or set input data
  setInputData(inputData);
  
  // Check global hash; if mismatch, reset state
  updateManager = getGlobalHash();
  if (updateManager != 0x3e8bf7b3) {
    resetState(inputData);
  }
  
  // Get the update manager and call its virtual update method (vtable+0x1c)
  updateManager = getUpdateManager();
  (**(code **)(*thisPtr + 0x1c))(updateManager + 0x30);
  
  // Build a stack-based update packet
  stackStruct[0] = 0;
  stackStruct[1] = 0;
  stackStruct[2] = 0;
  stackStruct[3] = _DAT_00d5780c; // global constant or state
  
  buildUpdatePacket(stackStruct);
  
  // Call another virtual method (vtable+0x20) with the packet
  (**(code **)(*thisPtr + 0x20))(stackStruct);
  
  return;
}