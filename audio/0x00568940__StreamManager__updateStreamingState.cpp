// FUNC_NAME: StreamManager::updateStreamingState
void StreamManager::updateStreamingState(void)
{
  int prevState = *(int *)((char *)this + 0xC);
  if (prevState != 2 && prevState != 3 && prevState != 4)
  {
    // Not in a final state; start loading if not already started
    if (prevState != 1)
    {
      *(int *)((char *)this + 0xC) = 1;
    }

    if (g_bStreamingEnabled)               // DAT_012234b8
    {
      if (isLoadAllowed())                  // FUN_00566920
      {
        void *pStreamMgr = getStreamingManager();  // FUN_00ad8d40
        if (pStreamMgr != nullptr)
        {
          // Get the actual loader interface from the streaming manager
          void *pLoader = (*(void *(__thiscall **)(void *))(*(int *)pStreamMgr + 4))(pStreamMgr);
          if (pLoader != nullptr)
          {
            *(int *)((char *)this + 0xC) = 2; // Mark as loaded

            char szPath[256];              // auStack_108
            char szName[64];               // auStack_148
            int resourceId;                // auStack_14c

            // Copy default path/name (max 0x100 bytes)
            getDefaultPath(szPath, 0x100); // FUN_00ae9750

            // Retrieve the loader's resource path
            (*(void (__thiscall **)(void *, char *))(*(int *)pLoader + 0x34))(pLoader, szName);

            // Get the unique resource identifier
            (*(void (__thiscall **)(void *, int *))(* (int *)pLoader + 0))(pLoader, &resourceId);

            // Load the specific streaming asset
            loadStreamedAsset(&resourceId); // FUN_00568c00

            // Finalize load process
            finalizeStreamLoad();           // FUN_00ae97f0
          }
        }
      }
    }
  }
}