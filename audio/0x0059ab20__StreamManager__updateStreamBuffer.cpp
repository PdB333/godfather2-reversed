// FUNC_NAME: StreamManager::updateStreamBuffer
void __fastcall StreamManager::updateStreamBuffer(int this)
{
  int streamBuffer;
  int result;
  
  streamBuffer = *(int *)(this + 8);
  if ((uint)*(ushort *)(streamBuffer + 2) != *(int *)(streamBuffer + 8) * 8 + 0xcU) {
    (**(code **)(*DAT_01205590 + 4))(); // likely error/assert handler
  }
  result = FUN_00599b10(this,*(undefined4 *)(streamBuffer + 4)); // validateStreamData
  if (result == 0) {
                    /* WARNING: Could not recover jumptable at 0x0059ab66. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*DAT_01205590 + 4))(); // error handler
    return;
  }
  FUN_00596030(streamBuffer + 0xc); // processStreamBufferData
  return;
}