// FUNC_NAME: AudioEntry::tryPlayIfNotBlocked
// Address: 0x008c81d0
// Checks a blocking flag on an associated audio data object and 
// conditionally plays the audio event with priority 4.

void __fastcall AudioEntry::tryPlayIfNotBlocked(int thisPtr)
{
    char isChannelAvailable;

    // Get pointer to audio data/state (offset +0x8)
    int* audioData = *(int**)(thisPtr + 0x8);
    if (audioData != (int*)0)
    {
        // Check if the block flag (bit 20 at offset 0x5c) is NOT set
        // This flag likely indicates the audio is currently disabled or muted
        if ((*(unsigned int*)(audioData + 0x5c) >> 0x14 & 1) == 0)
        {
            // Ask the audio system if a channel is available to play
            isChannelAvailable = FUN_00791230();
            if (isChannelAvailable != '\0')
            {
                // Play the audio using the handle stored at offset +0xC
                // Second parameter 4 likely indicates a priority or channel slot
                FUN_00791250(*(int*)(thisPtr + 0xC), 4);
            }
        }
    }
}