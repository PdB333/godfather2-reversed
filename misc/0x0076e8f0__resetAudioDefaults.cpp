// FUNC_NAME: resetAudioDefaults
// Function at 0x0076e8f0: Resets audio channel defaults (likely during game initialization).
void resetAudioDefaults(void)
{
    // Set volume of channel 0 to maximum (1.0f)
    setVolume(0, 1.0f);
    // Reset channel 0 state
    resetChannel(0);
}