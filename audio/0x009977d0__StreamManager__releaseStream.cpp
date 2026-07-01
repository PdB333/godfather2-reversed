// FUNC_NAME: StreamManager::releaseStream
void __fastcall StreamManager::releaseStream(uint* streamHandle) // param_1 is a pointer to a stream handle structure
{
    int streamIndex = streamHandle[2]; // +0x08: index into stream array
    if (streamIndex >= 0)
    {
        void* tlsData = TlsGetValue(DAT_01139810); // get per-thread stream manager data (TLS index)
        // Release stream at base address + (index * 64), with resource type 0x17 (23)
        FUN_00aa26e0(*streamHandle, streamIndex << 6, 0x17);
    }
}