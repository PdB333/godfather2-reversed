// FUNC_NAME: TNL::Connection::getSendDataStart
int __fastcall TNL::Connection::getSendDataStart(int this)
{
    // +0x20: mSendBuffer (pointer to send buffer header)
    return *(int *)(this + 0x20) + 4; // skip 4-byte header to get writable data area
}