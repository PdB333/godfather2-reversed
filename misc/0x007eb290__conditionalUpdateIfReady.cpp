// FUNC_NAME: conditionalUpdateIfReady
// Function address: 0x007eb290
// Role: Checks if the game is ready (via isGameReady()) and if so, triggers updates for three subsystems (audio, input, rendering). Called periodically.

void conditionalUpdateIfReady(void)
{
    char isReady;

    isReady = isGameReady();               // FUN_00481660: checks global readiness flag
    if (isReady != '\0') {
        updateAudioSubsystem();            // FUN_0093c210: audio streaming/playback update
        updateInputSubsystem();            // FUN_00983190: controller/keyboard input polling
        updateRenderingSubsystem();        // FUN_00984eb0: frame buffer/present or scene update
        return;
    }
    return;
}