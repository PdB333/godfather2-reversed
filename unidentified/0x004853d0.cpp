// FUN_004853d0: EarsAudioDriver::initialize

undefined4 * __thiscall EarsAudioDriver::initialize(int param_2)
{
  LPCRITICAL_SECTION lpCriticalSection;
  undefined4 *handle;
  int internal;
  int iVar2;
  uint uVar4;
  void *fsPointer;
  AudioFormat local_c;
  
  g_sampleRate = (param_2 + 0x7fU) & 0xffffff80;  // rounds up to multiple of 128, likely sample rate in Hz
  g_driver = this;
  this->vtable = &PTR_FUN_00e336c0;
  g_bufferSize = g_sampleRate * 2;
  this->field_4 = 0;
  this->field_8 = 0;
  this->field_C = 0;
  handle = (undefined4 *)FUN_009c8f80();           // get audio engine singleton
  local_c.channels = 2;
  local_c.sampleSize = 0x80;                      // 128, possibly bits per sample or block align
  local_c.field_8 = 0;
  g_buffer = (**(code **)*handle)(g_bufferSize, &local_c); // allocate audio buffer
  internal = FUN_009c8e50(0x1e0);                 // allocate internal structure (480 bytes)
  if (internal != 0) {
    internal = FUN_006488e0(this);                 // initialize internal object
  }
  g_internal = internal;
  *(code **)(internal + 0x198) = &LAB_00485350;   // set callback function pointer
  *(undefined4 **)(internal + 0x19c) = this;      // back-pointer to driver
  FUN_0064a7c0(0x3fff);                            // potentially set max entries for hash table
  lpCriticalSection = *(LPCRITICAL_SECTION *)(internal + 0x1b8);
  if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
    EnterCriticalSection(lpCriticalSection);
    lpCriticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&(lpCriticalSection[1].DebugInfo)->Type + 1);
  }
  iVar2 = FUN_00649040(internal, 4);               // allocate/find hash bucket
  if (iVar2 != 0) {
    uVar4 = *(int *)(internal + 0x58) * 2;
    if (uVar4 <= *(int *)(internal + 0x60) * 4 + 4U) {
      uVar4 = uVar4 + 1;
      if (uVar4 < *(uint *)(internal + 0x5c)) {
        uVar4 = *(uint *)(internal + 0x5c);
      }
      FUN_0064a7c0(uVar4);
    }
    uVar4 = (*(uint *)(iVar2 + 8) >> 4) % *(uint *)(internal + 0x58);
    *(undefined4 *)(iVar2 + 0x18) = *(undefined4 *)(*(int *)(internal + 0x54) + uVar4 * 4);
    *(int *)(*(int *)(internal + 0x54) + uVar4 * 4) = iVar2;
    *(int *)(internal + 0x60) = *(int *)(internal + 0x60) + 1;
  }
  if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
    lpCriticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&lpCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
    LeaveCriticalSection(lpCriticalSection);
  }
  fsPointer = (void *)(*(int *)(__readfsdword(0x2c)) + 8);
  *(undefined4 *)fsPointer = g_buffer;              // store buffer in thread-local handle
  FUN_00ab51e0(1);                                  // set some flag
  this->field_10 = 0;
  this->field_14 = 0;
  this->field_18 = 0;
  this->field_1C = 0;
  return this;
}