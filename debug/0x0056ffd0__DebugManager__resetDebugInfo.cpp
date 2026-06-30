// FUNC_NAME: DebugManager::resetDebugInfo
void DebugManager::resetDebugInfo(void* thisPtr)
{
    int debugValues[3] = {0, 0, 0}; // Three zeroed out debug fields (possibly counters or flags)
    // Call a virtual/global function pointer with this and the cleared struct
    ((void (*)(void*, int*))DAT_0120556c)(thisPtr, debugValues);
}