// FUNC_NAME: StreamManager::updateStreaming
void __thiscall StreamManager::updateStreaming(int thisPtr, char param_2)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  local_8 = 0;
  local_4 = 0;
  if (param_2 != '\0') {
    // Force flush: use the "force" stream handle at +0xA0
    local_c = *(undefined4 *)(thisPtr + 0xa0);
    FUN_00408a00(&local_c,0);  // likely StreamManager::closeStream
    FUN_00981ab0(thisPtr);     // likely StreamManager::resetStreaming
    iVar1 = FUN_008ff3e0();    // likely getCurrentStreamManager
    if (iVar1 == thisPtr) {
      FUN_008ff3f0(0);         // likely setCurrentStreamManager(NULL)
    }
    FUN_00894c90(0x191d8e5);   // likely debug/log with hash
    FUN_008fddc0();            // likely StreamManager::shutdown
    local_c = DAT_0112fee8;    // global stream handle
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);  // close global stream
    return;
  }
  // Normal update: use the "normal" stream handle at +0xA8
  local_c = *(undefined4 *)(thisPtr + 0xa8);
  FUN_00408a00(&local_c,0);    // close stream
  *(int *)(thisPtr + 0x68) = *(int *)(thisPtr + 0x68) + 1;  // +0x68: currentStreamIndex
  if (*(int *)(thisPtr + 0x68) == *(int *)(thisPtr + 0x6c)) {  // +0x6C: maxStreamIndex
    // Check for pending streams: array at +0x78, each entry 8 bytes (4 byte handle + 4 byte flag)
    pcVar2 = (char *)(thisPtr + 0x7c);  // +0x7C: first flag byte
    uVar3 = 0;
    while ((*(int *)(pcVar2 + -4) == 0 || (*pcVar2 != '\0'))) {  // handle != 0 and flag != 0 means pending
      uVar3 = uVar3 + 1;
      pcVar2 = pcVar2 + 8;
      if (2 < uVar3) {
        return;
      }
    }
    FUN_008fe990();  // likely StreamManager::processNextPendingStream
  }
  return;
}