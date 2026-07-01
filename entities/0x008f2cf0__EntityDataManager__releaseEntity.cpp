// FUNC_NAME: EntityDataManager::releaseEntity
void __thiscall EntityDataManager::releaseEntity(int* thisPtr, int entityId)
{
  uint flags = thisPtr[4];  // +0x10: flags field
  // Check if entity is pending release or in a transitional state (bit 6 and XOR of bits 5 and 3)
  if (((flags >> 6 & 1) != 0) && (((byte)(flags >> 5) ^ (byte)(flags >> 3)) & 1) != 0)
  {
    FUN_008f2ae0(entityId);  // Handle pending release
    return;
  }

  int entityType = thisPtr[3];             // +0x0C: type/state of entity
  thisPtr[4] = thisPtr[4] & 0xffffffbf;    // Clear bit 6 (pending)
  int callbackArg = thisPtr[0xD];          // +0x34: callback argument
  code* callback = (code*)thisPtr[0xC];    // +0x30: callback function pointer
  thisPtr[3] = 0;                           // Reset type
  thisPtr[0xC] = 0;                         // Clear callback
  thisPtr[0xD] = 0;                         // Clear callback arg

  // If bit 2 was set, release a global lock (e.g., mutex)
  if ((flags >> 2 & 1) != 0)
  {
    FUN_0068c590(1);        // Unlock/release mutex
    thisPtr[4] = thisPtr[4] & 0xfffffffb;  // Clear bit 2
  }

  // Virtual call to get the entity's current ID (or validate)
  int currentId = (**(int (__thiscall**)(int*))(*thisPtr + 0x2c))();  // vtable+0x2c: getEntityId?
  if (entityId == currentId)
  {
    // Log string based on entity type (4 or 7)
    undefined4 stringParam;
    if (entityType == 4)
    {
      stringParam = DAT_0112fe20;  // Probably "EntityErrorRemove" or similar
    }
    else if (entityType == 7)
    {
      stringParam = DAT_0112fe30;  // Probably "EntityRemoved" or similar
    }
    else
    {
      goto call_callback;
    }
    undefined4 unused1 = 0;
    undefined1 unused2 = 0;
    FUN_00408a00(&stringParam, 0);  // Debug output (log message)
  }

call_callback:
  // Invoke the stored callback with entityId and callbackArg
  (*callback)(entityId, callbackArg);
  return;
}