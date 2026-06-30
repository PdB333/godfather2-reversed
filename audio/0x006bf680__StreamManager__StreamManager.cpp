// FUNC_NAME: StreamManager::StreamManager
undefined4 * __thiscall StreamManager::StreamManager(undefined4 *this, undefined4 param_2)
{
  // Initialize stream manager with 0x4000 buffer size (16KB stream buffer)
  StreamManager::initStreamBuffer(param_2, 0x4000);
  
  // Set vtable pointer
  *this = &StreamManager_vtable;
  
  // Initialize stream state pointers (offset 0x3C = 0xF * 4)
  this[0xf] = StreamState_Ready;   // +0x3C: stream state
  this[0x12] = StreamState_Playing; // +0x48: stream state
  this[0x14] = StreamState_Paused;  // +0x50: stream state
  this[0x15] = StreamState_Stopped; // +0x54: stream state
  this[0x16] = StreamState_Error;   // +0x58: stream state
  
  this[0x60] = 0;  // +0x180: stream volume (0 = max)
  this[0x61] = 5;  // +0x184: stream priority (5 = default)
  
  return this;
}