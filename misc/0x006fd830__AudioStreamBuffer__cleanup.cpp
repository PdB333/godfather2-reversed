// FUNC_NAME: AudioStreamBuffer::cleanup
void __fastcall AudioStreamBuffer::cleanup(int *this)
{
  // +0x00: state (enum: 0=idle, 1=allocated, 2=loading, 3/4=playing/streaming, 5/6=stopped)
  // +0x04: flags (some sub-state)
  // +0x08: dataBuffer (void*) - allocated buffer
  // +0x0C: bufferSize (int)
  // +0x10: dataOffset (int) - written bytes offset
  // +0x14: ... potentially padding
  // +0x18: subObject (some pointer that needs separate destruction)

  // Lock global mutex (EARS buffer manager mutex)
  Mutex::lock(&gBufferManagerMutex);  // FUN_00ab4db0(&DAT_00d60c08)

  int state = *this;
  if (state == 1) {
    if (this[2] == 0) {
      goto skipCleanup;  // LAB_006fd878
    }
  } else {
    if (state != 2) {
      if ((state == 3) || (state == 4)) {
        // Specific cleanup for active streaming states
        stopStreaming();  // FUN_006fcb60()
      }
      goto skipCleanup;  // LAB_006fd878
    }
    // Transition from loading (state 2) to stopped (state 6)
    *this = 6;
    this[1] = 0;
  }

  // State is now 6 (stopped) or 5, or was 1 with buffer present
  if (this[2] != 0) {
    // Free buffer memory
    Memory::free(this[2]);                // FUN_004a83a0
    // Clear buffer: set entire block to zero before deallocation? (security/overwrite)
    Memory::memset((void *)this[2], 0, this[3]); // _memset
    this[4] = 0; // reset offset
  }

  // Reset state and flags
  this[1] = 0;
  *this = 0;  // state = idle

skipCleanup:  // LAB_006fd8b8
  if (this[2] != 0) {
    // Additional release of the buffer resource (e.g., reference count decrement)
    releaseBufferRef(this[2]);  // FUN_009c8f10
  }
  this[3] = 0; // clear buffer size

  // Unlock mutex (two-tier unlock? maybe nested locks)
  Mutex::unlock();  // FUN_00ab4e70 (likely unlock outer)
  Mutex::unlock();  // FUN_00ab4d30 (likely unlock inner? or counter)

  // Destroy sub-object if present
  if (this[6] != 0) {
    subObjectDestructor(this + 6);  // FUN_004daf90
  }
}