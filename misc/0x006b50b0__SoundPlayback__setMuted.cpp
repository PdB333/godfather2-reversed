// FUNC_NAME: SoundPlayback::setMuted
void __thiscall SoundPlayback::setMuted(SoundPlayback* this, bool muted)
{
    // Offset +0x34: flags field
    if (muted)
    {
        this->flags |= 0x100000;   // Set bit 20 (mute flag)
    }
    else
    {
        this->flags &= ~0x100000;  // Clear bit 20
    }

    // Offset +0x16c: pointer to a stream object (SoundStream*)
    SoundStream* stream = reinterpret_cast<SoundStream*>(this->streamPtr);
    // Call stop on the stream with parameter 0 (likely meaning "immediate" or "force stop")
    stream->stop(0);
}