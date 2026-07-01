// FUNC_NAME: StreamManager::startStream
void __thiscall StreamManager::startStream(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
  int iVar1;
  float10 fVar2;
  
  // Check if there's an existing stream handle at +0x7a4 and release it
  if (*(undefined4 **)(this + 0x7a4) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(this + 0x7a4))(1);
    *(undefined4 *)(this + 0x7a4) = 0;
  }
  
  // Allocate memory for stream (0x44 bytes)
  iVar1 = FUN_009c8e50(0x44);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    // Initialize stream with param_2 (likely stream filename or ID)
    iVar1 = FUN_008c96f0(param_2);
  }
  
  // Store stream parameters
  *(undefined4 *)(this + 0x7ac) = param_3;  // +0x7ac: stream parameter 3
  *(undefined4 *)(this + 0x7b0) = param_4;  // +0x7b0: stream parameter 4
  *(int *)(this + 0x7a4) = iVar1;           // +0x7a4: stream handle
  *(undefined4 *)(this + 0x7b4) = param_5;  // +0x7b4: stream parameter 5
  
  if (iVar1 != 0) {
    // Configure stream playback
    FUN_008c93f0(this);
    fVar2 = (float10)FUN_008c9590();  // Get current time or playback position
    *(float *)(this + 0x79c) = (float)fVar2;  // +0x79c: stream start time
    *(undefined4 *)(this + 0x7a0) = 8;         // +0x7a0: stream state (8 = playing)
  }
  return;
}