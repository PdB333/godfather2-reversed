// FUNC_NAME: AudioStreamObject::updateStream
void __thiscall AudioStreamObject::updateStream(void)
{
    // Check if bit 6 (0x40) is set in the flags at +0x1c4
    if ((flags_0x1c4 & 0x40) != 0)
    {
        // Clear bit 6
        flags_0x1c4 = flags_0x1c4 & ~0x40;
        // Notify the global audio system to handle stream completion or state change
        g_audioSystem->onStreamEvent(&DAT_012069d4);
    }

    // mpStreamData at +0x200 is a pointer to stream data with reference count at +0x08
    StreamData* streamData = mpStreamData_0x200;
    if (streamData != nullptr && streamData->refCount_0x08 == 0)
    {
        // Reference count dropped to zero, release the stream data
        releaseStreamData(streamData);
    }
}