// FUNC_NAME: StreamManager::CloseStream
void StreamManager::CloseStream()
{
    // +0x334: Handle to an OS resource (e.g., file, event)
    CloseHandle(this->resourceHandle);
    this->resourceHandle = 0;

    // +0x33c: Pointer to an allocated buffer or internal resource
    FreeResource(this->dataPointer);
    this->dataPointer = 0;

    // +0x338: Additional state (e.g., size, flags)
    this->sizeOrFlags = 0;
}