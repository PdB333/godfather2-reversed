// FUNC_NAME: initGameSystems
void initGameSystems(void)
{
    initRenderSystem();  // 0x007fbe50 - Likely initializes rendering/display system
    initAudioSystem(0);  // 0x007f6300 - Likely initializes audio with a parameter (0 = silent? or default)
}