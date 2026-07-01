// FUNC_NAME: VideoPlayerManager::initialize
undefined4 * __thiscall VideoPlayerManager::initialize(undefined4 *this, undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  this[1] = 1; // +0x04: m_initialized = true
  this[2] = 0; // +0x08: m_state = 0
  this[3] = &PTR_LAB_00d7d010; // +0x0C: vtable pointer
  DAT_01129820 = this; // global singleton pointer
  *this = &PTR_FUN_00d7d018; // +0x00: vtable
  this[3] = &PTR_LAB_00d7d014; // +0x0C: another vtable pointer
  this[4] = param_2; // +0x10: some parameter
  *(undefined1 *)(this + 5) = 0; // +0x14: byte field
  *(undefined1 *)((int)this + 0x15) = 0; // +0x15: byte field
  *(undefined1 *)((int)this + 0x16) = 0; // +0x16: byte field
  *(undefined1 *)((int)this + 0x17) = 0; // +0x17: byte field
  this[6] = 0; // +0x18: dword field
  *(undefined1 *)(this + 7) = 0; // +0x1C: byte field
  
  // Register message system strings
  FUN_00408240(&DAT_0112ddd8, "iMsgSystemRequestVideoPlayerShutdown");
  FUN_00408240(&DAT_0112dde0, "iMsgSystemVideoPlayerShutdownPending");
  FUN_00408240(&DAT_0112dde8, "iMsgSystemVideoPlayerShutdownComplete");
  
  // Call virtual function on param_2 (some object)
  (**(code **)(*(int *)this[4] + 8))();
  
  // Handle video player shutdown if needed
  if (DAT_01206940 != 0) {
    FUN_00408900(this, &DAT_01206940, 0x8000);
  }
  
  // Handle some other global state
  if (DAT_01129948 != 0) {
    if ((*(uint *)(DAT_01129948 + 0x4c) >> 5 & 1) == 0) {
      cVar1 = FUN_00842870();
      if (cVar1 == '\0') goto LAB_008d0fd3;
    }
    FUN_00842d20(1);
  }
  
LAB_008d0fd3:
  if (DAT_0112982c != 0) {
    FUN_00983190();
    *(undefined1 *)(DAT_0112982c + 0x90) = 0;
  }
  
  uVar2 = FUN_005bff40(&DAT_00e3e3e0);
  FUN_005c3960();
  FUN_005c2740(uVar2);
  FUN_004e01a0();
  
  return this;
}