// FUNC_NAME: StreamManager::updateStreamPriority
void __thiscall StreamManager::updateStreamPriority(int thisPtr, int streamIndex, float currentTime)
{
  int streamHandle;
  float deltaTime;
  float clampedDelta;
  
  // Initialize global timing factor if not done yet
  if ((_DAT_0112e004 & 1) == 0) {
    _DAT_0112e004 = _DAT_0112e004 | 1;
    _DAT_0112e000 = DAT_00d76310; // base time factor
  }
  
  // Calculate time delta since last update, masked to handle wrap-around
  deltaTime = (float)((uint)(currentTime - *(float *)(thisPtr + 0x2c)) & DAT_00e44680) * _DAT_0112e000;
  
  // Clamp delta time to max allowed (DAT_00d5780c)
  if (0.0 < deltaTime) {
    if (_DAT_00d5780c <= deltaTime) {
      deltaTime = _DAT_00d5780c;
    }
  } else {
    deltaTime = 0.0;
  }
  
  // Calculate remaining time before stream needs update
  deltaTime = _DAT_00d5780c - deltaTime;
  
  // If stream priority threshold is met (DAT_00e44598)
  if (DAT_00e44598 <= deltaTime) {
    // Check if stream handle already exists at offset +0x104 + streamIndex*4
    if (*(int *)(thisPtr + 0x104 + streamIndex * 4) == 0) {
      // Create new stream object at offset +0x84 + streamIndex*0x10
      uVar2 = FUN_00873ca0(streamIndex * 0x10 + 0x84 + thisPtr);
      *(int *)(thisPtr + 0x104 + streamIndex * 4) = uVar2;
    }
    streamHandle = *(int *)(thisPtr + 0x104 + streamIndex * 4);
    if (streamHandle != 0) {
      // Update stream with remaining time
      FUN_005e6700(streamHandle, deltaTime);
      return;
    }
  } else {
    // Priority too low - stop and destroy stream
    streamHandle = *(int *)(thisPtr + 0x104 + streamIndex * 4);
    if (streamHandle != 0) {
      FUN_005e6820(streamHandle, 0, 0); // Stop stream
      FUN_005e6660(streamHandle);       // Destroy stream object
      *(int *)(thisPtr + 0x104 + streamIndex * 4) = 0;
    }
  }
  return;
}