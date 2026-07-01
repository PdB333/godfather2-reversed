// FUNC_NAME: UIMinimapMarkerManager::removeMarkerFromSurface
undefined4 __fastcall UIMinimapMarkerManager::removeMarkerFromSurface(int thisPtr)
{
  // Check if the marker is currently being displayed (bit 0x20000 in flags)
  if ((*(uint *)(thisPtr + 0x11c) >> 0x11 & 1) != 0) {
    // Call engine function to remove the marker from the surface
    FUN_005a04a0("RemoveMarker", 0, &DAT_00d8b2cc, 1, thisPtr + 8);
    // Clear the display flag (bit 0x20000)
    *(uint *)(thisPtr + 0x11c) = *(uint *)(thisPtr + 0x11c) & 0xfffdffff;
  }
  return 2; // Return success code
}