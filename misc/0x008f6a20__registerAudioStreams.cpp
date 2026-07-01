// FUNC_NAME: registerAudioStreams
// Address: 0x008f6a20
// This function registers multiple audio stream paths/banks with the EARS engine.
// It calls registerStream (0x008f6770) for each resource identifier.

void registerAudioStreams(void)
{
    // Register stream pairs (likely stereo or left/right channels)
    registerStream((const char*)0x00472420); // First stream identifier
    registerStream((const char*)0x00472440); // Second stream identifier
    registerStream((const char*)0x00472420); // Repeat (possibly for different context)
    registerStream((const char*)0x00472440);
    registerStream((const char*)0x00472420);
    registerStream((const char*)0x00472440);

    // Register two instances of another stream
    registerStream((const char*)0x00709430); // Third stream identifier
    registerStream((const char*)0x00709430);

    // Register single instances of other streams
    registerStream((const char*)0x00703870); // Fourth stream identifier
    registerStream((const char*)0x0070d140); // Fifth stream identifier

    return;
}