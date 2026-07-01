// FUNC_NAME: UIHudMinimapMarkerManager::setMarkerDisplay
void __thiscall UIHudMinimapMarkerManager::setMarkerDisplay(int this, char show, char animate)
{
  // +0x50: flags field (bit0 = something, bit3 = iconShown, bit4 = animated)
  uint flags = *(uint *)(this + 0x50);
  
  if ((flags & 1) == 0) {
    if (show == '\0') {
      // Hide the icon
      FUN_005a04a0("HideIconDisplay", 0, &DAT_00d87b2c, 0);
      *(uint *)(this + 0x50) = flags & 0xffffffe7; // clear bits 3 and 5
    }
    else {
      // Show the icon
      FUN_005a04a0("ShowIconDisplay", 0, &DAT_00d87b2c, 0);
      *(uint *)(this + 0x50) = flags | 8; // set bit 3 (iconShown)
      
      if (animate == '\0') {
        // No animation requested, just clear animated flag
        *(uint *)(this + 0x50) = *(uint *)(this + 0x50) & 0xffffffef; // clear bit 4
        return;
      }
      
      // Start animation
      *(undefined4 *)(this + 0x70) = 0; // +0x70: animation timer or state
      if ((*(uint *)(this + 0x50) >> 4 & 1) == 0) {
        FUN_005c0260(this + 0x10, &LAB_00928720, 1); // Start animation timer (0x10 = animation callback data)
        *(uint *)(this + 0x50) = *(uint *)(this + 0x50) | 0x10; // set bit 4 (animated)
      }
    }
  }
}