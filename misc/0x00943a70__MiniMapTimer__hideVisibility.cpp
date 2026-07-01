// FUNC_NAME: MiniMapTimer::hideVisibility
void __fastcall MiniMapTimer::hideVisibility(int thisPtr)
{
  char formatBuffer [256];
  
  // Check if the visible flag (bit 0 at offset 0xFC) is set
  if ((*(byte *)(thisPtr + 0xfc) & 1) != 0) {
    // Build the timer name string: "mmap/minimap_timer._visible"
    __snprintf(formatBuffer, 0x100, "mmap/minimap_timer.%s", "_visible");
    // Set timer visibility to 0 (false) via the scripting system
    FUN_0059ee00(formatBuffer, 0);
    // Clear the visible flag (bit 0) at offset 0xFC
    *(ushort *)(thisPtr + 0xfc) = *(ushort *)(thisPtr + 0xfc) & 0xfffe;
  }
  return;
}