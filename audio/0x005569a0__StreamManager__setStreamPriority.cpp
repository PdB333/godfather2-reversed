// FUNC_NAME: StreamManager::setStreamPriority
void __thiscall StreamManager::setStreamPriority(undefined4 this, uint priority, int streamHandle, undefined4 param_4)
{
  // Call to set stream parameters (likely setting stream type or flags)
  FUN_00556ab0(0, 0, param_4, this, in_EAX);
  
  // Set priority field at offset +0x2c in stream handle structure
  // Priority is shifted right by 2 and OR'd with 0xC0000000 (likely a flag mask)
  *(uint *)(streamHandle + 0x2c) = priority >> 2 | 0xc0000000;
  
  // Perform some engine update
  FUN_0043b490();
  
  // Notify system with event 0x2001 (likely a stream priority change event)
  FUN_009f01f0(0x2001, param_4, 0);
  
  return;
}