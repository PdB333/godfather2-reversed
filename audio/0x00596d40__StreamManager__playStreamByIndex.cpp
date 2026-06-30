// FUNC_NAME: StreamManager::playStreamByIndex

void StreamManager::playStreamByIndex(void)
{
  int iVar1;
  uint streamIndex; // in_EAX
  int streamEntry;
  int streamBuffer[16]; // auStack_a4: 64 bytes, 16 ints
  int returnValue; // auStack_a8: 4 bytes
  
  // Check if stream index is valid (0-255) and if the stream entry exists
  if ((streamIndex < 0x100) && (streamEntry = streamLookupTable[streamIndex], streamEntry != 0)) {
    // Call vtable function at offset 0x28 from global object pointer (likely stop/clear)
    (**(code **)(*g_GlobalObject1 + 0x28))();
    
    // Call helper function (perhaps stop all mixing or reset)
    FUN_005974f0(1, 0);
    
    streamEntry = streamLookupTable[streamIndex]; // Re-fetch, but same
    if (streamEntry == 0) {
      // If stream entry became null, call another vtable function (error?)
      (**(code **)(*g_GlobalObject2 + 4))();
    }
    
    // Prepare stream buffer flags: set bit 0, clear bits 1-2, keep others
    streamBuffer[0] = (streamBuffer[0] & 0xfffffff9) | 1;
    streamBuffer[1] = 0; // +0x04
    streamBuffer[2] = 0; // +0x08
    streamBuffer[3] = *(int *)(streamEntry + 8); // +0x10: stream data (e.g., frequency)
    
    // Call vtable function at offset 0x40 from another global object (initialize stream)
    (**(code **)(*g_GlobalObject3 + 0x40))(streamBuffer);
    
    // Finalize stream setup
    FUN_00597370(&returnValue);
  }
  return;
}