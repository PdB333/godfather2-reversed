// FUNC_NAME: StreamManager::stopActiveStream
void __thiscall StreamManager::stopActiveStream(StreamManager *this)
{
    // Check if the active stream pointer (at +0x64) is non-null
    if (this->activeStream != 0)
    {
        // Call the stop/release virtual function at offset 0x18 of the stream's vtable
        this->activeStream->vtable->stop();  // +0x18
    }

    // Clear the stream active flag (+0x60)
    this->streamActiveFlag = 0;
}