// FUNC_NAME: BuildingManager::setBuildingStatus
undefined4 __thiscall BuildingManager::setBuildingStatus(int this, uint index)
{
  undefined4 *slotPtr;
  
  if (0x18 < index) {
    return 0;
  }
  // Array of building status structures at offset +0x24, each 0xC bytes
  slotPtr = (undefined4 *)(*(int *)(this + 0x24) + index * 0xc);
  *slotPtr = 2; // Set status to 2 (e.g., "owned" or "active")
  if ((slotPtr[1] != 0) && (slotPtr[1] != 0x48)) {
    // slotPtr[1] is some flag/ID; if non-zero and not 0x48, call notify
    if (slotPtr[1] != 0) {
      FUN_008dd2c0(2); // Likely a debug or event notification function
      return 1;
    }
    FUN_008dd2c0(2);
  }
  return 1;
}