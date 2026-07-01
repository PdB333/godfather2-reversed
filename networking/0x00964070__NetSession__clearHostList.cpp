// FUNC_NAME: NetSession::clearHostList

void __fastcall NetSession::clearHostList(int thisPtr)
{
  uint hostCount;
  
  *(undefined4 *)(thisPtr + 0xe0) = *(undefined4 *)(thisPtr + 0x17c); // m_lastHostCount = m_hostCount
  debugPrint("ClearHostsList", 0, &DAT_00d8cdec, 0);                 // Log the clear operation
  hostCount = 0;
  if (*(int *)(thisPtr + 0x17c) != 0) {                               // If there are hosts
    do {
      releaseHost(*(undefined4 *)(*(int *)(thisPtr + 0x178) + hostCount * 4)); // Release each host object
      hostCount = hostCount + 1;
    } while (hostCount < *(uint *)(thisPtr + 0x17c));                  // Loop until all hosts processed
  }
  *(undefined4 *)(thisPtr + 0x17c) = 0;                                // m_hostCount = 0
  freeHostArray(*(undefined4 *)(thisPtr + 0x178));                      // Free the host array
  *(undefined4 *)(thisPtr + 0x178) = 0;                                // m_hostArray = nullptr
  *(undefined4 *)(thisPtr + 0x180) = 0;                                // m_unknown180 = 0
  return;
}