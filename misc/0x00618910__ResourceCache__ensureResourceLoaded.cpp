// FUNC_NAME: ResourceCache::ensureResourceLoaded
void ResourceCache::ensureResourceLoaded(void)
{
  uint resourceIndex = in_EAX;
  ResourceEntry *entry;
  
  // Look up resource entry in global table (0x38 bytes per entry, max 0x1000)
  if (resourceIndex < 0x1000) {
    entry = &DAT_011a0f28 + resourceIndex * 0x38;
  } else {
    entry = nullptr;
  }
  
  // If resource handle not yet loaded (offset +0x1c == 0), load it
  if (entry->handle == 0) {
    uint handle = FUN_00606c80(
        0x15,                           // resource type (e.g., texture/model/sound?)
        *(uint32_t *)(entry + 0xc),     // file offset or identifier
        *(uint16_t *)(entry + 2),       // some dimension/width
        *(uint16_t *)(entry + 4),       // some dimension/height
        *(uint8_t *)(entry + 1),        // flags or priority
        0xffffffff                      // parent/container handle (-1)
    );
    entry->handle = handle;
  }
  
  return;
}