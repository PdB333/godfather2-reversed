// FUNC_NAME: AudioSource::stop
// Address: 0x006a8450
// Role: Stops the audio source, sets a stop state, releases the internal stream pointer, and clears flags.
//
// Class layout (inferred from offsets):
//   +0x10: uint8_t m_stopState;   // stop type (0 = stopped, 1 = fade, etc.)
//   +0x14: StreamObject* m_stream; // pointer to underlying stream, released if non-null
//   +0x1c: uint32_t m_flags;      // some flag, cleared on stop
//   +0x20: uint8_t m_otherFlag;   // other flag, cleared on stop

void __thiscall AudioSource::stop(uint8_t stopType)
{
    if (this->m_stream != nullptr)
    {
        releaseStream(&this->m_stream); // FUN_004daf90 - likely destructs or releases the stream
        this->m_stream = nullptr;
    }
    this->m_flags = 0;
    this->m_otherFlag = 0;
    this->m_stopState = stopType;
}