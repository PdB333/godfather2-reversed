//FUNC_NAME: resetAudioState
void resetAudioState(void) {
    // Set audio channel to 3 (likely a specific channel index)
    setAudioChannel(3); // FUN_00983c90(3)
    // Clear a flag at offset 0xcc in the global audio manager structure
    *(uint8_t*)(DAT_0112a838 + 0xcc) = 0;
    // Enable audio output with parameter 1 (enable)
    enableAudioOutput(1); // FUN_009848c0(1)
    // Play an audio event identified by hash 0x8dca5d0c and category 0xd
    playAudioEvent(0x8dca5d0c, 0xd); // FUN_00983d80(hash, category)
}