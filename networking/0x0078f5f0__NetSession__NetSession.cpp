// FUNC_NAME: NetSession::NetSession
void __fastcall NetSession::NetSession(int this)
{
    // Initialize sequence/ack fields to invalid (-1)
    *(int *)(this + 0x9c) = -1; // +0x9c: lastReceivedAck
    *(int *)(this + 0xa0) = -1; // +0xa0: lastSentSeq

    // Initialize global mutexes for thread-safe packet handling
    Mutex::Mutex(&g_sendMutex);   // DAT_0112db6c
    Mutex::Mutex(&g_recvMutex);   // DAT_012069c4

    // Initialize packet pool and connection state
    initializePacketPool(0);      // FUN_00790110
    initializeConnectionState(0); // FUN_00790750

    // Construct reliable queue sub-object at offset 0x50
    ReliableQueue::ReliableQueue(this + 0x50); // FUN_00791350

    // Mark session as inactive initially
    *(int *)(this + 0x98) = 0; // +0x98: isActive
}