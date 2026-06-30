// FUNC_NAME: ObjectManager::removeObject
void __thiscall ObjectManager::removeObject(void)
{
  // this in EAX
  if (!*(char *)((int)this + 0x28)) // m_bDeleted == false
  {
    if (*(int *)((int)this + 0x1c) != 0) // m_pSomeRef
    {
      // Call a virtual release function via g_objectManagerVtable[1] (offset +4)
      (**(code **)(*(int *)g_objectManagerVtable + 4))(*(int *)((int)this + 0x1c), *(undefined4 *)((int)this + 0x20));
      *(undefined4 *)((int)this + 0x1c) = 0;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_objectManagerCS);
    int i = 0;
    if (g_objectCount > 0)
    {
      while (g_objectArray[i] != (int)this)
      {
        i++;
        if (g_objectCount <= i)
        {
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_objectManagerCS);
          return;
        }
      }
      g_objectCount--;
      if (g_objectCount > 0)
      {
        g_objectArray[i] = g_objectArray[g_objectCount];
      }
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_objectManagerCS);
  }
  else // m_bDeleted != false
  {
    ObjectManager::unregisterObject(); // FUN_0060bfa0
    int *pPtr = *(int **)((int)this + 0x2c); // m_pSelfOrOther
    if (pPtr != 0)
    {
      if (g_objectManagerVtable != 0)
      {
        (**(code **)(*g_objectManagerVtable + 4))(pPtr, 0);
      }
      if ((int)this != (int)pPtr)
      {
        *(undefined4 *)((int)this + 0x2c) = 0;
        return;
      }
    }
  }
  return;
}