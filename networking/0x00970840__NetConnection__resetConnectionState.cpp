// FUNC_NAME: NetConnection::resetConnectionState
void __fastcall NetConnection::resetConnectionState(int thisPtr)
{
  code *pcVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_011308c0);
  *(undefined4 *)(thisPtr + 0xb8) = 0;  // +0xB8: mLastRecvAck
  *(undefined4 *)(thisPtr + 0xbc) = 0;  // +0xBC: mLastSendSeq
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_011308c0);
  *(undefined4 *)(thisPtr + 0xc0) = 0;  // +0xC0: mConnectionState
  *(undefined4 *)(thisPtr + 0xc4) = 0;  // +0xC4: mConnectSequence
  *(undefined1 *)(thisPtr + 0xd0) = 1;  // +0xD0: mIsInitialConnect (bool)
  *(undefined4 *)(thisPtr + 0xd4) = 0;  // +0xD4: mLastRecvPacketTime
  *(undefined4 *)(thisPtr + 0xd8) = 10; // +0xD8: mTimeout (default 10 seconds)
  *(undefined4 *)(thisPtr + 0xe0) = 0;  // +0xE0: mPingTime
  *(undefined4 *)(thisPtr + 0xf4) = 0;  // +0xF4: mPacketLossCount
  *(undefined4 *)(thisPtr + 0xf8) = 0;  // +0xF8: mPacketsSent
  *(undefined4 *)(thisPtr + 0x108) = 0; // +0x108: mBytesSent
  *(undefined4 *)(thisPtr + 0x10c) = 0; // +0x10C: mBytesReceived
  *(undefined1 *)(thisPtr + 0x11c) = 0; // +0x11C: mIsDisconnecting (bool)
  *(undefined4 *)(thisPtr + 0x134) = 0; // +0x134: mLastPingSendTime
  *(undefined4 *)(thisPtr + 0x140) = 0; // +0x140: mPingRetryCount
  *(undefined1 *)(thisPtr + 0x144) = 1; // +0x144: mIsConnected (bool)
  *(undefined1 *)(thisPtr + 0x145) = 0; // +0x145: mIsLocalConnection (bool)
  *(undefined4 *)(thisPtr + 0x148) = 0; // +0x148: mConnectionId
  *(undefined4 *)(thisPtr + 0x14c) = 0; // +0x14C: mConnectRequestId
  *(undefined1 *)(thisPtr + 0x160) = 0; // +0x160: mIsServer (bool)
  *(undefined4 *)(thisPtr + 0x164) = 0; // +0x164: mServerPort
  *(undefined4 *)(thisPtr + 0x168) = 0; // +0x168: mServerAddress
  FUN_0095e840();  // likely resetPacketWindow or similar
  pcVar1 = *(code **)(*(int *)(thisPtr + 0x2ec) + 0x8c); // +0x2EC: mGhostConnection vtable
  *(undefined4 *)(thisPtr + 0x2b4) = 0; // +0x2B4: mGhostSequence
  *(undefined4 *)(thisPtr + 0x2b8) = 0; // +0x2B8: mGhostRecvSequence
  *(undefined4 *)(thisPtr + 700) = 0;    // +0x2BC: mGhostSendSequence
  *(undefined4 *)(thisPtr + 0x2c0) = 0xffffffff; // +0x2C0: mGhostId
  *(undefined4 *)(thisPtr + 0x2c4) = 0; // +0x2C4: mGhostCount
  *(undefined4 *)(thisPtr + 0x2c8) = 0; // +0x2C8: mGhostUpdateCount
  *(undefined4 *)(thisPtr + 0x2cc) = 0; // +0x2CC: mGhostPacketCount
  *(undefined4 *)(thisPtr + 0x2d0) = 0; // +0x2D0: mGhostLastUpdateTime
  *(undefined4 *)(thisPtr + 0x2d8) = 0; // +0x2D8: mGhostSendRate
  *(undefined4 *)(thisPtr + 0x2dc) = 0; // +0x2DC: mGhostSendRateCounter
  (*pcVar1)();  // call ghost connection reset
  (**(code **)(*(int *)(thisPtr + 0x378) + 0x8c))(); // +0x378: mEventConnection vtable reset
  *(undefined4 *)(thisPtr + 0x6ec) = 0; // +0x6EC: mEventSequence
  *(undefined1 *)(thisPtr + 0x6f0) = 0; // +0x6F0: mEventRecvSequence
  *(undefined1 *)(thisPtr + 0x6f1) = 0; // +0x6F1: mEventSendSequence
  *(undefined4 *)(thisPtr + 0x6f4) = 0; // +0x6F4: mEventQueueCount
  if (*(int *)(DAT_01129828 + 0x2c) != 0) {
    FUN_008f1f40();  // likely resetNetInterface
  }
  FUN_00970400(0);  // likely resetConnectionStats
  return;
}