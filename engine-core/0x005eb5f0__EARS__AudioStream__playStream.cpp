// FUNC_NAME: EARS::AudioStream::playStream
void __thiscall EARS::AudioStream::playStream(
    uint        soundId,
    uint        channel,
    uint        category,
    uint        priority,
    int         volumeInt,
    uint        flags,
    byte        leftVolByte,
    byte        rightVolByte
)
{
    // Engine global scaling factors (likely for converting integer to float, e.g. 1.0f / 255.0f)
    extern float g_scaleVolume;   // DAT_00e2af48
    extern float g_scalePan;      // DAT_00e2af44
    extern uint  g_channelMask;   // DAT_00e2b1a4

    // Audio format structure (proprietary EARS format, 36 uint32s plus a leading field)
    struct EarsAudioFormat {
        uint32 firstField;     // local_98
        uint32 buffer[36];     // auStack_94
    } fmt;

    // Initialize format
    fmt.firstField = g_channelMask;
    fmt.buffer[0x22] = 0;                       // Clear one extra slot

    // Fill 16 channel pairs (mask + speaker position)
    for (uint i = 0; i < 16; i++) {
        fmt.buffer[i * 2]     = g_channelMask;  // Channel mask
        fmt.buffer[i * 2 + 1] = 0;              // Speaker position / flags
    }

    // Clear two more slots (likely channel count or unused)
    fmt.buffer[0x20] = 0;
    fmt.buffer[0x21] = 0;

    // Scale volume and pan from integer range to float
    float volume    = (float)volumeInt    * g_scaleVolume;
    float leftVol   = (float)leftVolByte  * g_scalePan;
    float rightVol  = (float)rightVolByte * g_scalePan;

    // Call the audio engine to play the stream
    // Parameters: soundId, channel, category, priority, volume, flags, leftVol, rightVol, formatPtr, sampleRate(96000), reserved(0)
    FUN_005eb6d0(
        soundId, channel, category, priority,
        volume, flags, leftVol, rightVol,
        &fmt, 96000, 0
    );
}