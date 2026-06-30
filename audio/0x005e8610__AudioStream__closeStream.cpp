// FUNC_NAME: AudioStream::closeStream
// Address: 0x005e8610
// Releases a streaming resource handle and frees the associated buffer.
// Returns 1 if released successfully, 0 if already released or release failed.
int AudioStream::closeStream()
{
    // +0x1c8 : stream handle (resource ID, -1 means unused)
    if (this->streamHandle != -1)
    {
        // Global vtable at DAT_01223510, offset 0x54 is a release/close function
        bool released = (**(code**)(*DAT_01223510 + 0x54))(this->streamHandle);
        if (released)
        {
            this->streamHandle = -1;

            // +0x1c0 : pointer to allocated stream buffer
            if (this->bufferPtr != nullptr)
            {
                // Free buffer using global allocator at DAT_01223518
                // +0x04 from DAT_01223518 points to a vtable with a free function at offset 0x04
                if (*(int*)(DAT_01223518 + 4) != 0)
                {
                    (**(code**)(**(int**)(DAT_01223518 + 4) + 4))(this->bufferPtr, 0);
                }
                this->bufferPtr = nullptr;  // +0x1c0
                this->bufferSize = 0;       // +0x1c4 (probably buffer size)
                return 1;
            }
        }
    }
    return 0;
}