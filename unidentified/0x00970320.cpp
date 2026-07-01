// FUN_NAME: FamilyTreeController::updateSortedTitle
void __fastcall FamilyTreeController::updateSortedTitle(int *this) {
  // VTable call at offset 0x8 (vtable+4) - probably "update" or "preFrame"
  (**(code **)(*this + 8))();
  FUN_00982c90();
  // Clear bit 2 of the flags at offset 0x76C (0x1BD*4)
  this[0x1BD] = this[0x1BD] & 0xFFFFFFFB;
  FUN_00983120(0, 0, 0);
  // Sort mode at offset 0xDC (0x37*4)
  switch (this[0x37]) {
  case 1:   // Name sort
  case 5:   // Rank sort
  case 6:   // Level sort
  case 7:   // Progress sort
  case 0xB: // Custom sort
  case 0xC: // Default sort
  {
    int *listMgr = FUN_00965910(); // Get the list/grid manager
    if (listMgr != (int *)0x0) {
      FUN_005a04a0("HighlightSortedTitle", 0, &DAT_00d8cdec, 0);
      // VTable+0xA0: setHighlightedTitle(bool) - offset 40 in vtable
      (**(code **)(*listMgr + 0xA0))(this[0x44], this[0x37] == 1);
      // VTable+0x6C: refresh() - offset 27 in vtable
      (**(code **)(*listMgr + 0x6C))(0);
    }
    break;
  }
  case 8: // Exiting sort mode
    // Check bit 12 (0x1000) of flags (offset 0x76C)
    if (((uint)this[0x1BD] >> 0xC & 1) != 0) {
      FUN_009700c0(); // Handle exit animation/transition
      return;
    }
  // default: fall through
  }
  return;
}