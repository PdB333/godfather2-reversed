// FUNC_NAME: AudioManager::updateStreamState
void __thiscall AudioManager::updateStreamState(int *this, int *streamState, int param3)
{
  int uVar1;
  
  if (param3 != 0) {
    if (param3 != 0) {
      uVar1 = (**(code **)(*this + 0x70))(0);  // getStreamHandle
      uVar1 = (**(code **)(*this + 0x80))(0, uVar1);  // getStreamBuffer
      FUN_005a04a0(uVar1);  // processStreamBuffer
      return;
    }
  }
  else if (*streamState != 0) {
    uVar1 = (**(code **)(*this + 0x70))(0);  // getStreamHandle
    uVar1 = (**(code **)(*this + 0x74))(0, uVar1);  // getStreamData
    FUN_005a04a0(uVar1);  // processStreamData
    *streamState = *streamState + -1;  // decrement stream state counter
    (**(code **)(*this + 0x6c))(*streamState);  // setStreamState
    uVar1 = (**(code **)(*this + 0x70))(0);  // getStreamHandle
    uVar1 = (**(code **)(*this + 0x78))(0, uVar1);  // getStreamBuffer2
    FUN_005a04a0(uVar1);  // processStreamBuffer
  }
  return;
}