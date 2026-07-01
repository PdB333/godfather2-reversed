// FUNC_NAME: Entity::cleanupAfterDeactivation
void __fastcall Entity::cleanupAfterDeactivation(Entity* this) 
{
  // Call global resource release functions
  uint resourceId = getResourceManager(); // FUN_0043b490 - returns handle
  releaseResource(resourceId);            // FUN_007f9620
  setGlobalFlag(0);                       // FUN_007222b0

  // Get the data item list (from offset +0x80)
  DataItem* item = getDataItemAtIndex(this->dataListBase + 0x80); // FUN_00875b90
  if (item != nullptr) {
    item->field_0x14 = 0; // Clear "inUse" flag
  }

  // Check if bit 11 of the flags field is set (Active flag?)
  if ((this->flags & 0x800) != 0) { // 0x800 = bit 11
    this->flags &= ~0x800; // Clear the bit

    // Get parent container pointer
    // this->parentPtr (offset 0x70) points to a reference that is an offset
    // into an array/object at a base address minus 0x48
    ContainerBase* container = nullptr;
    if (this->parentPtr == 0) {
      container = nullptr;
    } else {
      container = reinterpret_cast<ContainerBase*>(*(int*)this->parentPtr - 0x48);
    }
    if (container != nullptr) {
      // Dec reference count at offset +0xe80 (likely activeEntityCount)
      if (container->activeEntityCount != 0) {
        container->activeEntityCount--;
      }
    }
  }
}