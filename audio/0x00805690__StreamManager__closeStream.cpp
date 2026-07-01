// FUNC_NAME: StreamManager::closeStream
void __fastcall StreamManager::closeStream(int this)
{
  if (*(char *)(this + 0xff8) != '\x01') {
    if (*(int *)(this + 0xff0) == 0) goto LAB_008056de;
    this = *(int *)(this + 0xff0) + -0x48;
  }
  if (this != 0) {
    if (*(int *)(this + 0xff0) != 0) {
      FUN_004daf90((undefined4 *)(this + 0xff0));  // likely BNKStreamManager::releaseStream
      *(undefined4 *)(this + 0xff0) = 0;
    }
    *(undefined1 *)(this + 0xff8) = 0;  // +0xff8: stream active flag
    *(undefined1 *)(this + 0xff9) = 0xff;  // +0xff9: stream state/priority
  }
LAB_008056de:
  FUN_007fce80();  // likely StreamManager::update or cleanup
  return;
}