// FUNC_NAME: StreamManager::getFilePathBuffer
char* StreamManager::getFilePathBuffer()
{
    // +0x15c: File path buffer (char array)
    // +0x160: Initialized flag (int, 0 = not initialized)
    // +0x17c: Source file path string pointer

    if (IsStreamingEnabled() && *(int*)(this + 0x160) == 0)
    {
        copyString(*(char**)(this + 0x17c), this + 0x15c); // copy source to buffer
    }
    return (char*)(this + 0x15c);
}