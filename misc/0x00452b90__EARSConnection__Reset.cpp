// FUNC_NAME: EARSConnection::Reset
void __thiscall EARSConnection::Reset(void)
{
  // Release global synchronization objects (likely mutexes or semaphores)
  // These are used for thread-safe access to shared network resources
  ReleaseHandle(&g_hGlobalResourceA);  // DAT_012069e4
  ReleaseHandle(&g_hGlobalResourceB);  // DAT_012069dc

  // If a dynamically allocated packet buffer exists, free it
  if (m_pPacketBuffer != (void *)0x0)  // +0x30
  {
    CustomFree(m_pPacketBuffer);       // FUN_004daf90
    m_pPacketBuffer = (void *)0x0;     // +0x30
  }

  // Reset all connection state fields to zero
  // These fields track send/receive sequencing, window sizes, and other protocol state
  m_ulSendSequence = 0;    // +0x10
  m_ulRecvSequence = 0;    // +0x14
  m_ulSendWindowSize = 0;  // +0x18
  m_ulRecvWindowSize = 0;  // +0x1c
  m_ulAckSequence = 0;     // +0x20
  m_ulRemoteSendSeq = 0;   // +0x24
  m_ulRemoteRecvSeq = 0;   // +0x28
  m_ulFlags = 0;           // +0x2c
  m_pReliableBuffer = (void *)0x0; // +0x38 (could be another pointer or integer)
  return;
}