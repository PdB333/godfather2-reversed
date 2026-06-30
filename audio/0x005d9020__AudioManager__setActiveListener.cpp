// FUNC_NAME: AudioManager::setActiveListener
void __fastcall AudioManager::setActiveListener(int thisPtr)
{
  int iVar1;
  undefined1 *puVar2;
  float local_8;
  float local_4;
  
  if (DAT_012058e8 == thisPtr) {
    *(undefined4 *)(thisPtr + 0xa4) = 0;  // +0xA4: isActive flag
  }
  else {
    *(undefined4 *)(thisPtr + 0xa4) = 1;  // Mark as active
    DAT_012058e8 = thisPtr;                // Store as current active listener
    FUN_0060a460(*(undefined4 *)(thisPtr + 0x10));  // Release previous listener? +0x10: audio handle
    FUN_0060a460(*(undefined4 *)(thisPtr + 0x14));  // Release another handle? +0x14: audio handle
  }
  if (*(char *)(thisPtr + 0x130) != '\0') {  // +0x130: hasPosition flag
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x174),  // +0x174: audio system
                 *(undefined4 *)(thisPtr + 0x168),  // +0x168: position vector
                 thisPtr + 0x150);                  // +0x150: orientation vector
    FUN_0060add0(*(undefined4 *)(thisPtr + 0x174),
                 *(undefined4 *)(thisPtr + 0x164),  // +0x164: velocity vector
                 thisPtr + 0x140);                  // +0x140: another orientation vector
    FUN_0060aa90(*(undefined4 *)(thisPtr + 0x174),
                 *(undefined4 *)(thisPtr + 0x16c),  // +0x16C: listener properties
                 *(undefined4 *)(thisPtr + 0x160)); // +0x160: volume/pan settings
  }
  iVar1 = *(int *)(thisPtr + 0xb8 + *(int *)(thisPtr + 0x110) * 0xc);  // +0xB8: audio channel array, +0x110: channel index
  if (iVar1 != 0) {
    if (*(uint *)(thisPtr + 0x100) < 0x1000) {  // +0x100: audio buffer index
      puVar2 = &DAT_011a0f28 + *(uint *)(thisPtr + 0x100) * 0x38;  // Audio buffer table, 0x38 bytes per entry
    }
    else {
      puVar2 = (undefined1 *)0x0;
    }
    local_8 = DAT_00e2cd54 / (float)*(ushort *)(puVar2 + 2);  // Sample rate / sample count
    local_4 = DAT_00e2cd54 / (float)*(ushort *)(puVar2 + 4);  // Sample rate / another sample count
    FUN_0060ac80(*(undefined4 *)(thisPtr + 0x14), iVar1, &local_8);  // Set audio playback rate
  }
  return;
}