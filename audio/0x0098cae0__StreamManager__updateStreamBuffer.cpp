// FUNC_NAME: StreamManager::updateStreamBuffer
void __thiscall StreamManager::updateStreamBuffer(int this, undefined4 param_2)
{
  uint uVar1;
  int local_10 [3];
  code *local_4;
  
  FUN_004d3bc0(param_2);
  FUN_004d5570();
  uVar1 = *(uint *)(this + 0x254); // +0x254: currentStreamPosition
  if (uVar1 < *(uint *)(this + 600)) { // +0x258: streamBufferSize
    *(uint *)(this + 0x254) = uVar1 + 0x10; // advance by 16 bytes
    if (uVar1 != 0) {
      FUN_004d3b50(local_10); // processStreamData
    }
  }
  else {
    FUN_0098c2b0(uVar1,local_10); // flushStreamBuffer
  }
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]); // callCompletionCallback
  }
  return;
}