// FUNC_NAME: SoundStream::release
// Offset +0x490: byte flag indicating if stream is active
// Offset +0x494: pointer/reference to managed resource (e.g., a bank stream handle)
// Offset +0x498: associated data (integer)
// Offset +0x49c: associated data (integer)
// Offset +0x4a0: function pointer for releasing the resource (takes the handle as argument)
bool __thiscall SoundStream::release()
{
    bool bResult = false;
    if (this->bActive)
    {
        this->stopStream();          // calls FUN_005e8300 to internally stop/cleanup the stream
        this->bActive = false;       // clear activity flag
        if (this->pHandle != 0)
        {
            // Call the stored release function on the resource handle
            this->releaseCallback(this->pHandle);
        }
        // Zero out the resource handle and two associated integer fields
        this->pHandle = 0;
        this->field_0x498 = 0;
        this->field_0x49c = 0;
        bResult = true;
    }
    return bResult;
}