// FUNC_NAME: StreamManager::clearStreams
void __fastcall StreamManager::clearStreams(int thisPtr)
{
  uint streamIndex;
  int streamData;
  int *streamEntry;
  uint streamCount;
  
  streamIndex = 0;
  if (*(int *)(thisPtr + 0xd0) != 0) { // +0xD0: streamCount
    do {
      streamData = *(int *)(*(int *)(thisPtr + 0xcc) + 8 + streamIndex * 0x10); // +0xCC: streamArray pointer
      streamEntry = (int *)(*(int *)(thisPtr + 0xcc) + streamIndex * 0x10);
      if (streamData != 0) {
        FUN_009e71f0(&local_5, streamData); // likely releaseStreamData
        FUN_009f01a0(); // likely freeMemory
        streamEntry[2] = 0; // +8: streamData pointer cleared
      }
      if ((undefined4 *)streamEntry[1] != (undefined4 *)0x0) { // +4: some resource pointer
        (*(code *)**(undefined4 **)streamEntry[1])(1); // release via vtable
        streamEntry[1] = 0;
      }
      if ((undefined4 *)*streamEntry != (undefined4 *)0x0) { // +0: another resource pointer
        (*(code *)**(undefined4 **)*streamEntry)(1); // release via vtable
        *streamEntry = 0;
      }
      streamIndex = streamIndex + 1;
    } while (streamIndex < *(uint *)(thisPtr + 0xd0)); // +0xD0: streamCount
  }
  *(undefined4 *)(thisPtr + 0xb8) = 0; // +0xB8: some state flag
  FUN_009c8f10(*(undefined4 *)(thisPtr + 0xb4)); // +0xB4: release buffer
  *(undefined4 *)(thisPtr + 0xb4) = 0; // +0xB4: buffer pointer cleared
  *(undefined4 *)(thisPtr + 0xbc) = 0; // +0xBC: another state flag
  return;
}