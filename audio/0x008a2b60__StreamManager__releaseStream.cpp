// FUNC_NAME: StreamManager::releaseStream
bool __fastcall StreamManager::releaseStream(int thisPtr)
{
    // Get pointer to stream interface at offset +0x8
    StreamInterface* pStream = *(StreamInterface**)(thisPtr + 0x8);
    if (pStream != nullptr) {
        // Call virtual destructor or release function (vtable index 0)
        pStream->release();
        // Clear the stream pointer
        *(StreamInterface**)(thisPtr + 0x8) = nullptr;
        // Set flag at offset 0x37c to indicate resource released
        *(uint32*)(thisPtr + 0x37c) |= 0x100;
    }
    return pStream != nullptr;
}