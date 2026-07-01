// FUNC_NAME: MapContainer::findOrCreateEntry
undefined4 * __thiscall MapContainer::findOrCreateEntry(MapContainer *this, undefined4 *outEntry, undefined4 key)
{
  undefined ***pppuVar1;
  char equalFlag;
  uint hashIndex;
  int iVar4;
  undefined ***pppuVar5;
  undefined **local_70 [19];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  // State machine based on count field at +0x0C
  if (*(int *)(this + 0xc) == 0) {
    // No entries yet: initialize first entry
    MapContainer::clear(); // FUN_008334a0
    local_70[0] = &PTR_LAB_00d73688; // vtable pointer for entry type
    MapContainer::assignDefault(); // FUN_009d3650
    MapContainer::initSlot(local_70); // FUN_0081f9f0
    *outEntry = &PTR_LAB_00d73688;
    outEntry[0x13] = local_24; // copy the 16 bytes of entry data (offsets 0x4C-0x58 relative to entry base)
    outEntry[0x14] = local_20;
    outEntry[0x15] = local_1c;
    outEntry[0x16] = local_18;
    return outEntry;
  }
  if (*(int *)(this + 0xc) != 1) {
    // More than one entry: hash the key, search for match
    hashIndex = MapContainer::hashKey(key); // FUN_0082de40
    if (hashIndex == 0xffffffff) {
      // Hash failed: fallback to blank entry
      MapContainer::clear();
      local_70[0] = &PTR_LAB_00d73688;
      MapContainer::assignDefault();
      pppuVar5 = local_70;
    }
    else {
      *(uint *)(this + 4) = hashIndex; // store hash index
      // Determine next slot index (circular resolution)
      if (hashIndex < *(int *)(this + 0xc) - 1U) {
        iVar4 = hashIndex + 1;
      }
      else {
        iVar4 = 0;
      }
      // Get pointers to current and next slot structures (each slot is a pointer array)
      pppuVar1 = *(undefined ****)(*(int *)(this + 8) + hashIndex * 4);
      pppuVar5 = *(undefined ****)(*(int *)(this + 8) + iVar4 * 4);
      // Check if the next slot's key matches the incoming key
      equalFlag = MapContainer::keyEqual(key, pppuVar5 + 1); // FUN_00835a00
      if (equalFlag != 0) {
        // Key matches next slot – use current slot instead (TODO: verify logic)
        pppuVar5 = pppuVar1;
      }
    }
    // Finalize the entry construction from the selected slot
    MapContainer::finalizeEntry(pppuVar5); // FUN_0082dcc0
    return outEntry;
  }
  // Exactly one entry: retrieve first slot
  iVar4 = **(int **)(this + 8); // first entry pointer
  MapContainer::initSlot(iVar4); // FUN_0081f9f0 (reuse init?)
  *outEntry = &PTR_LAB_00d73688;
  outEntry[0x13] = *(undefined4 *)(iVar4 + 0x4c); // copy 16 bytes of entry data
  outEntry[0x14] = *(undefined4 *)(iVar4 + 0x50);
  outEntry[0x15] = *(undefined4 *)(iVar4 + 0x54);
  outEntry[0x16] = *(undefined4 *)(iVar4 + 0x58);
  return outEntry;
}