// FUNC_NAME: EarsSoundData::initFromTemplate

void __thiscall EarsSoundData::initFromTemplate(int thisPtr, undefined4 param2, char isNew)
{
  void *destBuffer;
  undefined *srcData;
  
  // If creating a new instance (isNew == 0), call a virtual initialization method
  // via vtable at offset 0x3c on the internal pointer at this+0x04
  if (isNew == '\0') {
    (**(code **)(**(int **)(thisPtr + 4) + 0x3c))();
  }
  
  // Select template data based on a flag at this+0x1c (likely stereo/3D or loop flag)
  srcData = &g_AudioTemplateStereo;       // DAT_00e2e970
  if (*(char *)(thisPtr + 0x1c) == '\0') {
    srcData = &g_AudioTemplateMono;       // DAT_00e2e7c0
  }
  
  // Prepare internal allocator (may lock or flush pools)
  FUN_00418c50();
  
  // Allocate buffer for the template copy
  // Arguments: alignment=4, size=0x24 (maybe flags/pool?), then zeros and a pool index
  destBuffer = (void *)FUN_0060cd00(4, 0x24, 0, 1, 0);
  if (destBuffer != (void *)0x0) {
    _memcpy(destBuffer, srcData, 0x1b0);   // copy 432 bytes of audio setup data
    FUN_0060cde0();                         // release allocator lock/commit
  }
  
  // If global sound system is active, notify the sound manager
  if (DAT_0120587e != '\0') {
    // Call virtual function at vtable+0xE4 on the global sound manager pointer
    // with message 0xB4 and parameter 0 (e.g., eAudioCmd_InitInstance)
    (**(code **)(*DAT_01205750 + 0xe4))(DAT_01205750, 0xb4, 0);
  }
  return;
}