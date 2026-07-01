// FUNC_NAME: EARS::Animation::release
void __fastcall Animation::release(int *this)
{
  // +0x60 (offset 0x180) likely a bitfield/status word (16-bit)
  // Check if the reference count (bit 15) is set (negative short)
  if ((short)this[0x60] < 0) {
    // Decrement global resource counter
    FUN_004086d0(&DAT_012069d4);
    // Clear the high bit (reference count flag)
    *(ushort *)(this + 0x60) = *(ushort *)(this + 0x60) & 0x7fff;
  }
  // Check if already released (bit 0)
  if ((*(ushort *)(this + 0x60) & 1) == 0) {
    // Mark as released
    *(ushort *)(this + 0x60) = *(ushort *)(this + 0x60) | 1;
    // Release the associated resource/handle at +0x61 (offset 0x184)
    FUN_00851210(this[0x61]);
    // Check if still active (bit 14) and not paused (bits 12-13)
    if ((*(ushort *)(this + 0x60) & 0x4000) != 0) {
      if ((*(ushort *)(this + 0x60) & 0x3000) == 0) {
        // Call virtual function at vtable offset 0x14 (likely cleanup/stop)
        (**(code **)(*this + 0x14))();
      }
      // Set the "stopped" flag (bit 13)
      *(ushort *)(this + 0x60) = *(ushort *)(this + 0x60) | 0x2000;
    }
  }
}