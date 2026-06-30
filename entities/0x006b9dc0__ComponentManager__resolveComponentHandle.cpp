// FUNC_NAME: ComponentManager::resolveComponentHandle
int __thiscall ComponentManager::resolveComponentHandle(int thisPtr, int* guid)
{
  int result = 0;

  // Test bit 2 of flags at offset +0x80. If set, use global component lookup.
  if ((*(unsigned int*)(thisPtr + 0x80) >> 2 & 1) == 0)
  {
    // Known component GUID (e.g., for GodfatherGameManager)
    static const int kComponentGUID[4] = {0xBABDB9BA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911};

    bool isKnownGUID = (guid[0] == kComponentGUID[0] && guid[1] == kComponentGUID[1] &&
                        guid[2] == kComponentGUID[2] && guid[3] == kComponentGUID[3]);
    bool isNullGUID = (guid[0] == 0 && guid[1] == 0 && guid[2] == 0 && guid[3] == 0);

    if (!isKnownGUID && !isNullGUID)
    {
      // Attempt to locate the component via GUID-based lookup (SimManager::findByGUID)
      int componentBase = FUN_00446100(guid, 0);
      if (componentBase != 0)
      {
        // Return offset into component (e.g., +0x50 for component data)
        result = componentBase + 0x50;
      }
    }
  }
  else
  {
    // Global component path: retrieve from singleton or global structure
    int globalBase = FUN_0078e110();
    if (globalBase != 0)
    {
      result = FUN_0078dbb0();
    }
  }

  return result;
}