// FUNC_NAME: NetConnection::cancelQueuedPackets
void __fastcall NetConnection::cancelQueuedPackets(NetConnection* thisPtr)
{
    // Call to clear the queued reliable packet list
    // DAT_012069c4 is likely the global unreliable packet queue or a packet list
    FUN_004086d0(&DAT_012069c4);
    
    // Clear the flag bit 7 (0x80) in field +0x10
    // This flag likely indicates "hasPendingReliablePackets" or "connectionActive"
    thisPtr->field_0x10 &= 0xffffff7f;
}