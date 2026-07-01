// FUNC_NAME: PlayerF2FSM::updateCameraVFX
void __fastcall PlayerF2FSM::updateCameraVFX(int this)
{
  int vfxIndex;
  uint flags;
  int row;
  int col;
  char buffer[16];
  // +0xdc: bitfield flags for camera VFX state
  // bits 0-1: row selection (0-2)
  // bits 5-9: column selection (0-4)
  
  // Extract row (bits 0-1)
  if ((*(byte *)(this + 0xdc) & 1) == 0) {
    if ((*(uint *)(this + 0xdc) >> 1 & 1) == 0) {
      col = (*(uint *)(this + 0xdc) >> 2 & 1) * 2;
    } else {
      col = 1;
    }
  } else {
    col = 0;
  }
  
  // Extract column (bits 5-9)
  flags = *(uint *)(this + 0xdc);
  if ((flags >> 5 & 1) == 0) {
    if ((flags >> 6 & 1) == 0) {
      if ((flags >> 7 & 1) == 0) {
        if ((flags >> 8 & 1) == 0) {
          row = (flags >> 9 & 1) * 4;
        } else {
          row = 3;
        }
      } else {
        row = 2;
      }
    } else {
      row = 1;
    }
  } else {
    row = 0;
  }
  
  vfxIndex = row + col * 5;
  
  // Set camera VFX properties from lookup table
  // +0xd8: camera FOV multiplier
  *(float *)(this + 0xd8) = (float)(&DAT_00e50fe0)[vfxIndex * 3] * DAT_00e445a4;
  // +0xd0: camera near clip
  *(undefined4 *)(this + 0xd0) = (&DAT_00e50fe4)[vfxIndex * 3];
  // +0xd4: camera far clip
  *(undefined4 *)(this + 0xd4) = (&DAT_00e50fe8)[vfxIndex * 3];
  
  // Handle VFX name string
  int newVfx = (&DAT_0112a7c8)[row + col * 5];
  int currentVfx = DAT_0112a808;
  
  if (newVfx != currentVfx) {
    if (currentVfx != 0) {
      // Release current VFX
      undefined4 local_28 = DAT_0112a820;
      undefined4 local_24 = 0;
      undefined1 local_20 = 0;
      FUN_00408a00(&local_28, 0); // likely release/delete
      DAT_0112a808 = 0;
    }
    
    currentVfx = newVfx;
    if (newVfx != 0) {
      // Create new VFX with name "F2FCamVFX<index>"
      _sprintf(buffer, "F2FCamVFX%1d", newVfx);
      undefined4 local_28 = 0;
      undefined4 local_24 = 0;
      FUN_00408240(&local_28, buffer); // likely create VFX
      undefined4 local_1c = local_28;
      undefined4 local_18 = 0;
      undefined1 local_14 = 0;
      FUN_00408a00(&local_1c, 0); // likely play/start
      FUN_00408310(&local_28); // likely release temp
    }
  }
  
  DAT_0112a808 = currentVfx;
  return;
}