// FUNC_NAME: Building::setActive
void __thiscall Building::setActive(int this, byte active)
{
  int iVar1;
  
  // Check if the 'active' flag (bit 1 of flags at +0x10) differs from the requested state
  if ((*(byte *)(this + 0x10) >> 1 & 1) != active) {
    if (active != 0) {
      // Set bit 1 (active flag) at +0x10
      *(ushort *)(this + 0x10) = *(ushort *)(this + 0x10) | 2;
      return;
    }
    // Clear bit 1 (active flag) at +0x10
    *(ushort *)(this + 0x10) = *(ushort *)(this + 0x10) & 0xfffd;
    // If there's a parent building (offset +0x4) and it's not a special ID (0x48 for "none" or 0)
    if ((*(int *)(this + 4) != 0) && (*(int *)(this + 4) != 0x48)) {
      if (*(int *)(this + 4) == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(this + 4) + -0x48;
      }
      // If this building is the current active building of the parent (at parent+0x1e10)
      if (*(int *)(iVar1 + 0x1e10) == this) {
        FUN_007ee8e0(); // likely Building::onActiveRemoved or similar cleanup
      }
    }
  }
  return;
}