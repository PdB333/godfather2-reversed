// FUNC_NAME: EAudioSystem::ResetChannelGains
void __thiscall EAudioSystem::ResetChannelGains(EAudioSystem *this)
{
    // 68-byte command block used to batch state changes
    char commandBlock[68];
    // Begin a command block of type 2 (audio state) with flag 0
    EAudioSystem::BeginCommand(this, 2, 0, commandBlock);
    // Reset 128 channel gains to 1.0 (full volume)
    float *gains = this->channelGains; // +0x?? offset from this
    for (int i = 0; i < 128; i++)
    {
        gains[i] = 1.0f;
    }
    // Finalize and submit the command block
    EAudioSystem::EndCommand(commandBlock);
}