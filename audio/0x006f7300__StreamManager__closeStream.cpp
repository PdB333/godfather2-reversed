// FUNC_NAME: StreamManager::closeStream

void __fastcall StreamManager::closeStream(StreamManager* this)
{
    int streamIndex = this->streamIndex;  // +0x28
    if (streamIndex != 0xFF) {
        releaseStream(streamIndex);  // FUN_006f0d60 - close the stream identified by index
        this->streamIndex = 0xFF;    // mark slot as free
    }
}